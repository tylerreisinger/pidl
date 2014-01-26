#include "Token.h"

namespace pidl
{

Token::Token(TokenType type):
	m_type(type)
{
}

Token::Token(TokenType type, const std::string& string):
	m_type(type), m_string(string)
{

}

Token::Token(TokenType type, std::string&& string):
	m_type(type), m_string(std::move(string))
{
}

Token::Token(TokenType type, int startCol, int endCol, int startLine, int endLine):
	m_type(type),
	m_startLine(startLine), m_endLine(endLine), m_startCol(startCol), m_endCol(endCol)
{
}

Token::Token(TokenType type, const std::string& string, int startCol, int endCol, int startLine, int endLine):
	m_type(type), m_string(string),
	m_startLine(startLine), m_endLine(endLine), m_startCol(startCol), m_endCol(endCol)
{
}

Token::Token(TokenType type, std::string&& string, int startCol, int endCol, int startLine, int endLine):
	m_type(type), m_string(std::move(string)),
	m_startLine(startLine), m_endLine(endLine), m_startCol(startCol), m_endCol(endCol)
{
}


Token::Token(const Token& other):
	m_type(other.m_type), m_string(other.m_string),
	m_startLine(other.m_startLine), m_endLine(other.m_endLine), m_startCol(other.m_startCol), m_endCol(other.m_endCol)
{
}

Token::Token(Token&& other): Token()
{
	swap(*this, other);
}

Token& Token::operator =(const Token& other)
{
	m_type = other.m_type;
	m_string = other.m_string;
	m_startCol = other.m_startCol;
	m_endCol = other.m_endCol;
	m_startLine = other.m_startLine;
	m_endLine = other.m_endLine;
	return *this;
}

Token& Token::operator =(Token&& other)
{
	m_type = other.m_type;
	m_string = std::move(other.m_string);
	m_startCol = other.m_startCol;
	m_endCol = other.m_endCol;
	m_startLine = other.m_startLine;
	m_endLine = other.m_endLine;
	return *this;
}

void swap(Token& token1, Token& token2)
{
	using std::swap;
	swap(token1.m_type, token2.m_type);
	swap(token1.m_string, token2.m_string);
	swap(token1.m_startCol, token2.m_startCol);
	swap(token1.m_endCol, token2.m_endCol);
	swap(token1.m_startLine, token2.m_startLine);
	swap(token1.m_endLine, token2.m_endLine);
}

std::ostream& operator <<(std::ostream& os, Token::TokenType tokenType)
{
	switch(tokenType)
	{
	case Token::TokenType::None:
	{
		os << "none";
		break;
	}
	case Token::TokenType::Number:
	{
		os << "number";
		break;
	}
	case Token::TokenType::HexNumber:
	{
		os << "hex number";
		break;
	}
	case Token::TokenType::FloatNumber:
	{
		os << "float";
		break;
	}
	case Token::TokenType::String:
	{
		os << "string";
		break;
	}
	case Token::TokenType::Comment:
	{
		os << "comment";
		break;
	}
	case Token::TokenType::Identifier:
	{
		os << "identifier";
		break;
	}
	case Token::TokenType::OpenDelimiter:
	{
		os << "Open Delimiter";
		break;
	}
	case Token::TokenType::CloseDelimiter:
	{
		os << "Close Delimiter";
		break;
	}
	case Token::TokenType::ScopeResolution:
	{
		os << "scope resolution operator";
		break;
	}
	case Token::TokenType::KeywordConstant:
	{
		os << "keyword constant";
		break;
	}
	case Token::TokenType::KeywordEnum:
	{
		os << "keyword enum";
		break;
	}
	case Token::TokenType::KeywordNamespace:
	{
		os << "keyword namespace";
		break;
	}
	case Token::TokenType::KeywordPacket:
	{
		os << "keyword packet";
		break;
	}
	case Token::TokenType::KeywordTrue:
	{
		os << "keyword true";
		break;
	}
	case Token::TokenType::KeywordFalse:
	{
		os << "keyword false";
		break;
	}
	case Token::TokenType::KeywordRequired:
	{
		os << "keyword req";
		break;
	}
	case Token::TokenType::KeywordOptional:
	{
		os << "keyword opt";
		break;
	}
	case Token::TokenType::SymCloseBrace:
	{
		os << "}";
		break;
	}
	case Token::TokenType::SymComma:
	{
		os << ",";
		break;
	}
	case Token::TokenType::SymEquals:
	{
		os << "=";
		break;
	}
	case Token::TokenType::SymOpenBrace:
	{
		os << "{";
		break;
	}
	case Token::TokenType::SymOpenSqBracket:
	{
		os << "[";
		break;
	}
	case Token::TokenType::SymCloseSqBracket:
	{
		os << "]";
		break;
	}
	case Token::TokenType::SymOpenAngBracket:
	{
		os << "<";
		break;
	}
	case Token::TokenType::SymCloseAngBracket:
	{
		os << ">";
		break;
	}
	case Token::TokenType::SymColon:
	{
		os << ":";
		break;
	}
	default:
	{
		os << "unknown";
		break;
	}
	}
	return os;
}

std::ostream& operator <<(std::ostream& os, const Token& token)
{
	os << token.type();
#ifndef NDEBUG
	os << " (" << token.startLine() << ":" << token.startColumn() << " - " <<
			token.endLine() << ":" << token.endColumn() << ") ";
#endif
	if(!token.m_string.empty())
	{
		os << ": " << token.m_string;
	}
	return os;
}

}
