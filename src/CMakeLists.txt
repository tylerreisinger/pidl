set(PARSER_MAIN
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	PARENT_SCOPE)

set(PARSER_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/Parser.h
	${CMAKE_CURRENT_SOURCE_DIR}/Parser.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Token.h
	${CMAKE_CURRENT_SOURCE_DIR}/Token.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Tokenizer.h
	${CMAKE_CURRENT_SOURCE_DIR}/Tokenizer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/Addition.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/Addition.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/AstNode.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/AstNode.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/AttributeList.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/AttributeList.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/AttributeValue.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/AttributeValue.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/AstNode.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/AstNode.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/BooleanExpression.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/BooleanExpression.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/BinaryExpression.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/BinaryExpression.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/Constant.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/Constant.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/ConstantAssignment.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/ConstantAssignment.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/Division.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/Division.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/Enum.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/Enum.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/Expression.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/Expression.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/FloatExpression.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/FloatExpression.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/IdentifierExpression.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/IdentifierExpression.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/IntegerConstantExpression.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/IntegerConstantExpression.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/Multiplication.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/Multiplication.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/NamespaceStatement.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/NamespaceStatement.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/Negation.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/Negation.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/Packet.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/Packet.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/PacketFieldDefinition.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/PacketFieldDefinition.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/ParameterizedType.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/ParameterizedType.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/SimpleType.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/SimpleType.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/Statement.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/Statement.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/StringExpression.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/StringExpression.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/Subtraction.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/Subtraction.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/Type.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/Type.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/TypeList.h
	${CMAKE_CURRENT_SOURCE_DIR}/Ast/TypeList.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/ParserError.h
	${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/ParserError.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/PidlError.h
	${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/PidlError.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/TokenizerError.h
	${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/TokenizerError.cpp
	PARENT_SCOPE)