cmake_minimum_required(VERSION 3.15)
project(dcc_core_test)

find_package(GTest CONFIG REQUIRED)

# Add all .cpp files in this directory as test sources
file(GLOB TEST_SOURCES *.cpp)
add_executable(dcc_core_test ${TEST_SOURCES})

target_include_directories(dcc_core_test PRIVATE
    ${CMAKE_SOURCE_DIR}/cpp/include
)

target_link_libraries(dcc_core_test PRIVATE
    dcc_core
    GTest::gtest
    GTest::gtest_main
    # GTest::gmock 
    # GTest::gmock_main
)

add_test(NAME dcc_core_test COMMAND dcc_core_test)