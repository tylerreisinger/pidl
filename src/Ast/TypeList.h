#ifndef TYPELIST_H_
#define TYPELIST_H_

#include "Statement.h"

namespace pidl
{
namespace ast
{
class Type;
class TypeList: public pidl::ast::Statement
{
public:
	TypeList();
	virtual ~TypeList() = default;

	void appendChild(std::unique_ptr<Type> child);

	virtual void output(std::ostream& stream) const override;

protected:

};

}
}

#endif
