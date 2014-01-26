#ifndef NAMESPACESTATEMENT_H_
#define NAMESPACESTATEMENT_H_

#include "Statement.h"

#include <string>
#include <vector>

namespace pidl
{
namespace ast
{

class NamespaceStatement : public Statement
{
public:
	NamespaceStatement(std::vector<std::string>&& path);
	virtual ~NamespaceStatement() = default;

	const std::vector<std::string>& path() const {return m_path;}

	virtual void output(std::ostream& stream) const override;

protected:
	std::vector<std::string> m_path;
};

}
}

#endif
