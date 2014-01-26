#ifndef ATTRIBUTELIST_H_
#define ATTRIBUTELIST_H_

#include "Statement.h"

namespace pidl
{
namespace ast
{
class AttributeValue;
class AttributeList: public pidl::ast::Statement
{
public:
	AttributeList();
	virtual ~AttributeList() = default;

	void appendChild(std::unique_ptr<AttributeValue> child);

	virtual void output(std::ostream& stream) const override;

protected:
};

}
}

#endif
