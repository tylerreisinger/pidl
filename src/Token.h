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

		Comment,

		Identifier,

		OpenDelimiter,
		CloseDelimiter,

		OperatorPlus
	};

	Token() = default;
	Token(TokenType type);
	Token(TokenType type, int startCol, int endCol, int startLine, int endLine);
	Token(TokenType type, const std::string& string);
	Token(TokenType type, std::string&& string);
	Token(TokenType type, const std::string& string, int startCol, int endCol, int startLine, int endLine);
	Token(TokenType type, std::string&& string, int startCol, int endCol, int startLine, int endLine);
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

	int startLine() const {return m_startLine;}
	int endLine() const {return m_endLine;}
	int startColumn() const {return m_startCol;}
	int endColumn() const {return m_endCol;}

	friend std::ostream& operator <<(std::ostream& os, TokenType tokenType);
	friend std::ostream& operator <<(std::ostream& os, const Token& token);

	friend void swap(Token& token1, Token& token2);

protected:

	TokenType m_type = TokenType::None;
	std::string m_string;

	int m_startLine = 0;
	int m_endLine = 0;
	int m_startCol = 0;
	int m_endCol = 0;
};

}

#endif
