/*
 * Token.cpp
 *
 *  Created on: Jan 24, 2014
 *      Author: tyler
 */

#include "Token.h"

namespace pidl
{

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

Token& Token::operator =(Token other)
{
	swap(*this, other);
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


}
