#include "PidlError.h"

namespace pidl
{

PidlError::PidlError(const std::string& message):
	m_message(message)
{
}

PidlError::PidlError(const PidlError& other):
	m_message(other.m_message)
{
}

PidlError::PidlError(PidlError&& other) noexcept:
	m_message(std::move(other.m_message))
{
}

PidlError& PidlError::operator =(const PidlError& other)
{
	m_message = other.m_message;
	return *this;
}

PidlError& PidlError::operator =(PidlError&& other) noexcept
{
	m_message = std::move(other.m_message);
	return *this;
}

void PidlError::setMessage(const std::string& message)
{
	m_message = message;
}

}
