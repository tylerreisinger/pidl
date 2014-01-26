#ifndef CONSTANT_H_
#define CONSTANT_H_

#include "Expression.h"

namespace pidl
{
namespace ast
{

class Constant: public pidl::ast::Expression
{
public:
	Constant(const std::string& name);
	virtual ~Constant();

	const std::string& name() const {return m_name;}

	virtual void output(std::ostream& stream) const override;

protected:
	std::string m_name;
};

}
}

#endif
