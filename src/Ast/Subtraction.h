#ifndef SUBTRACTION_H_
#define SUBTRACTION_H_

#include "BinaryExpression.h"

namespace pidl
{
namespace ast
{

class Subtraction: public pidl::ast::BinaryExpression
{
public:
	static constexpr int precedence = 20;

	Subtraction(std::unique_ptr<Expression> leftExpression, std::unique_ptr<Expression> rightExpression);
	virtual ~Subtraction() = default;

	virtual void output(std::ostream& stream) const override;
};

}
}

#endif
