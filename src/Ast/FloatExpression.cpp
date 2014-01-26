#include "FloatExpression.h"

namespace pidl
{
namespace ast
{

FloatExpression::FloatExpression(double value): Expression(NodeType::FloatExpression),
	m_value(value)
{

}

void FloatExpression::output(std::ostream& stream) const
{
	stream << "<float_expression " << m_value << ">";
}

}
}
