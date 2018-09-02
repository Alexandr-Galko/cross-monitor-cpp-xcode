#include "application.hpp"
#include <gmock/gmock.h>
#include <stdexcept>
using namespace testing;

// Unit test to test 0 Minutes arguments.
TEST(ArgumentTest, MinuteArgumentShouldNotBeZero) {
    using std::chrono::minutes;
    using crossover::monitor::client::application;
    try{
        application a{minutes(0)};
        FAIL();
    }
    catch(const std::invalid_argument & expected) {}
    
}
int main( int argc, char *argv[] ) {
    ::testing::InitGoogleMock( &argc, argv );
    return RUN_ALL_TESTS( );
}
