#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include <string>
#include <utility>

#include "Token.h"

namespace pidl
{
///Lexical analyzer for pidl files.
///Converts the stream to a series of tokens for parsing.
class Tokenizer
{
public:
	Tokenizer(const std::string& source);
	Tokenizer(std::string&& source);
	~Tokenizer();

	///Extract the next token from the stream, advancing the stream as necessary
	Token nextToken();

	///Return if the end of the stream has been reached.
	bool isEndOfInput() const {return m_endOfInput;}

protected:

	///Advance the character stream one position and return the new current character.
	char getNextCharacter() {m_col++; return *(++m_sourcePtr);}
	///Advance the character stream one position.
	void advanceInput();
	///Advance the character stream @a n position.
	void advanceInput(int n);
	///Get the next character in the stream but do not advance.
	///@details It is an error to use this function when at the end of the stream.
	char peekNextCharacter() const {return *(m_sourcePtr + 1);}
	///Return the current character in the character stream.
	char currentCharacter() const {return *m_sourcePtr;}

	int currentColumn() const {return m_col;}
	int currentLine() const {return m_line;}

	void storeCharacterAndGetNext()
	{
		m_currentToken.append(1, currentCharacter());
		advanceInput();
	}

	///Check if the current character is after the end of the stream.
	bool checkEndOfStream();
	///Check if the current character is after the end of the stream and throw and exception if it is.
	///@throw TokenizerError The stream is at the end.
	void checkInvalidEndOfStream(const char* errorMessage);

	///Check if the given character is a digit character [0-9].
	bool isDigit(char character) const;

	///Check if the given character is a hex digit character [0-9A-Za-z].
	bool isHexDigit(char character) const;

	///Advance the stream forward until the next non-whitespace character.
	///@details Also advances the line counter forward if a newline is encountered.
	void skipWhitespace();

	void handleEscapeString();

	///Test if character belongs to [A-Za-z_]
	bool isValidLeadingIdentifierCharacter(char character);
	///Test if character belongs to [A-Za-z_0-9]
	bool isValidIdentifierCharacter(char character);

	bool isNewline(char character) const {return character == '\n';}

	///Lookahead max @a count characters and see if they is equal to @a str.
	///Handles end of stream gracefully.
	bool lookaheadEq(const char* str, int count);

	///Read a decimal or hexadecimal number from the stream, returning the Token.
	///@details A number is defined as either a decimal number ([0-9]+) or a hexadecimal number(0x[0-9]+).
	///Decimal numbers may have leading zeros as octal is not recognized.
	///@throw TokenizerError A null hexadecimal string ('0x') was encountered.
	Token readNumber();

	Token readDecimalNumber();
	Token readHexNumber();

	/**
	 * Read a string literal from the stream, returning the Token.
	 * @details A string literal is surrounded by ""'s. readString also expands
	 * any escape sequences it finds. Currently, \\, \n and \t are defined.
	 * @throw TokenizerError
	 * - An invalid escape sequence was encountered.
	 * - The stream ended while searching for the terminating '"'.
	 */
	Token readString();

	Token readLineComment();
	Token readBlockComment();

	//[A-Za-z_][A-Za-z_0-9]*
	Token readIdentifier();
	bool makeKeyword(const std::string& name, int line, int startCol, Token& outToken);

	bool readSymbol(Token& outToken);
	Token makeSingleCharSymbol(Token::TokenType type);

	std::string m_currentToken;

	std::string m_source;
	const char* m_sourcePtr = nullptr;

	std::string m_file;
	int m_line = 1;
	int m_col = 1;

	bool m_endOfInput = false;
};

inline void Tokenizer::advanceInput()
{
	//Go to the next line
	if(currentCharacter() == '\n')
	{
		m_line += 1;
		m_col = 0;
	}
	m_col += 1;
	m_sourcePtr += 1;
}

inline void Tokenizer::advanceInput(int n)
{
	for(int i = 0; i < n; ++i)
	{
		advanceInput();
	}
}

}

#endif
