add_executable(parser_test testParser.cpp ${PARSER_SOURCES})

set_target_properties(parser_test PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY_DEBUG "${TESTING_BIN_DIR}/debug"
	RUNTIME_OUTPUT_DIRECTORY "${TESTING_BIN_DIR}/release")
	
set_target_properties(parser_test PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY_DEBUG "${TESTING_BIN_DIR}/debug"
	RUNTIME_OUTPUT_DIRECTORY "${TESTING_BIN_DIR}/release")