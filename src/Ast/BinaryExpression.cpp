#include "BinaryExpression.h"

namespace pidl
{
namespace ast
{

BinaryExpression::BinaryExpression(NodeType type,
		std::unique_ptr<Expression> leftExpression, std::unique_ptr<Expression> rightExpression): Expression(type),
	m_left(leftExpression.get()), m_right(rightExpression.get())
{
	if(leftExpression != nullptr)
	{
		setAsParent(leftExpression.get());
		m_children.push_back(std::move(leftExpression));
	}
	if(rightExpression != nullptr)
	{
		setAsParent(rightExpression.get());
		m_children.push_back(std::move(rightExpression));
	}
}

}
}
