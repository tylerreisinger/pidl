#ifndef TOKENIZERERROR_H_
#define TOKENIZERERROR_H_

#include "PidlError.h"

namespace pidl
{

class TokenizerError: public pidl::PidlError
{
public:
	TokenizerError(const std::string& error);
	TokenizerError(const std::string& error, int line, int column);
	TokenizerError(const std::string& error, const std::string& file, int line, int column);
	virtual ~TokenizerError() = default;

	TokenizerError(const TokenizerError& other);
	TokenizerError(TokenizerError&& other) noexcept;
	TokenizerError& operator =(const TokenizerError& other);
	TokenizerError& operator =(TokenizerError&& other) noexcept;

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
