#ifndef PACKET_H_
#define PACKET_H_

#include "Statement.h"

#include <string>

#include "PacketFieldDefinition.h"

namespace pidl
{
namespace ast
{
class AttributeList;

class Packet : public Statement
{
public:
	Packet(const std::string& name, std::unique_ptr<AttributeList> attributeList);
	virtual ~Packet() = default;

	virtual void output(std::ostream& stream) const override;

	void appendChild(std::unique_ptr<PacketFieldDefinition> child);

	AttributeList* attributeList() const {return m_attributeList;}

protected:
	std::string m_name;
	AttributeList* m_attributeList = nullptr;
};

}
}

#endif /* PACKET_H_ */
