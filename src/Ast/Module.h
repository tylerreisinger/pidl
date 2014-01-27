#ifndef MODULE_H_
#define MODULE_H_

#include "AstNode.h"

namespace pidl
{
namespace ast
{

class Module: public pidl::ast::AstNode
{
public:
	Module() = default;
	virtual ~Module() = default;

	void appendChild(std::unique_ptr<AstNode> child);

	virtual void output(std::ostream& stream) const override;

protected:

};

}
}

#endif
