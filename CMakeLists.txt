cmake_minimum_required(VERSION 2.8)
project(LabyrinthGame CXX)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
include_directories("src")

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
	list(APPEND CMAKE_CXX_FLAGS "-std=c++11")
endif()

set(BUILD_TEST_PROGRAMS 1)

set(CMAKE_BUILD_TYPE DEBUG)

add_executable(pidl_generator ${PARSER_MAIN} ${PARSER_SOURCES})

set(PROJECT_BIN_DIR "${CMAKE_BINARY_DIR}/bin")

if(DEFINED BUILD_TEST_PROGRAMS)
	message("Building test binaries")
	add_subdirectory(${PROJECT_SOURCE_DIR}/test)
endif()

set_target_properties(pidl_generator PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_BIN_DIR}/debug"
	RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BIN_DIR}/release")
	
set_target_properties(pidl_generator PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_BIN_DIR}/debug"
	RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BIN_DIR}/release")