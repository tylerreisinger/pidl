#include "ParameterizedType.h"

#include "TypeList.h"

#include <cassert>

namespace pidl
{
namespace ast
{

ParameterizedType::ParameterizedType(std::unique_ptr<Type> primaryType,
		std::unique_ptr<TypeList> typeList): Type(NodeType::ParameterizedType),
	m_primaryType(primaryType.get()), m_typeList(typeList.get())
{
	assert(primaryType != nullptr);
	assert(typeList != nullptr);

	setAsParent(primaryType.get());
	setAsParent(typeList.get());
	m_children.push_back(std::move(primaryType));
	m_children.push_back(std::move(typeList));
}

ParameterizedType::~ParameterizedType()
{
}

void ParameterizedType::output(std::ostream& stream) const
{
	stream << "<parameterized_type " << name() << ">";
}

}
}
