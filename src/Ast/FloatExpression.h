#ifndef FLOATEXPRESSION_H_
#define FLOATEXPRESSION_H_

#include "Expression.h"

namespace pidl
{
namespace ast
{

class FloatExpression: public pidl::ast::Expression
{
public:
	FloatExpression(double value);
	virtual ~FloatExpression() = default;

	double value() const {return m_value;}

	virtual void output(std::ostream& stream) const override;

protected:
	double m_value;
};

}
}

#endif
