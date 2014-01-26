#include "SimpleType.h"

namespace pidl
{
namespace ast
{

SimpleType::SimpleType(const std::string& name): Type(NodeType::SimpleType),
	m_name(name)
{
}

void SimpleType::output(std::ostream& stream) const
{
	stream << "<simple_type " << m_name << ">";
}

}
}
