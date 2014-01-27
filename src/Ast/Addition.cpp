#include "Addition.h"

namespace pidl
{
namespace ast
{

Addition::Addition(std::unique_ptr<Expression> leftExpression, std::unique_ptr<Expression> rightExpression):
		BinaryExpression(NodeType::Addition, std::move(leftExpression), std::move(rightExpression))
{

}

void Addition::output(std::ostream& stream) const
{
	stream << "<addition>";
}

}
}


