#ifndef BOOLEANEXPRESSION_H_
#define BOOLEANEXPRESSION_H_

#include "Expression.h"

namespace pidl
{
namespace ast
{

class BooleanExpression: public pidl::ast::Expression
{
public:
	BooleanExpression(bool value);
	virtual ~BooleanExpression() = default;

	bool value() const {return m_value;}

	virtual void output(std::ostream& stream) const override;

protected:
	bool m_value;
};

}
}

#endif
