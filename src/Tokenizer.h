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
	bool endOfInput() const {return m_endOfInput;}

protected:

	///Advance the character stream one position and return the new current character.
	char getNextCharacter() {m_col++; return *(++m_sourcePtr);}
	///Advance the character stream one position.
	void advanceInput() {++m_sourcePtr;}
	///Get the next character in the stream but do not advance.
	///@details It is an error to use this function when at the end of the stream.
	char peekNextCharacter() {return *(m_sourcePtr + 1);}
	///Return the current character in the character stream.
	char currentCharacter() {return *m_sourcePtr;}

	///Check if the given character is a digit character [0-9].
	bool isDigit(char character);

	///Read a decimal or hexadecimal number from the stream, returning the Token.
	///@details A number is defined as either a decimal number ([0-9]+) or a hexidecimal number(0x[0-9]+).
	///Decimal numbers may have leading zeros as octal is not recognized.
	///@throw TokenizerError A null hexadecimal string ('0x') was encountered.
	Token readNumber();

	std::string m_currentToken;

	std::string m_source;
	const char* m_sourcePtr = nullptr;

	std::string m_file;
	int m_line = 0;
	int m_col = 0;

	bool m_endOfInput = false;
};

}

#endif
