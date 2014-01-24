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

Token::~Token()
{

}

}
