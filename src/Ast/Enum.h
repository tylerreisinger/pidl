#ifndef ENUM_H_
#define ENUM_H_

#include "Statement.h"

#include <vector>
#include <memory>

#include "ConstantAssignment.h"

namespace pidl
{
namespace ast
{

class Enum: public pidl::ast::Statement
{
public:
	Enum(const std::string& name);
	virtual ~Enum() = default;

	void appendChild(std::unique_ptr<ConstantAssignment> value);

	virtual void output(std::ostream& stream) const override;

protected:
	std::string m_name;
};

}
}

#endif
