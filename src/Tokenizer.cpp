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

	if(isEndOfInput())
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

	Token symbolToken;
	if(readSymbol(symbolToken))
	{
		return symbolToken;
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
	bool foundDot = false;
	while(isDigit(currentCharacter()) || currentCharacter() == '.')
	{
		storeCharacterAndGetNext();
		if(currentCharacter() == '.')
		{
			if(foundDot)
			{
				throw TokenizerError("Multiple radix points found in one number", m_file, m_line, m_col);
			}
			foundDot = true;
		}
	}
	Token token;
	if(foundDot)
	{
		token = Token(Token::TokenType::FloatNumber, std::move(m_currentToken), startCol,
					currentColumn() - 1, currentLine(), currentLine());
	}
	else
	{
		token = Token(Token::TokenType::Number, std::move(m_currentToken), startCol,
					currentColumn() - 1, currentLine(), currentLine());
	}
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
	if(m_currentToken.empty())
	{
		throw TokenizerError("Null hexadecimal literal encountered", m_file, m_line, m_col);
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

	Token token;
	if(!makeKeyword(m_currentToken, currentLine(), startCol, token))
	{
		token = Token(Token::TokenType::Identifier, std::move(m_currentToken),
				startCol, currentColumn() - 1, currentLine(), currentLine());
	}
	m_currentToken.clear();
	return token;
}

bool Tokenizer::makeKeyword(const std::string& name, int line, int startCol, Token& outToken)
{
	Token::TokenType type = Token::TokenType::None;
	//Compare character by character instead of doing a bunch of string comparisons
	//as it should be considerably faster and scale upward without much extra overhead.
	switch(name[0])
	{
	case 'c':
	{
		if(name == "constant")
		{
			type = Token::TokenType::KeywordConstant;
		}
		break;
	}
	case 'e':
	{
		if(name == "enum")
		{
			type = Token::TokenType::KeywordEnum;
		}
		break;
	}
	case 'f':
	{
		if(name == "false")
		{
			type = Token::TokenType::KeywordFalse;
		}
		break;
	}
	case 'n':
	{
		if(name == "namespace")
		{
			type = Token::TokenType::KeywordNamespace;
		}
		break;
	}
	case 'o':
	{
		if(name == "opt")
		{
			type = Token::TokenType::KeywordOptional;
		}
		break;
	}
	case 'p':
	{
		if(name == "packet")
		{
			type = Token::TokenType::KeywordPacket;
		}
		break;
	}
	case 'r':
	{
		if(name == "req")
		{
			type = Token::TokenType::KeywordRequired;
		}
		break;
	}
	case 't':
	{
		if(name == "true")
		{
			type = Token::TokenType::KeywordTrue;
		}
		break;
	}
	}
	if(type != Token::TokenType::None)
	{
		outToken = Token(type, startCol, startCol + name.size(), line, line);
		return true;
	}
	return false;
}

bool Tokenizer::readSymbol(Token& outToken)
{
	switch(currentCharacter())
	{
	case '{':
	{
		outToken = makeSingleCharSymbol(Token::TokenType::SymOpenBrace);
		break;
	}
	case '}':
	{
		outToken = makeSingleCharSymbol(Token::TokenType::SymCloseBrace);
		break;
	}
	case '[':
	{
		outToken = makeSingleCharSymbol(Token::TokenType::SymOpenSqBracket);
		break;
	}
	case ']':
	{
		outToken = makeSingleCharSymbol(Token::TokenType::SymCloseSqBracket);
		break;
	}
	case '<':
	{
		outToken = makeSingleCharSymbol(Token::TokenType::SymOpenAngBracket);
		break;
	}
	case '>':
	{
		outToken = makeSingleCharSymbol(Token::TokenType::SymCloseAngBracket);
		break;
	}
	case '.':
	{
		outToken = makeSingleCharSymbol(Token::TokenType::ScopeResolution);
		break;
	}
	case ',':
	{
		outToken = makeSingleCharSymbol(Token::TokenType::SymComma);
		break;
	}
	case ':':
	{
		outToken = makeSingleCharSymbol(Token::TokenType::SymColon);
		break;
	}
	case '=':
	{
		outToken = makeSingleCharSymbol(Token::TokenType::SymEquals);
		break;
	}
	case '+':
	{
		outToken = makeSingleCharSymbol(Token::TokenType::SymAdd);
		break;
	}
	case '-':
	{
		outToken = makeSingleCharSymbol(Token::TokenType::SymSub);
		break;
	}
	case '*':
	{
		outToken = makeSingleCharSymbol(Token::TokenType::SymMul);
		break;
	}
	case '/':
	{
		outToken = makeSingleCharSymbol(Token::TokenType::SymDiv);
		break;
	}
	default:
	{
		return false;
	}
	}
	return true;
}

Token Tokenizer::makeSingleCharSymbol(Token::TokenType type)
{
	advanceInput();
	return Token(type,
		currentColumn() - 1, currentColumn() - 1, currentLine(), currentLine());
}

}
