#include "Multiplication.h"

namespace pidl
{
namespace ast
{

Multiplication::Multiplication(
		std::unique_ptr<Expression> leftExpression,
		std::unique_ptr<Expression> rightExpression):
	BinaryExpression(NodeType::Multiplication, std::move(leftExpression), std::move(rightExpression))
{
}

void Multiplication::output(std::ostream& stream) const
{
	stream << "<multiplication>";
}


}
}

