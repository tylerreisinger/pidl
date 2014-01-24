#ifndef PIDLERROR_H_
#define PIDLERROR_H_

#include <exception>
#include <string>

namespace pidl
{
///Base exception class for all exceptions in the pidl library
class PidlError: public std::exception
{
public:
	PidlError() = default;
	PidlError(const std::string& message);
	virtual ~PidlError() noexcept = default;

	PidlError(const PidlError& other);
	PidlError(PidlError&& other) noexcept;
	PidlError& operator =(const PidlError& other);
	PidlError& operator =(PidlError&& other) noexcept;

	virtual const char* what() const noexcept {return m_message.c_str();}

protected:

	void setMessage(const std::string& message);

	std::string m_message;
};

}

#endif
