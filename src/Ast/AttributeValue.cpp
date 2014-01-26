#include "AttributeValue.h"

#include "Expression.h"

namespace pidl
{
namespace ast
{

AttributeValue::AttributeValue(const std::string& name,
		std::unique_ptr<Expression> value): Statement(NodeType::AttributeValue),
	m_name(name), m_value(value.get())

{
	setAsParent(value.get());
	m_children.push_back(std::move(value));
}

void AttributeValue::output(std::ostream& stream) const
{
	stream << "<attribute_value " << m_name << ">";
}

}
}
