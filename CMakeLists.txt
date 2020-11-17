cmake_minimum_required (VERSION 3.1)
project(DescribeInstances)

set(CMAKE_CXX_STANDARD 11)

add_executable(test test.cpp)
target_link_libraries(test tencentcloud-sdk-cpp-cvm tencentcloud-sdk-cpp-core tencentcloud-sdk-cpp-sms) 
