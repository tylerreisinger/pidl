#include "Module.h"

namespace pidl
{
namespace ast
{

void Module::appendChild(std::unique_ptr<AstNode> child)
{
	setAsParent(child.get());
	m_children.push_back(std::move(child));
}

void Module::output(std::ostream& stream) const
{
	stream << "<module>";
}

}
}
