#ifndef ADDITION_H_
#define ADDITION_H_

#include "BinaryExpression.h"

namespace pidl
{
namespace ast
{

class Addition: public pidl::ast::BinaryExpression
{
public:
	static constexpr int precedence = 20;

	Addition(std::unique_ptr<Expression> leftExpression, std::unique_ptr<Expression> rightExpression);
	virtual ~Addition() = default;

	virtual void output(std::ostream& stream) const override;
};

}
}

#endif
