cmake_minimum_required(VERSION 3.5)
project(my_aruco)

find_package(OpenCV REQUIRED)
include_directories(${OPENCV_INCLUDE_DIR})

add_executable(create_marker src/create_marker.cpp)
target_link_libraries(create_marker ${OpenCV_LIBRARIES})

add_executable(create_board src/create_board.cpp)
target_link_libraries(create_board ${OpenCV_LIBRARIES})

add_executable(detect_marker src/detect_marker.cpp)
target_link_libraries(detect_marker ${OpenCV_LIBRARIES})

add_executable(pose_estimation_marker src/pose_estimation_marker.cpp)
target_link_libraries(pose_estimation_marker ${OpenCV_LIBRARIES})

add_executable(pose_estimation_board src/pose_estimation_board.cpp)
target_link_libraries(pose_estimation_board ${OpenCV_LIBRARIES})

add_executable(draw_cube src/draw_cube.cpp)
target_link_libraries(draw_cube ${OpenCV_LIBRARIES})

add_executable(camera_calib src/camera_calib.cpp)
target_link_libraries(camera_calib ${OpenCV_LIBRARIES})