#ifndef ATTRIBUTEVALUE_H_
#define ATTRIBUTEVALUE_H_

#include "Statement.h"

namespace pidl
{
namespace ast
{
class Expression;
class AttributeValue: public pidl::ast::Statement
{
public:
	AttributeValue(const std::string& name, std::unique_ptr<Expression> value);
	virtual ~AttributeValue() = default;

	const std::string& name() const {return m_name;}
	Expression* value() const {return m_value;}

	virtual void output(std::ostream& stream) const override;

protected:
	std::string m_name;
	Expression* m_value = nullptr;
};

}
}

#endif
