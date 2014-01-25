#ifndef TOKEN_H_
#define TOKEN_H_

#include <string>

#include <ostream>

namespace pidl
{

class Token
{
public:

	enum class TokenType
	{
		None,

		Number,
		HexNumber,

		String,

		OperatorPlus
	};

	Token() = default;
	Token(TokenType type);
	Token(TokenType type, const std::string& string);
	Token(TokenType type, std::string&& string);
	~Token() = default;

	Token(const Token& other);
	Token(Token&& other);
	Token& operator =(const Token& other);
	Token& operator =(Token&& other);

	const std::string& string() const {return m_string;}
	TokenType type() const {return m_type;}

	//Category functions

	bool isNumber() const {return m_type == TokenType::Number || m_type == TokenType::HexNumber;}
	bool isString() const {return m_type == TokenType::String;}

	friend std::ostream& operator <<(std::ostream& os, TokenType tokenType);
	friend std::ostream& operator <<(std::ostream& os, const Token& token);

	friend void swap(Token& token1, Token& token2);

protected:

	TokenType m_type = TokenType::None;
	std::string m_string;
};

}

#endif
