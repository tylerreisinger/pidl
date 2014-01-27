#include "Negation.h"

namespace pidl
{
namespace ast
{

Negation::Negation(std::unique_ptr<Expression> operand) : Expression(NodeType::Negation),
	m_operand(operand.get())
{
	setAsParent(operand.get());
	m_children.push_back(std::move(operand));
}

void Negation::output(std::ostream& stream) const
{
	stream << "<unary_negation>";
}

}
}
