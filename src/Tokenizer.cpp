#include "Tokenizer.h"

#include <cstring>

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
	skipWhitespace();
	checkEndOfStream();

	if(endOfInput())
	{
		return Token(Token::TokenType::None);
	}

	if(isDigit(currentCharacter()))
	{
		return readNumber();
	}
	if(currentCharacter() == '"')
	{
		return readString();
	}
	if(currentCharacter() == '/')
	{
		if(peekNextCharacter() == '/')
		{
			advanceInput(2);
			return readLineComment();
		}
		else if(peekNextCharacter() == '*')
		{
			advanceInput(2);
			return readBlockComment();
		}
	}
	if(isValidLeadingIdentifierCharacter(currentCharacter()))
	{
		return readIdentifier();
	}

	auto sym = readSymbol();
	if(sym.is_initialized())
	{
		return sym.get();
	}

	throw TokenizerError(std::string("Unexpected character '") + currentCharacter() +
			std::string("' encountered"), m_file, currentLine(), currentColumn());
}

bool Tokenizer::isDigit(char character) const
{
	return character >= '0' && character <= '9';
}

bool Tokenizer::isHexDigit(char character) const
{
	return (character >= '0' && character <= '9') || (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f');
}


void Tokenizer::skipWhitespace()
{
	while(currentCharacter() <= 32 && currentCharacter() != 0)
	{
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
		advanceInput();
		return readHexNumber();
	}
	return readDecimalNumber();
}

Token Tokenizer::readDecimalNumber()
{
	int startCol = currentColumn();
	while(isDigit(currentCharacter()))
	{
		storeCharacterAndGetNext();
	}
	if(m_currentToken.empty())
	{
		throw TokenizerError("Null hexadecimal literal encountered", m_file, m_line, m_col);
	}
	Token token(Token::TokenType::Number, std::move(m_currentToken), startCol,
			currentColumn() - 1, currentLine(), currentLine());
	m_currentToken.clear();
	return token;
}

Token Tokenizer::readHexNumber()
{
	int startCol = currentColumn();
	while(isHexDigit(currentCharacter()))
	{
		storeCharacterAndGetNext();
	}
	Token token(Token::TokenType::HexNumber, std::move(m_currentToken), startCol - 2,
			currentColumn() - 1, currentLine(), currentLine());
	m_currentToken.clear();
	return token;
}

void Tokenizer::checkInvalidEndOfStream(const char* errorMessage)
{
	if(checkEndOfStream())
	{
		throw TokenizerError(errorMessage, m_file, m_line, m_col);
	}
}

void Tokenizer::handleEscapeString()
{
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

bool Tokenizer::lookaheadEq(const char* str, int count)
{
	return std::strcmp(str, m_sourcePtr) == 0;
}

Token Tokenizer::readString()
{
	int startCol = currentColumn();
	int startLine = currentLine();
	advanceInput();
	while(currentCharacter() != '"')
	{
		checkInvalidEndOfStream("Unexpected end of stream found while looking for terminating '\"'");
		//Handle escape sequences
		if(currentCharacter() == '\\')
		{
			advanceInput();
			handleEscapeString();
		}
		storeCharacterAndGetNext();
	}
	advanceInput();
	Token token(Token::TokenType::String, std::move(m_currentToken),
			startCol, currentColumn() - 1, startLine, currentLine());
	m_currentToken.clear();
	return token;
}

Token Tokenizer::readLineComment()
{
	int startCol = currentColumn();
	int startLine = currentLine();
	while(!isNewline(currentCharacter()) && !checkEndOfStream())
	{
		storeCharacterAndGetNext();
	}
	Token token(Token::TokenType::Comment, std::move(m_currentToken),
				startCol - 2, currentColumn() - 1, startLine, startLine);
	m_currentToken.clear();
	return token;
}



Token Tokenizer::readBlockComment()
{
	int startCol = currentColumn();
	int startLine = currentLine();
	while(currentCharacter() != '*' && peekNextCharacter() != '/')
	{
		checkInvalidEndOfStream("Unexpected end of stream found while looking for end of block comment");
		storeCharacterAndGetNext();
	}
	advanceInput(2);
	Token token(Token::TokenType::Comment, std::move(m_currentToken),
			startCol - 2, currentColumn() - 1, startLine, currentLine());
	m_currentToken.clear();
	return token;
}

bool Tokenizer::isValidLeadingIdentifierCharacter(char character)
{
	return character == '_' ||
			(character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z');
}

bool Tokenizer::isValidIdentifierCharacter(char character)
{
	return isValidLeadingIdentifierCharacter(character) || (character >= '0' && character <= '9');
}

Token Tokenizer::readIdentifier()
{
	int startCol = currentColumn();
	if(isValidLeadingIdentifierCharacter(currentCharacter()))
	{
		storeCharacterAndGetNext();
	}
	while(isValidIdentifierCharacter(currentCharacter()))
	{
		storeCharacterAndGetNext();
	}
	Token token(Token::TokenType::Identifier, std::move(m_currentToken),
			startCol, currentColumn() - 1, currentLine(), currentLine());
	m_currentToken.clear();
	return token;
}

Token Tokenizer::readKeyword()
{
}

boost::optional<Token> Tokenizer::readSymbol()
{
	switch(currentCharacter())
	{
	case '(':
	case '[':
	case '{':
	case '<':
	{
		storeCharacterAndGetNext();
		Token token(Token::TokenType::OpenDelimiter, std::move(m_currentToken),
				currentColumn() - 1, currentColumn() - 1, currentLine(), currentLine());
		m_currentToken.clear();
		return token;
	}
	case ')':
	case ']':
	case '}':
	case '>':
	{
		storeCharacterAndGetNext();
		Token token(Token::TokenType::CloseDelimiter, std::move(m_currentToken),
				currentColumn() - 1, currentColumn() - 1, currentLine(), currentLine());
		m_currentToken.clear();
		return token;
	}
	default:
	{
		return boost::optional<Token>();
		break;
	}
	}
}

}
