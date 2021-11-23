cmake_minimum_required(VERSION 3.0.2)
project(opencv_samples)

find_package(OpenCV REQUIRED)
find_package(catkin REQUIRED)

catkin_package(
)

include_directories(
 include
 ${OpenCV_INCLUDE_DIRS} 
)

add_executable(mat src/mat.cpp)
target_link_libraries(mat
  ${OpenCV_LIBRARIES}
)

add_executable(info src/info.cpp)
target_link_libraries(info
  ${OpenCV_LIBRARIES}
)

add_executable(sobel src/sobel.cpp)
target_link_libraries(sobel
  ${OpenCV_LIBRARIES}
)

add_executable(sobel1 src/sobel1.cpp)
target_link_libraries(sobel1
  ${OpenCV_LIBRARIES}
)
