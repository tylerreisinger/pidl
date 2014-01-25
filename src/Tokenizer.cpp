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
	checkEndOfStream();

	if(endOfInput())
	{
		return Token(Token::TokenType::None);
	}

	skipWhitespace();

	if(isDigit(currentCharacter()))
	{
		return readNumber();
	}
	if(currentCharacter() == '"')
	{
		return readString();
	}

	return Token();
}

bool Tokenizer::isDigit(char character) const
{
	return character >= '0' && character <= '9';
}

void Tokenizer::skipWhitespace()
{
	while(currentCharacter() <= 32 && currentCharacter() != 0)
	{
		//Go to the next line
		if(currentCharacter() == '\n')
		{
			m_line += 1;
			m_col = 1;
		}
		advanceInput();
	}
}

bool Tokenizer::checkEndOfStream()
{
	if(currentCharacter() == '\0')
	{
		m_endOfInput = true;
	}
	return m_endOfInput;
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
		storeCharacterAndGetNext();
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

void Tokenizer::checkInvalidEndOfStream(const std::string& errorMessage)
{
	if(checkEndOfStream())
	{
		throw TokenizerError(errorMessage, m_file, m_line, m_col);
	}
}

Token Tokenizer::readString()
{
	advanceInput();
	while(currentCharacter() != '"')
	{
		checkInvalidEndOfStream("Unexpected end of stream found while looking for terminating '\"'");
		//Handle escape sequences
		if(currentCharacter() == '\\')
		{
			advanceInput();
			switch(currentCharacter())
			{
			//Treat it as a normal character
			case '\\':
			{
				break;
			}
			case 'n':
			{
				m_currentToken.append(1, '\n');
				advanceInput();
				break;
			}
			case 't':
			{
				m_currentToken.append(1, '\t');
				advanceInput();
				break;
			}
			default:
			{
				throw TokenizerError("Invalid escape sequence", m_file, m_line, m_col);
			}
			}
		}
		storeCharacterAndGetNext();
	}
	advanceInput();
	Token token(Token::TokenType::String, std::move(m_currentToken));
	m_currentToken.clear();
	return token;
}

}
