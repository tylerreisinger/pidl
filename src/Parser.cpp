#include "Parser.h"

#include "Tokenizer.h"
#include "Ast/NamespaceStatement.h"
#include "Ast/IntegerConstantExpression.h"
#include "Ast/ConstantAssignment.h"
#include "Ast/Constant.h"
#include "Ast/Enum.h"
#include "Ast/Packet.h"
#include "Ast/PacketFieldDefinition.h"
#include "Ast/SimpleType.h"
#include "Ast/IdentifierExpression.h"
#include "Exceptions/ParserError.h"

#include "make_unique.h"

#include <sstream>

namespace pidl
{

Parser::Parser(std::unique_ptr<Tokenizer> tokenizer):
	m_tokenizer(std::move(tokenizer))
{
	getNextToken();
}

std::unique_ptr<ast::AstNode> Parser::readNext()
{
	return readStatement();
}

std::unique_ptr<ast::AstNode> Parser::readStatement()
{
	if(checkEndOfStream())
	{
		return nullptr;
	}

	switch(m_currentToken.type())
	{
	case Token::TokenType::KeywordNamespace:
	{
		return readNamespace();
	}
	case Token::TokenType::KeywordConstant:
	{
		getNextToken();
		return readConstantAssignment();
	}
	case Token::TokenType::KeywordEnum:
	{
		getNextToken();
		return readEnum();
	}
	case Token::TokenType::KeywordPacket:
	{
		getNextToken();
		return readPacket();
	}
	default:
	{
		break;
	}
	}

	std::string errorString("Unexpected token '{0}' found when looking for statement");
	replaceTypeString(m_currentToken.type(), 0, errorString);
	raiseError(errorString);
	return nullptr;
}

bool Parser::checkEndOfStream()
{
	if(m_currentToken.type() == Token::TokenType::None)
	{
		m_endOfStream = true;
	}
	return m_endOfStream;
}

void Parser::requireTokenType(Token::TokenType type, const char* error)
{
	if(m_currentToken.type() != type)
	{
		std::string errorStr = error;
		replaceTypeString(type, 1, errorStr);
		replaceTypeString(m_currentToken.type(), 0, errorStr);
		throw ParserError(errorStr, m_file, m_currentToken.startLine(), m_currentToken.startColumn());
	}
}

void Parser::consumeToken(Token::TokenType type, const char* error)
{
	requireTokenType(type, error);
	getNextToken();
}

void Parser::replaceTypeString(Token::TokenType type, int index,
		std::string& replaceString)
{
	std::ostringstream escapeStr;
	escapeStr << "{" << index << "}";
	std::ostringstream typeStr;
	typeStr << type;
	size_t replaceIndex = replaceString.find(escapeStr.str());
	while(replaceIndex != std::string::npos)
	{
		replaceString.replace(replaceIndex, escapeStr.str().size(), typeStr.str());
		replaceIndex = replaceString.find(escapeStr.str());
	}
}

void Parser::raiseError(const std::string& string)
{
	std::string errorString = string;
	replaceTypeString(m_currentToken.type(), 0, errorString);
	throw ParserError(errorString, m_file, m_currentToken.startLine(), m_currentToken.startColumn());
}

std::unique_ptr<ast::ConstantAssignment> Parser::readConstantAssignment()
{
	requireTokenType(Token::TokenType::Identifier, "Expected an identifier naming a constant but found a '{0}' instead");
	std::string name = m_currentToken.string();
	getNextToken();
	consumeToken(Token::TokenType::SymEquals, "In assignment, constant identifier must be followed by an equals sign");
	if(!m_currentToken.isNumber())
	{
		raiseError("Expected a number, but found a '{0}' instead");
	}
	auto value = readIntegerConstant();
	return make_unique<ast::ConstantAssignment>(make_unique<ast::Constant>(name), std::move(value));
}

std::unique_ptr<ast::NamespaceStatement> Parser::readNamespace()
{
	std::vector<std::string> path;
	do
	{
		getNextToken();
		requireTokenType(Token::TokenType::Identifier
				, "'namespace' must be followed by a series of identifiers designating a path");
		path.push_back(m_currentToken.string());
		getNextToken();
	}
	while(m_currentToken.type() == Token::TokenType::ScopeResolution);

	return make_unique<ast::NamespaceStatement>(std::move(path));

}

std::unique_ptr<ast::Enum> Parser::readEnum()
{
	requireTokenType(Token::TokenType::Identifier, "Expected an identifier naming an enum but found a '{1}' instead");
	std::string enumName = m_currentToken.string();
	getNextToken();
	consumeToken(Token::TokenType::SymOpenBrace, "enum declaration must be followed by '{'");
	auto enumObj = make_unique<ast::Enum>(enumName);
	while(true)
	{
		auto val = readConstantAssignment();
		enumObj->appendChild(std::move(val));
		if(m_currentToken.type() != Token::TokenType::SymComma)
		{
			break;
		}
		getNextToken();
	}
	consumeToken(Token::TokenType::SymCloseBrace, "Ending '}' expected for enum declaration.");
	return std::move(enumObj);
}

std::unique_ptr<ast::IntegerConstantExpression> Parser::readIntegerConstant()
{
	std::stringstream numStream;
	numStream << m_currentToken.string();
	int64_t value;
	if(m_currentToken.type() == Token::TokenType::Number)
	{
		numStream >> value;
	}
	else
	{
		numStream >> std::hex >> value;
	}
	getNextToken();
	return make_unique<ast::IntegerConstantExpression>(value);
}

std::unique_ptr<ast::Packet> Parser::readPacket()
{
	requireTokenType(Token::TokenType::Identifier, "Expected an identifier naming a packet but found a '{1}' instead");
	std::string packetName = m_currentToken.string();
	getNextToken();
	auto packetObj = make_unique<ast::Packet>(packetName);
	consumeToken(Token::TokenType::SymOpenBrace, "packet declaration must be followed by '{'");
	while(true)
	{
		auto fieldDef = readPacketFieldDefinition();
		packetObj->appendChild(std::move(fieldDef));
		if(m_currentToken.type() != Token::TokenType::SymComma)
		{
			break;
		}
		getNextToken();
	}
	consumeToken(Token::TokenType::SymCloseBrace, "Ending '}' expected for packet declaration.");
	return std::move(packetObj);
}

std::unique_ptr<ast::PacketFieldDefinition> Parser::readPacketFieldDefinition()
{
	bool required = true;
	if(m_currentToken.type() == Token::TokenType::KeywordOptional ||
			m_currentToken.type() == Token::TokenType::KeywordRequired)
	{
		required = m_currentToken.type() == Token::TokenType::KeywordRequired;
		getNextToken();
	}
	auto type = readType();
	requireTokenType(Token::TokenType::Identifier, "Expected an identifier naming a field but found a '{1}' instead");
	std::string fieldName = m_currentToken.string();
	getNextToken();
	consumeToken(Token::TokenType::SymColon, "Packet field requires an index specifier preceded by a colon");
	auto locationExpression = readExpression();
	return make_unique<ast::PacketFieldDefinition>(fieldName, std::move(type), std::move(locationExpression), required);
}

std::unique_ptr<ast::Type> Parser::readType()
{
	requireTokenType(Token::TokenType::Identifier, "Expected a type name but found a '{1}' instead");
	std::string name = m_currentToken.string();
	getNextToken();
	return make_unique<ast::SimpleType>(name);
}

std::unique_ptr<ast::Expression> Parser::readExpression()
{
	switch(m_currentToken.type())
	{
	case Token::TokenType::Number:
	case Token::TokenType::HexNumber:
	{
		return readIntegerConstant();
	}
	case Token::TokenType::Identifier:
	{
		return readIdentifierExpression();
	}
	default:
	{
		raiseError("Unexpected token '{0}' encountered when parsing expression");
		break;
	}
	}
	return nullptr;
}

std::unique_ptr<ast::IdentifierExpression> Parser::readIdentifierExpression()
{
	std::vector<std::string> namePath;
	while(true)
	{
		requireTokenType(Token::TokenType::Identifier, "Expected a qualified name but found a '{1}' instead");
		namePath.push_back(m_currentToken.string());
		getNextToken();
		if(m_currentToken.type() != Token::TokenType::ScopeResolution)
		{
			break;
		}
		getNextToken();
	}
	return make_unique<ast::IdentifierExpression>(std::move(namePath));
}


}
