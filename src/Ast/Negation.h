#ifndef NEGATION_H_
#define NEGATION_H_

#include "Expression.h"

namespace pidl
{
namespace ast
{

class Negation: public pidl::ast::Expression
{
public:
	Negation(std::unique_ptr<Expression> operand);
	virtual ~Negation() = default;

	Expression* operand() {return m_operand;}

	virtual void output(std::ostream& stream) const override;

protected:
	Expression* m_operand;
};

}
}

#endif
