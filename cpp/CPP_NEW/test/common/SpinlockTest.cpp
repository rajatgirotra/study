#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include "common/system/Spinlock.hpp"
using namespace cs::common;
using std::string;
using namespace std;
/*
 * Any environment settings will go here
 */
namespace {
    class SpinlockTestEnvironment : public ::testing::Environment {
    private:
        string name;
    public:
        SpinlockTestEnvironment() : ::testing::Environment(), name("SpinlockTest") {}

        void SetUp() override;

        void TearDown() override;
    };

    void SpinlockTestEnvironment::SetUp() {
        cout << "Setting up SpinlockTest environment\n";
    }

    void SpinlockTestEnvironment::TearDown() {
        cout << "Tearing down SpinlockTest environment\n";
    }

    class SpinlockTestSuite : public ::testing::Test {
    public:
        void SetUp() override;
        void TearDown() override;

        static void SetUpTestSuite();
        static void TearDownTestSuite();

        system::Spinlock m_lock;
    };

    void SpinlockTestSuite::SetUpTestSuite()  {
        cout << "Setting up SpinlockTestSuite\n";
    }
    void SpinlockTestSuite::TearDownTestSuite()  {
        cout << "Tearing down SpinlockTestSuite\n";
    }

    void SpinlockTestSuite::SetUp() {
        cout << "Setup test case\n";
    }

    void SpinlockTestSuite::TearDown() {
        cout << "Tear down test case\n";
    }
}

TEST_F(SpinlockTestSuite, SpinlockTest1) {
    int count = 0;
    std::vector<std::thread> threadVec{};
    for (int i = 0; i < 6; ++i) {
         threadVec.emplace_back([&count, this] () {
             while(true) {
                 std::lock_guard<system::Spinlock> _(m_lock);
                 if(count >= 100000000)
                     return;
                 count++;
             }
         });
    }
    for(auto&& t : threadVec) {
        t.join();
    }

    ASSERT_EQ(count, 100000000);
}

TEST_F(SpinlockTestSuite, SpinlockTest2) {
    ASSERT_TRUE(true);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
   [[maybe_unused]] auto test_environment = ::testing::AddGlobalTestEnvironment(new SpinlockTestEnvironment);

    return RUN_ALL_TESTS();
}

