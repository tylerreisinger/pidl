#include "Packet.h"

#include "AttributeList.h"

namespace pidl
{
namespace ast
{

Packet::Packet(const std::string& name, std::unique_ptr<AttributeList> attributeList):
		Statement(NodeType::Packet),
	m_name(name), m_attributeList(attributeList.get())
{
	if(attributeList != nullptr)
	{
		setAsParent(attributeList.get());
		m_children.push_back(std::move(attributeList));
	}
}

void Packet::output(std::ostream& stream) const
{
	stream << "<packet " << m_name << ">";
}

void Packet::appendChild(std::unique_ptr<PacketFieldDefinition> child)
{
	setAsParent(child.get());
	m_children.push_back(std::move(child));
}

}
}
