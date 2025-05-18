#include <iostream>
#include <string>
#include <grpcpp/grpcpp.h>
#include <record_route.grpc.pb.h>
#include <record_route.pb.h>
#include <absl/flags/flag.h>
#include <absl/flags/parse.h>
#include <absl/log/initialize.h>
#include <absl/strings/str_format.h>
#include <cmath>
#include <chrono>
#include <algorithm>
#include <memory>

#include "helper.hpp"
using namespace std;
using namespace routeguide;
using namespace grpc;
using namespace std::chrono;


ABSL_FLAG(uint16_t, port, 50053, "Server port to listen on");

namespace {
    float ConvertToRadians(float num) { return num * 3.1415926 / 180; }

    // The formula is based on http://mathforum.org/library/drmath/view/51879.html
    float GetDistance(const Point& start, const Point& end) {
        const float kCoordFactor = 10000000.0;
        float lat_1 = start.latitude() / kCoordFactor;
        float lat_2 = end.latitude() / kCoordFactor;
        float lon_1 = start.longitude() / kCoordFactor;
        float lon_2 = end.longitude() / kCoordFactor;
        float lat_rad_1 = ConvertToRadians(lat_1);
        float lat_rad_2 = ConvertToRadians(lat_2);
        float delta_lat_rad = ConvertToRadians(lat_2 - lat_1);
        float delta_lon_rad = ConvertToRadians(lon_2 - lon_1);

        float a = pow(sin(delta_lat_rad / 2), 2) +
                  cos(lat_rad_1) * cos(lat_rad_2) * pow(sin(delta_lon_rad / 2), 2);
        float c = 2 * atan2(sqrt(a), sqrt(1 - a));
        int R = 6371000;  // metres

        return R * c;
    }

    std::string GetFeatureName(const Point& point,
                           const std::vector<Feature>& feature_list) {
        for (const Feature& f : feature_list) {
            if (f.location().latitude() == point.latitude() &&
                f.location().longitude() == point.longitude()) {
                return f.name();
                }
        }
        return "";
    }
}

class RouteGuideServiceImpl : public RouteGuide::Service {
    public:
    explicit RouteGuideServiceImpl(string db_path) {
        ParseDb(std::move(db_path), &m_feature_list);
    }

    ~RouteGuideServiceImpl() override {}

   Status GetFeature([[maybe_unused]] ServerContext *context, const Point *point,
        Feature *feature) override {
        feature->set_name(GetFeatureName(*point, m_feature_list));
        feature->mutable_location()->CopyFrom(*point);
        return Status::OK;
    }

    Status ListFeatures([[maybe_unused]] ServerContext *context, const Rectangle *rectangle,
        ServerWriter<Feature> *writer) override {
        auto lo = rectangle->lo();
        auto hi = rectangle->hi();
        long left = (std::min)(lo.longitude(), hi.longitude());
        long right = (std::max)(lo.longitude(), hi.longitude());
        long top = (std::max)(lo.latitude(), hi.latitude());
        long bottom = (std::min)(lo.latitude(), hi.latitude());
        for (const Feature& f : m_feature_list) {
            if (f.location().longitude() >= left &&
                f.location().longitude() <= right &&
                f.location().latitude() >= bottom && f.location().latitude() <= top) {
                writer->Write(f);
                }
        }
        return Status::OK;
    }

    Status RecordRoute([[maybe_unused]] ServerContext *context, ServerReader<Point> *reader,
        RouteSummary *summary) override {
        Point point;
        int point_count = 0;
        int feature_count = 0;
        float distance = 0.0;
        Point previous;

        system_clock::time_point start_time = system_clock::now();
        while (reader->Read(&point)) { // this will be false when all Point's are read
            point_count++;
            if (!GetFeatureName(point, m_feature_list).empty()) {
                feature_count++;
            }
            if (point_count != 1) {
                distance += GetDistance(previous, point);
            }
            previous = point;
        }
        system_clock::time_point end_time = system_clock::now();
        summary->set_point_count(point_count);
        summary->set_feature_count(feature_count);
        summary->set_distance(static_cast<long>(distance));
        auto secs =
            std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
        summary->set_elapsed_time(secs.count());

        return Status::OK;
    }

    Status RouteChat([[maybe_unused]] ServerContext *context,
        ServerReaderWriter<RouteNote, RouteNote> *stream) override {
        RouteNote note;
        while (stream->Read(&note)) {
            std::unique_lock<std::mutex> lock(m_mtx);
            for (const RouteNote& n : m_received_notes) {
                if (n.location().latitude() == note.location().latitude() &&
                    n.location().longitude() == note.location().longitude()) {
                    stream->Write(n);
                    }
            }
            m_received_notes.push_back(note);
        }
        return Status::OK;
    }

private:
    std::vector<Feature> m_feature_list;
    std::mutex m_mtx;
    std::vector<RouteNote> m_received_notes;
};

void RunServer(uint16_t port, std::string db_path) {
    auto listenOn = absl::StrFormat("0.0.0.0:%d", port);
    RouteGuideServiceImpl service(std::move(db_path));

    ServerBuilder builder;
    builder.AddListeningPort(listenOn, InsecureServerCredentials());
    builder.RegisterService(&service);
    auto server = builder.BuildAndStart();
    cout << "Server listening on " << listenOn << endl;
    server->Wait();
}

int main(int argc, char** argv) {
    absl::ParseCommandLine(argc, argv);
    absl::InitializeLog();

    auto port = absl::GetFlag(FLAGS_port);
    std::string db_path = GetDbFileContent();

    RunServer(port, db_path);
}

