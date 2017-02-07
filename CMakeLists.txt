cmake_minimum_required(VERSION 3.2)
project(ComputionalGeometry)

find_package( OpenCV REQUIRED )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    include/geo_convex_hull.hpp
    include/geo_dcel.hpp
    include/geo_intersection.hpp
    include/geo_status.hpp
    include/geo_triangulation.hpp
    include/geo_type.hpp
    src/main.cpp)

include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( include )

add_executable(ComputionalGeometry ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(ComputionalGeometry ${OpenCV_LIBS} )