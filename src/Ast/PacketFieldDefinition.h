#ifndef PACKETFIELDDEFINITION_H_
#define PACKETFIELDDEFINITION_H_

#include "Statement.h"

#include "Type.h"

namespace pidl
{
namespace ast
{
class Type;
class Expression;

class PacketFieldDefinition: public pidl::ast::Statement
{
public:
	PacketFieldDefinition(const std::string& name, std::unique_ptr<Type> type,
			std::unique_ptr<Expression> index, bool required);
	virtual ~PacketFieldDefinition() = default;

	virtual void output(std::ostream& stream) const override;

	const std::string& name() const {return m_name;}
	bool isRequired() const {return m_required;}
	Type* fieldType() const {return m_type;}
	Expression* fieldIndex() const {return m_index;}

protected:
	std::string m_name;
	bool m_required = false;
	Type* m_type = nullptr;
	Expression* m_index = nullptr;
};

}
}

#endif
