#include "NamespaceStatement.h"

namespace pidl
{
namespace ast
{

NamespaceStatement::NamespaceStatement(std::vector<std::string>&& path) : Statement(NodeType::Namespace),
	m_path(std::move(path))

{
}

void NamespaceStatement::output(std::ostream& stream) const
{
	stream << "<namespace: ";
	int i = 0;
	for(auto& node : m_path)
	{
		if(i++ != 0)
		{
			stream << ".";
		}
		stream << node;
	}
	stream << ">";
}

}
}

