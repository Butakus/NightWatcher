cmake_minimum_required (VERSION 2.8)

project (OpenCVTests)

find_package (OpenCV REQUIRED)

# Use C++11 standard
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/")
add_definitions (-DROOT_PATH=${CMAKE_SOURCE_DIR})

file (GLOB_RECURSE SRC_FILES src/*.cpp tests/*.cpp)

foreach (src_file ${SRC_FILES})
	MESSAGE (STATUS "Processing file: ${src_file}")
	get_filename_component (exec_name ${src_file} NAME_WE)
	add_executable (${exec_name} ${src_file})
	MESSAGE (STATUS "Exec file: bin/${exec_name}")
	target_link_libraries (${exec_name} ${OpenCV_LIBS})
endforeach (src_file ${SRC_FILES})
