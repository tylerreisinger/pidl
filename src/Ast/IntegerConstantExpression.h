#ifndef INTEGERCONSTANTEXPRESSION_H_
#define INTEGERCONSTANTEXPRESSION_H_

#include "Expression.h"

#include <cstdint>

namespace pidl
{
namespace ast
{

class IntegerConstantExpression: public pidl::ast::Expression
{
public:
	IntegerConstantExpression(int64_t value);
	virtual ~IntegerConstantExpression();

	int64_t value() const {return m_value;}

	virtual void output(std::ostream& stream) const override;

protected:
	int64_t m_value;
};

}
}

#endif
