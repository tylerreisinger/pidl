#include "AstNode.h"

namespace pidl
{
namespace ast
{

AstNode::AstNode(NodeType type):
	m_type(type)
{
}

AstNode::AstNode(NodeType type, std::vector<std::unique_ptr<AstNode>>&& children):
	m_type(type), m_children(std::move(children))
{
	for(auto& child : m_children)
	{
		setAsParent(child.get());
	}
}

std::ostream& operator <<(std::ostream& stream, const AstNode& node)
{
	node.output(stream);
	return stream;
}

void AstNode::outputTree(std::ostream& stream) const
{
	outputTreeInternal(stream, "");
}

void AstNode::outputTreeInternal(std::ostream& stream, const std::string& prefixString)	const
{
	static constexpr int lineSep = 1;
	std::string prefix = prefixString.substr(0, prefixString.size() - 1);
	if(prefixString.empty())
	{
		stream << "---";
	}
	else
	{
		stream << prefix << "+---";
	}
	output(stream);
	stream << "\n";
	std::string spacePrefix = prefixString + "   |";
	std::string connectPrefix = prefixString + "    ";
	for(auto i = 0; i < m_children.size(); ++i)
	{
		for(int i = 0; i < lineSep; ++i)
		{
			stream << spacePrefix << "\n";
		}
		if(i != m_children.size() - 1)
		{
			m_children[i]->outputTreeInternal(stream, spacePrefix);
		}
		else
		{
			m_children[i]->outputTreeInternal(stream, connectPrefix);
		}
	}
}

}
}


