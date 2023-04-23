cmake_minimum_required(VERSION 3.20)
project(coffee-tests LANGUAGES CXX)

# # Add test executable target
set(coffee_TEST_SRC
    LevelTests.cpp
)

add_executable(coffee-test ${coffee_TEST_SRC})

target_link_libraries(coffee-test
    coffee
    gtest_main
)

GTEST_ADD_TESTS(coffee-test "" ${coffee_TEST_SRC})
