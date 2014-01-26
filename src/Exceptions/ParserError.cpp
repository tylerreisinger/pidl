/*
 * ParserError.cpp
 *
 *  Created on: Jan 24, 2014
 *      Author: tyler
 */

#include "ParserError.h"

#include <sstream>

namespace pidl
{

ParserError::ParserError(const std::string& error) : PidlError(error)
{
}

ParserError::ParserError(const std::string& error, int line, int column): PidlError(error),
	m_line(line), m_column(column)
{
	std::ostringstream stream;
	stream << "Error at " << line << ":" << column << ": " << error;
	setMessage(stream.str());
}

ParserError::ParserError(const std::string& error, const std::string& file, int line, int column): PidlError(error),
	m_file(file), m_line(line), m_column(column)
{
	std::ostringstream stream;
	stream << "Error in '" << file << "'" << " at " << line << ":" << column << ": " << error;
	setMessage(stream.str());
}

ParserError::ParserError(const ParserError& other): PidlError(other),
	m_file(other.m_file), m_line(other.m_line), m_column(other.m_column)
{
}

ParserError::ParserError(ParserError&& other) noexcept: PidlError(other),
	m_file(std::move(other.m_file)), m_line(other.m_line), m_column(other.m_column)
{
}

ParserError& ParserError::operator =(const ParserError& other)
{
	PidlError::operator =(other);
	m_file = other.m_file;
	m_line = other.m_line;
	m_column = other.m_column;
	return *this;
}

ParserError& ParserError::operator =(ParserError&& other) noexcept
{
	m_message = std::move(other.m_message);
	m_file = std::move(other.m_file);
	m_line = other.m_line;
	m_column = other.m_column;
	return *this;
}

}

