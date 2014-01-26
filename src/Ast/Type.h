#ifndef TYPE_H_
#define TYPE_H_

#include "AstNode.h"

namespace pidl
{
namespace ast
{

class Type: public pidl::ast::AstNode
{
public:
	Type(NodeType type);
	virtual ~Type();

	virtual std::string name() const = 0;
};

}
}

#endif
