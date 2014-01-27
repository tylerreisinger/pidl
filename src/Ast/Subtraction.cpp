#include "Subtraction.h"

namespace pidl
{
namespace ast
{

Subtraction::Subtraction(std::unique_ptr<Expression> leftExpression,
		std::unique_ptr<Expression> rightExpression):
	BinaryExpression(NodeType::Subtraction, std::move(leftExpression), std::move(rightExpression))
{
}

void Subtraction::output(std::ostream& stream) const
{
	stream << "<subtraction>";
}

}
}


