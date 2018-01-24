cmake_minimum_required(VERSION 2.8)
project( app_soft )
find_package( OpenCV REQUIRED )
add_executable( app_soft app_soft.cpp )
target_link_libraries( app_soft ${OpenCV_LIBS} )

