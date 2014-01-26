#ifndef SIMPLETYPE_H_
#define SIMPLETYPE_H_

#include "Type.h"

namespace pidl
{
namespace ast
{

class SimpleType: public pidl::ast::Type
{
public:
	SimpleType(const std::string& name);
	virtual ~SimpleType() = default;

	virtual std::string name() const override {return m_name;}

	virtual void output(std::ostream& stream) const;

protected:
	std::string m_name;
};

}
}

#endif
