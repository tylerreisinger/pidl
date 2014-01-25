add_executable(tokenizer_unittest tokenizer.cpp ${PARSER_SOURCES})

target_link_libraries(tokenizer_unittest gtest)

set_target_properties(tokenizer_unittest PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY_DEBUG "${TESTING_BIN_DIR}/debug"
	RUNTIME_OUTPUT_DIRECTORY "${TESTING_BIN_DIR}/release")
	
set_target_properties(tokenizer_unittest PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY_DEBUG "${TESTING_BIN_DIR}/debug"
	RUNTIME_OUTPUT_DIRECTORY "${TESTING_BIN_DIR}/release")