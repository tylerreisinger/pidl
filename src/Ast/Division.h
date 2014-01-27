#ifndef DIVISION_H_
#define DIVISION_H_

#include "BinaryExpression.h"

namespace pidl
{
namespace ast
{

class Division: public pidl::ast::BinaryExpression
{
public:
	static constexpr int precedence = 10;

	Division(std::unique_ptr<Expression> leftExpression, std::unique_ptr<Expression> rightExpression);
	virtual ~Division() = default;

	virtual void output(std::ostream& stream) const override;
};

}
}

#endif
