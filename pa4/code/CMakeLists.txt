cmake_minimum_required(VERSION 3.10)
project(BezierCurve)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(OpenCV_DIR "/home/fsreed/opencv-4.12.0/build")
find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_executable(BezierCurve main.cpp)

target_link_libraries(BezierCurve ${OpenCV_LIBRARIES})
