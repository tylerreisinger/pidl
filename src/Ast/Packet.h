#ifndef PACKET_H_
#define PACKET_H_

#include "Statement.h"

#include <string>

#include "PacketFieldDefinition.h"

namespace pidl
{
namespace ast
{

class Packet : public Statement
{
public:
	Packet(const std::string& name);
	virtual ~Packet() = default;

	virtual void output(std::ostream& stream) const override;

	void appendChild(std::unique_ptr<PacketFieldDefinition> child);

protected:
	std::string m_name;
};

}
}

#endif /* PACKET_H_ */
