cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project (ComputationalGeometry)
find_package( OpenCV REQUIRED )

include_directories(include)

add_compile_options(-std=c++11)

add_executable(ComputationalGeometry
	src/main.cpp
	include/geo_convex_hull.hpp
	include/geo_intersection.hpp
	include/geo_triangulation.hpp
	include/geo_dcel.hpp
	include/geo_status.hpp
	include/geo_type.hpp)


target_link_libraries( ComputationalGeometry ${OpenCV_LIBS} )
# target_compile_features( ComputationalGeometry PRIVATE cxx_range_for)