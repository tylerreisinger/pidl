#include "StringExpression.h"

namespace pidl
{
namespace ast
{

StringExpression::StringExpression(const std::string& value) : Expression(NodeType::StringExpression),
	m_value(value)
{

}

void StringExpression::output(std::ostream& stream) const
{
	stream << "<string_expression " << m_value << ">";
}

}
}
