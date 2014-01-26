#ifndef PARSERERROR_H_
#define PARSERERROR_H_

#include "PidlError.h"

namespace pidl
{

class ParserError: public pidl::PidlError
{
public:
	ParserError(const std::string& error);
	ParserError(const std::string& error, int line, int column);
	ParserError(const std::string& error, const std::string& file, int line, int column);
	virtual ~ParserError() = default;

	ParserError(const ParserError& other);
	ParserError(ParserError&& other) noexcept;
	ParserError& operator =(const ParserError& other);
	ParserError& operator =(ParserError&& other) noexcept;

	int line() const {return m_line;}
	int column() const {return m_column;}
	const std::string& file() const {return m_file;}

protected:
	std::string m_file;
	int m_line = 0;
	int m_column = 0;
};

}

#endif
