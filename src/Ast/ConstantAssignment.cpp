#include "ConstantAssignment.h"

namespace pidl
{
namespace ast
{

ConstantAssignment::ConstantAssignment(std::unique_ptr<Constant> constant, std::unique_ptr<IntegerConstantExpression> value):
	Statement(NodeType::ConstantAssignment),
	m_constant(constant.get()), m_value(value.get())
{
	m_children.push_back(std::move(constant));
	m_children.push_back(std::move(value));
	setAsParent(m_value);
	setAsParent(m_constant);

}

void ConstantAssignment::output(std::ostream& stream) const
{
	stream << "<constant_assignment " << name() << "=" << value() << ">";
}

}
}
