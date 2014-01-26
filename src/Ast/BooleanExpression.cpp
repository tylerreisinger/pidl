#include "BooleanExpression.h"

namespace pidl
{
namespace ast
{

BooleanExpression::BooleanExpression(bool value) : Expression(NodeType::BooleanExpression),
	m_value(value)
{

}

void BooleanExpression::output(std::ostream& stream) const
{
	stream << "<boolean_expression " << (m_value == true ? "true" : "false") << ">";
}

}
}
