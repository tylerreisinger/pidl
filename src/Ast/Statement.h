#ifndef STATEMENT_H_
#define STATEMENT_H_

#include "AstNode.h"

namespace pidl
{
namespace ast
{

class Statement: public pidl::ast::AstNode
{
public:
	Statement(NodeType type);
	Statement(NodeType type, std::vector<std::unique_ptr<AstNode>>&& children);
	virtual ~Statement() = default;


};

}
}

#endif
