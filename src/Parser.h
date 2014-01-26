#ifndef PARSER_H_
#define PARSER_H_

#include <memory>

#include "Token.h"
#include "Tokenizer.h"

#include "Ast/AstNode.h"
#include "Ast/Statement.h"
#include "Ast/Expression.h"
#include "Ast/AttributeList.h"

namespace pidl
{
namespace ast
{
	class NamespaceStatement;
	class IntegerConstantExpression;
	class ConstantAssignment;
	class Enum;
	class Packet;
	class PacketFieldDefinition;
	class Type;
	class IdentifierExpression;
	class AttributeList;
	class AttributeValue;
	class TypeList;
	class ParameterizedType;
	class StringExpression;
	class BooleanExpression;
}
class Parser
{
public:
	Parser(std::unique_ptr<Tokenizer> tokenizer);
	~Parser() = default;

	std::unique_ptr<ast::AstNode> readNext();

	bool isEndOfStream() const {return m_endOfStream;}

protected:

	void getNextToken() {m_currentToken = m_tokenizer->nextToken();}
	void requireTokenType(Token::TokenType type, const char* error);
	void consumeToken(Token::TokenType type, const char* error);

	void replaceTypeString(Token::TokenType type, int index, std::string& replaceString);

	void raiseError(const std::string& string);

	bool checkEndOfStream();

	std::unique_ptr<ast::AstNode> readStatement();

	std::unique_ptr<ast::NamespaceStatement> readNamespace();
	std::unique_ptr<ast::ConstantAssignment> readConstantAssignment();
	std::unique_ptr<ast::Enum> readEnum();
	std::unique_ptr<ast::Packet> readPacket();
	std::unique_ptr<ast::PacketFieldDefinition> readPacketFieldDefinition();
	std::unique_ptr<ast::AttributeList> readAttributeList();
	std::unique_ptr<ast::AttributeValue> readAttributeValue();

	std::unique_ptr<ast::Type> readType();
	std::unique_ptr<ast::TypeList> readTypeList();

	std::unique_ptr<ast::Expression> readExpression();
	std::unique_ptr<ast::IntegerConstantExpression> readIntegerConstant();
	std::unique_ptr<ast::StringExpression> readStringExpression();
	std::unique_ptr<ast::BooleanExpression> readBooleanExpression();
	std::unique_ptr<ast::IdentifierExpression> readIdentifierExpression();


	std::string m_file;

	std::unique_ptr<Tokenizer> m_tokenizer;
	Token m_currentToken;

	std::unique_ptr<ast::AttributeList> m_prefixAttributeList = nullptr;

	bool m_endOfStream = false;
};

}

#endif
