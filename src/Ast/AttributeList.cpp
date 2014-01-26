#include "AttributeList.h"

#include "AttributeValue.h"

namespace pidl
{
namespace ast
{

AttributeList::AttributeList(): Statement(NodeType::AttributeList)
{

}

void AttributeList::appendChild(std::unique_ptr<AttributeValue> child)
{
	setAsParent(child.get());
	m_children.push_back(std::move(child));
}

void AttributeList::output(std::ostream& stream) const
{
	stream << "<attribute_list>";
}

}
}
