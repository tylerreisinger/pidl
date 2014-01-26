#include "Constant.h"

namespace pidl
{
namespace ast
{

Constant::Constant(const std::string& name): Expression(NodeType::Constant),
	m_name(name)
{

}

Constant::~Constant()
{
}

void Constant::output(std::ostream& stream) const
{
	stream << "<constant " << m_name << ">";
}

}
}
