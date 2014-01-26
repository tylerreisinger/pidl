#include "Enum.h"

namespace pidl
{
namespace ast
{

Enum::Enum(const std::string& name) : Statement(NodeType::Enum),
	m_name(name)
{
}

void Enum::appendChild(std::unique_ptr<ConstantAssignment> value)
{
	setAsParent(value.get());
	m_children.push_back(std::move(value));
}

void Enum::output(std::ostream& stream) const
{
	stream << "<enum " << m_name << ">";
}

}
}
