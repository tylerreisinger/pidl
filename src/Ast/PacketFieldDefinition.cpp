#include "PacketFieldDefinition.h"

#include "Type.h"
#include "Expression.h"
#include "AttributeList.h"

namespace pidl
{
namespace ast
{

PacketFieldDefinition::PacketFieldDefinition(const std::string& name, std::unique_ptr<Type> type,
		std::unique_ptr<Expression> index, bool required, std::unique_ptr<AttributeList> attributeList):
		Statement(NodeType::PacketFieldDefinition),
	m_name(name), m_type(type.get()), m_index(index.get()), m_required(required), m_attributeList(attributeList.get())
{
	setAsParent(type.get());
	setAsParent(index.get());
	if(attributeList != nullptr)
	{
		setAsParent(attributeList.get());
		m_children.push_back(std::move(attributeList));
	}
	m_children.push_back(std::move(type));
	m_children.push_back(std::move(index));
}

void PacketFieldDefinition::output(std::ostream& stream) const
{
	stream << "<packet_field_definition " << m_name << ">";
}

}
}
