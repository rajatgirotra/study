#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "common/Singleton.hpp"
using namespace cs::common;
using std::string;
using namespace std;
/*
 * Any environment settings will go here
 */
namespace {
    class SingletonTestEnvironment : public ::testing::Environment {
    private:
        string name;
    public:
        SingletonTestEnvironment() : ::testing::Environment(), name("SingletonTest") {}

        void SetUp() override;

        void TearDown() override;
    };

    void SingletonTestEnvironment::SetUp() {
        cout << "Setting up SingletonTest environment\n";
    }

    void SingletonTestEnvironment::TearDown() {
        cout << "Tearing down SingletonTest environment\n";
    }

    class SingletonTestSuite : public ::testing::Test {
    public:
        void SetUp() override;
        void TearDown() override;

        static void SetUpTestSuite();
        static void TearDownTestSuite();
    };

    void SingletonTestSuite::SetUpTestSuite()  {
        cout << "Setting up SingletonTestSuite\n";
    }
    void SingletonTestSuite::TearDownTestSuite()  {
        cout << "Tearing down SingletonTestSuite\n";
    }

    void SingletonTestSuite::SetUp() {
        cout << "Setup test case\n";
    }

    void SingletonTestSuite::TearDown() {
        cout << "Tear down test case\n";
    }
}

TEST_F(SingletonTestSuite, SingletonTest1) {
    ASSERT_TRUE(true);
}

TEST_F(SingletonTestSuite, SingletonTest2) {
    ASSERT_TRUE(true);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
   [[maybe_unused]] auto test_environment = ::testing::AddGlobalTestEnvironment(new SingletonTestEnvironment);

    return RUN_ALL_TESTS();
}

