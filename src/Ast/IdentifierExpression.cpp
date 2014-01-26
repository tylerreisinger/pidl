#include "IdentifierExpression.h"

namespace pidl
{
namespace ast
{

IdentifierExpression::IdentifierExpression(
		std::vector<std::string>&& identifierPath) : Expression(NodeType::IdentifierExpression),
	m_identifierPath(std::move(identifierPath))
{
}

std::string IdentifierExpression::fullName() const
{
	std::string path;
	int i = 0;
	for(auto& str : m_identifierPath)
	{
		if(i != 0)
		{
			path += '.';
		}
		path += str;
		i += 1;
	}
	return path;
}

void IdentifierExpression::output(std::ostream& stream) const
{
	stream << "<identifier_expression " << fullName() << ">";
}

}
}
