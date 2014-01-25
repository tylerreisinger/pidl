add_executable(tokenizer_test testTokenizer.cpp ${PARSER_SOURCES})

set_target_properties(tokenizer_test PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY_DEBUG "${TESTING_BIN_DIR}/debug"
	RUNTIME_OUTPUT_DIRECTORY "${TESTING_BIN_DIR}/release")
	
set_target_properties(tokenizer_test PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY_DEBUG "${TESTING_BIN_DIR}/debug"
	RUNTIME_OUTPUT_DIRECTORY "${TESTING_BIN_DIR}/release")