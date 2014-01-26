#include "Packet.h"

namespace pidl
{
namespace ast
{

Packet::Packet(const std::string& name): Statement(NodeType::Packet),
	m_name(name)
{
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
