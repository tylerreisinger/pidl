#include "Division.h"

namespace pidl
{
namespace ast
{

Division::Division(
		std::unique_ptr<Expression> leftExpression,
		std::unique_ptr<Expression> rightExpression):
	BinaryExpression(NodeType::Division, std::move(leftExpression), std::move(rightExpression))
{
}

void Division::output(std::ostream& stream) const
{
	stream << "<division>";
}


}
}
