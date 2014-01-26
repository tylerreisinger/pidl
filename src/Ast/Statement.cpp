#include "Statement.h"

namespace pidl
{
namespace ast
{

Statement::Statement(NodeType type) : AstNode(type)
{

}

Statement::Statement(NodeType type,
		std::vector<std::unique_ptr<AstNode>>&& children) : AstNode(type, std::move(children))
{
}

}
}


