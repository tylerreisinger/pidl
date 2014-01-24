#include "TokenizerError.h"

#include <sstream>

namespace pidl
{

TokenizerError::TokenizerError(const std::string& error): PidlError(error)
{
}

TokenizerError::TokenizerError(const std::string& error, int line, int column):
	m_line(line), m_column(column)
{
	std::ostringstream stream;
	stream << "Error at " << line << ":" << column << ": " << error;
	setMessage(stream.str());
}

TokenizerError::TokenizerError(const std::string& error, const std::string& file, int line, int column):
	m_file(file), m_line(line), m_column(column)
{
	std::ostringstream stream;
	stream << "Error in '" << file << "'" << " at " << line << ":" << column << ": " << error;
	setMessage(stream.str());
}

TokenizerError::TokenizerError(const TokenizerError& other): PidlError(other),
	m_file(other.m_file), m_line(other.m_line), m_column(other.m_column)
{

}

TokenizerError::TokenizerError(TokenizerError&& other) noexcept: PidlError(other),
	m_file(std::move(other.m_file)), m_line(other.m_line), m_column(other.m_column)
{
}

TokenizerError& TokenizerError::operator =(const TokenizerError& other)
{
	PidlError::operator =(other);
	m_file = other.m_file;
	m_line = other.m_line;
	m_column = other.m_column;
	return *this;
}

TokenizerError& TokenizerError::operator =(TokenizerError&& other) noexcept
{
	m_message = std::move(other.m_message);
	m_file = std::move(other.m_file);
	m_line = other.m_line;
	m_column = other.m_column;
	return *this;
}

}
