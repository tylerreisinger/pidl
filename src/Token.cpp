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

Token::Token(const Token& other):
	m_type(other.m_type), m_string(other.m_string)
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
	return *this;
}

Token& Token::operator =(Token&& other)
{
	m_type = other.m_type;
	m_string = std::move(other.m_string);
	return *this;
}

void swap(Token& token1, Token& token2)
{
	using std::swap;
	swap(token1.m_type, token2.m_type);
	swap(token2.m_string, token2.m_string);
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
	if(!token.m_string.empty())
	{
		os << ": " << token.m_string;
	}
	return os;
}

}
