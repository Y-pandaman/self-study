project(stitch_test)
cmake_minimum_required(VERSION 3.5)
find_package(OpenCV REQUIRED)
include_directories(${OPENCV_INCLUDE_DIR})

add_executable(stitch_test src/stitch_test.cpp)
target_link_libraries(stitch_test ${OpenCV_LIBRARIES})
