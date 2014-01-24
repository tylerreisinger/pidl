cmake_minimum_required(VERSION 2.8)
project(LabyrinthGame CXX)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
include_directories("src")

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
	list(APPEND CMAKE_CXX_FLAGS "-std=c++11")
endif()

add_executable(pidl_generator ${GENERATOR_SOURCES})

set(PROJECT_BIN_DIR "${CMAKE_BINARY_DIR}/bin")

set_target_properties(pidl_generator PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_BIN_DIR}/debug"
	RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BIN_DIR}/release")
	
set_target_properties(pidl_generator PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_BIN_DIR}/debug"
	RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BIN_DIR}/release")