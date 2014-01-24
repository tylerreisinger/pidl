#include "Tokenizer.h"

#include "Exceptions/TokenizerError.h"

namespace pidl
{

Tokenizer::Tokenizer(const std::string& source):
	m_source(source)
{
	m_sourcePtr = m_source.data();
}

Tokenizer::Tokenizer(std::string&& source):
	m_source(std::move(source))
{
	m_sourcePtr = m_source.data();
}

Tokenizer::~Tokenizer()
{
}

Token Tokenizer::nextToken()
{
	if(endOfInput())
	{
		return Token(Token::TokenType::EndOfInput);
	}

	if(isDigit(currentCharacter()))
	{
		return readNumber();
	}

	return Token();
}

bool Tokenizer::isDigit(char character)
{
	std::isdigit(character);
}

Token Tokenizer::readNumber()
{
	bool isHex = false;
	//Hex numbers start with '0x'. It is not invalid for a decimal number to start with leading zeros otherwise.
	if(currentCharacter() == '0' && getNextCharacter() == 'x')
	{
		isHex = true;
		advanceInput();
	}
	while(isDigit(currentCharacter()))
	{
		m_currentToken.append(1, currentCharacter());
		advanceInput();
	}
	Token token;
	if(isHex)
	{
		//'0x' is an invalid number
		if(m_currentToken.empty())
		{
			throw TokenizerError("Null hexadecimal literal encountered", m_file, m_line, m_col);
		}
		token = Token(Token::TokenType::HexNumber, std::move(m_currentToken));
	}
	else
	{
		token = Token(Token::TokenType::Number, std::move(m_currentToken));
	}
	m_currentToken.clear();
	return token;
}

}
