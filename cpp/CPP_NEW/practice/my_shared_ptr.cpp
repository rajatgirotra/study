#include "my_shared_ptr.hpp"
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

class SharedPtrTests : public ::testing::Test {
public:
    void SetUp() override;
    void TearDown() override;

    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void SharedPtrTests::SetUpTestSuite()  {
    cout << "Setting up SingletonTestSuite\n";
}
void SharedPtrTests::TearDownTestSuite()  {
    cout << "Tearing down SingletonTestSuite\n";
}

void SharedPtrTests::SetUp() {
    cout << "Setup test case\n";
}

void SharedPtrTests::TearDown() {
    cout << "Tear down test case\n";
}


TEST_F(SharedPtrTests, TestOne) {
    SharedPtr<int> x;
    ASSERT_TRUE(x.use_count() == 1);
    ASSERT_TRUE(x.unique());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}