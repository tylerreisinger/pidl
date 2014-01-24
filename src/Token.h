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
		OperatorPlus
	};


	Token(TokenType type, const std::string& string);
	Token(TokenType type, std::string&& string);
	~Token();

	const std::string& string() const;
	TokenType type() const;

protected:
	TokenType m_type;
	std::string m_string;
};

}

#endif /* TOKEN_H_ */
