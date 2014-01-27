#ifndef MULTIPLICATION_H_
#define MULTIPLICATION_H_

#include "BinaryExpression.h"

namespace pidl
{
namespace ast
{

class Multiplication: public pidl::ast::BinaryExpression
{
public:
	static constexpr int precedence = 10;

	Multiplication(std::unique_ptr<Expression> leftExpression, std::unique_ptr<Expression> rightExpression);
	virtual ~Multiplication() = default;

	virtual void output(std::ostream& stream) const override;
};

}
}

#endif
