#ifndef STRINGEXPRESSION_H_
#define STRINGEXPRESSION_H_

#include "Expression.h"

namespace pidl
{
namespace ast
{

class StringExpression: public pidl::ast::Expression
{
public:
	StringExpression(const std::string& value);
	virtual ~StringExpression() = default;

	const std::string& value() const {return m_value;}

	virtual void output(std::ostream& stream) const override;

protected:
	std::string m_value;
};

}
}

#endif
