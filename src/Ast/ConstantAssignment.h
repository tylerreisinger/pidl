#ifndef CONSTANTASSIGNMENT_H_
#define CONSTANTASSIGNMENT_H_

#include "Statement.h"

#include "IntegerConstantExpression.h"
#include "Constant.h"

namespace pidl
{
namespace ast
{

class ConstantAssignment: public pidl::ast::Statement
{
public:
	ConstantAssignment(std::unique_ptr<Constant> constant, std::unique_ptr<IntegerConstantExpression> value);
	virtual ~ConstantAssignment() = default;

	Constant* left() {return m_constant;}
	IntegerConstantExpression* right() {return m_value;}

	int64_t value() const {return m_value->value();}
	const std::string& name() const {return m_constant->name();}

	virtual void output(std::ostream& stream) const override;

protected:
	Constant* m_constant;
	IntegerConstantExpression* m_value;
};

}
}

#endif
