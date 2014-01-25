#include "Token.h"

namespace pidl
{

Token::Token(TokenType type):
	m_type(type)
{
}

Token::Token(TokenType type, const std::string& string):
	m_type(type), m_string(string)
{

}

Token::Token(TokenType type, std::string&& string):
	m_type(type), m_string(std::move(string))
{
}

Token::Token(TokenType type, int startCol, int endCol, int startLine, int endLine):
	m_type(type),
	m_startLine(startLine), m_endLine(endLine), m_startCol(startCol), m_endCol(endCol)
{
}

Token::Token(TokenType type, const std::string& string, int startCol, int endCol, int startLine, int endLine):
	m_type(type), m_string(string),
	m_startLine(startLine), m_endLine(endLine), m_startCol(startCol), m_endCol(endCol)
{
}

Token::Token(TokenType type, std::string&& string, int startCol, int endCol, int startLine, int endLine):
	m_type(type), m_string(std::move(string)),
	m_startLine(startLine), m_endLine(endLine), m_startCol(startCol), m_endCol(endCol)
{
}


Token::Token(const Token& other):
	m_type(other.m_type), m_string(other.m_string),
	m_startLine(other.m_startLine), m_endLine(other.m_endLine), m_startCol(other.m_startCol), m_endCol(other.m_endCol)
{
}

Token::Token(Token&& other): Token()
{
	swap(*this, other);
}

Token& Token::operator =(const Token& other)
{
	m_type = other.m_type;
	m_string = other.m_string;
	m_startCol = other.m_startCol;
	m_endCol = other.m_endCol;
	m_startLine = other.m_startLine;
	m_endLine = other.m_endLine;
	return *this;
}

Token& Token::operator =(Token&& other)
{
	m_type = other.m_type;
	m_string = std::move(other.m_string);
	m_startCol = other.m_startCol;
	m_endCol = other.m_endCol;
	m_startLine = other.m_startLine;
	m_endLine = other.m_endLine;
	return *this;
}

void swap(Token& token1, Token& token2)
{
	using std::swap;
	swap(token1.m_type, token2.m_type);
	swap(token1.m_string, token2.m_string);
	swap(token1.m_startCol, token2.m_startCol);
	swap(token1.m_endCol, token2.m_endCol);
	swap(token1.m_startLine, token2.m_startLine);
	swap(token1.m_endLine, token2.m_endLine);
}

std::ostream& operator <<(std::ostream& os, Token::TokenType tokenType)
{
	switch(tokenType)
	{
	case Token::TokenType::None:
	{
		os << "None";
		break;
	}
	case Token::TokenType::Number:
	{
		os << "Number";
		break;
	}
	case Token::TokenType::HexNumber:
	{
		os << "Hex Number";
		break;
	}
	case Token::TokenType::String:
	{
		os << "String";
		break;
	}
	case Token::TokenType::Comment:
	{
		os << "Comment";
		break;
	}
	case Token::TokenType::Identifier:
	{
		os << "Identifier";
		break;
	}
	case Token::TokenType::OpenDelimiter:
	{
		os << "Open Delimiter";
		break;
	}
	case Token::TokenType::CloseDelimiter:
	{
		os << "Close Delimiter";
		break;
	}
	default:
	{
		os << "Unknown";
		break;
	}
	}
	return os;
}

std::ostream& operator <<(std::ostream& os, const Token& token)
{
	os << token.type();
#ifndef NDEBUG
	os << " (" << token.startLine() << ":" << token.startColumn() << " - " <<
			token.endLine() << ":" << token.endColumn() << ") ";
#endif
	if(!token.m_string.empty())
	{
		os << ": " << token.m_string;
	}
	return os;
}

}
