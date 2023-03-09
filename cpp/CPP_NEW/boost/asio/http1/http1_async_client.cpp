#include <iostream>
#include <boost/asio.hpp>
#include <memory>
#include <thread>
#include <string>
#include <ostream>
using namespace std;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class HttpClient : public std::enable_shared_from_this<HttpClient> {
private:
    asio::io_context& m_io;
    string m_host;
    tcp::resolver m_resolver;
    tcp::socket m_socket;
    asio::streambuf m_request;
    asio::streambuf m_response;


public:
    HttpClient(asio::io_context& io, string host, const string& doc_path) : m_io(io), m_host(std::move(host)), m_resolver(m_io), m_socket(m_io) {
        // prepare HTTP request here. HTTP request is really trivial.
        // we create an ostream object passing a pointer to asio::streambuf. This way we can easily create the request body.
        std::ostream stream(&m_request);

        // First line is <REQUEST_TYPE> <URI> <HTTPVERSION>\r\n"
        stream << "GET " << doc_path << " HTTP/1.1\r\n";
        // followed by request headers
        stream << "Host: " << m_host << "\r\n";
        stream << "Accept: */*\r\n";
        stream << "Connection: close\r\n\r\n"; // 2 blank lines to denote end of headers
    }

    void run() noexcept {
        // start an async resolver to resolve the HTTP host
        m_resolver.async_resolve(m_host, "http", [self = shared_from_this()]
        (const boost::system::error_code& ec, const tcp::resolver::results_type& endpoints) {
            if(!ec) {
                self->connect(endpoints);
            } else {
                cout << "failed to resolve host: " << self->m_host << " with error " << ec.message() << endl;
            }
        });
    }
private:
    void connect(const tcp::resolver::results_type& endpoints) noexcept {
        asio::async_connect(m_socket, endpoints, [self = shared_from_this()]
        (const boost::system::error_code& ec, const tcp::endpoint& ep ) {
            if(!ec) {
                self->send_request();
            } else {
                cout << "failed to connect to http host " << self->m_host << " with error " << ec.message() << endl;
            }
        });
    }

    void send_request() noexcept {
        asio::async_write(m_socket, m_request, [self = shared_from_this()]
        (const boost::system::error_code& ec, size_t bytes) {
            if(!ec) {
                // prepare to read response
                self->read_response();
            } else {
                cout << "failed to send request to host " << self->m_host << " with error: " << ec.message() << endl;
            }
        });
    }

    void read_response() noexcept {
        // we will first read the response status. If all ok, we will read the response headers, and then only we will read the response body.
        asio::async_read_until(m_socket, m_response, "\r\n", [self = shared_from_this()]
        (const boost::system::error_code& ec, size_t bytes) {
            if(!ec) {
                // Note that async_read_until() may read more data in the streambuf past the \r\n. But that data we should leave in the streambuf for a subsequent
                // call to async_read_until
                std::istream stream(&(self->m_response));

                // read status line
                string http_version{}, status_message{};
                int status_code{};
                stream >> http_version;
                stream >> status_code;
                std::getline(stream, status_message);
                if(!stream || http_version.substr(0, 5) != "HTTP/") {
                    cout << "invalid response received from host " << self->m_host << endl;
                }
                cout << "Received http_version: " << http_version << ", status_code: " << status_code << ", status_message: " << status_message << endl;
                /*
                 * We get a 301 Moved permanently error here. Why?
                 * We are attempting to load an HTTPS URI over plain HTTP. This results in a 301 redirect that points you back to the original page over HTTPS.
                 * This indicates that the hosting server does not provide this resource over insecure HTTP.
                 *
                 * Our HTTP implementation does not support redirects. We are just making a request and delivering the first response.
                 * A full HTTP client would check for a 301 response and retry using the URI in the location header of the 301.
                 * To fix this we need to implement support for TLS/HTTPS and ideally HTTP redirects.
                 */
                if(status_code != 200 && status_code != 301) { // for now accept error 301 and continue reading the response body.
                    return;
                }
                // read response headers next.
                self->read_response_headers();
            } else {
                cout << "failed to read response from " << self->m_host << " with error: " << ec.message() << endl;
            }
        });
    }

    void read_response_headers() noexcept {
        asio::async_read_until(m_socket, m_response, "\r\n\r\n", [self = shared_from_this()]
                (const boost::system::error_code& ec, size_t bytes) {
            if(!ec) {
                std::istream stream(&(self->m_response));
                // dump response headers
                string header{};
                while(std::getline(stream, header) && header != "\r") { // header != "\r" means we read a blank line with \r\n
                    cout << "Header --> " << header << endl;
                }

                // whatever is left in the m_response streambuf, output that
                if(self->m_response.size() > 0)
                    std::cout << &(self->m_response);
                    // read rest of the response body now.
                    self->read_response_body();
            } else {
                cout << "failed to read response headers from " << self->m_host << " with error: " << ec.message() << endl;
            }
        });
    }

    void read_response_body() noexcept {
        asio::async_read(m_socket, m_response, asio::transfer_at_least(1), [self = shared_from_this()]
        (const boost::system::error_code& ec, size_t bytes) {
            if(!ec) {
                std::cout << &(self->m_response);
                self->read_response_body();
            } else if(ec == asio::error::eof) {
                cout << "Response Body Complete!\n";
            } else {
                cout << "failed to read response body from host " << self->m_host << " with error: " << ec.message() << endl;
            }
        });
    }
};

int main(int argc, char** argv) {
    if(argc != 3) {
        cout << "Usage:\n\t" << argv[0] << " <HOST> <DOC_PATH>\n";
        exit (1);
    }
    try {
        asio::io_context io;
        std::make_shared<HttpClient>(io, argv[1], argv[2])->run();

        std::thread t([&io] { io.run(); });

        t.join();
    } catch(const std::exception& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
}