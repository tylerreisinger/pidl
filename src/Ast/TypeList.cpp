#include "TypeList.h"

#include "Type.h"

namespace pidl
{
namespace ast
{

TypeList::TypeList() : Statement(NodeType::TypeList)
{
}

void TypeList::appendChild(std::unique_ptr<Type> child)
{
	setAsParent(child.get());
	m_children.push_back(std::move(child));
}

void TypeList::output(std::ostream& stream) const
{
	stream << "<type_list>";
}


}
}

