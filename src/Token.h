/*
 * Token.h
 *
 *  Created on: Jan 24, 2014
 *      Author: tyler
 */

#ifndef TOKEN_H_
#define TOKEN_H_

#include <string>

namespace pidl
{

class Token
{
public:

	enum class TokenType
	{
		None,
		OperatorPlus
	};


	Token(TokenType type, const std::string& string);
	Token(TokenType type, std::string&& string);
	~Token() = default;

	Token(const Token& other);
	Token(Token&& other);
	Token& operator =(Token other);
	Token& operator =(Token&& other);

	const std::string& string() const {return m_string;}
	TokenType type() const {return m_type;}

	friend void swap(Token& token1, Token& token2);

protected:
	Token() = default;

	TokenType m_type = TokenType::None;
	std::string m_string;
};

}

#endif /* TOKEN_H_ */
