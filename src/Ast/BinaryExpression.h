#ifndef BINARYEXPRESSION_H_
#define BINARYEXPRESSION_H_

#include "Expression.h"

namespace pidl
{
namespace ast
{

class BinaryExpression: public pidl::ast::Expression
{
public:
	BinaryExpression(NodeType type,
			std::unique_ptr<Expression> leftExpression, std::unique_ptr<Expression> rightExpression);
	virtual ~BinaryExpression() = default;

	Expression* leftExpression() {return m_left;}
	Expression* rightExpression() {return m_right;}

protected:
	Expression* m_left;
	Expression* m_right;
};

}
}

#endif
