#ifndef IDENTIFIEREXPRESSION_H_
#define IDENTIFIEREXPRESSION_H_

#include "Expression.h"

namespace pidl
{
namespace ast
{

class IdentifierExpression: public pidl::ast::Expression
{
public:
	IdentifierExpression(std::vector<std::string>&& identifierPath);
	virtual ~IdentifierExpression() = default;

	std::string fullName() const;
	const std::string& shortName() const {return m_identifierPath.back();}

	const std::vector<std::string>& identifierPath() const {return m_identifierPath;}

	virtual void output(std::ostream& stream) const override;

protected:
	std::vector<std::string> m_identifierPath;
};

}
}

#endif
