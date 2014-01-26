#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include "AstNode.h"

namespace pidl
{
namespace ast
{

class Expression: public pidl::ast::AstNode
{
public:
	Expression(NodeType type);
	virtual ~Expression() = default;

protected:

};

}
}

#endif
