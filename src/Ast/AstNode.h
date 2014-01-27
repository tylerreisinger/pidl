#ifndef ASTNODE_H_
#define ASTNODE_H_

#include <ostream>
#include <vector>
#include <memory>

namespace pidl
{
namespace ast
{

class AstNode
{
public:

	enum class NodeType
	{
		None,

		//Statements
		Namespace,
		ConstantAssignment,
		Enum,
		Packet,
		PacketFieldDefinition,
		AttributeList,
		AttributeValue,
		TypeList,


		//Expressions
		IntegerConstant,
		StringExpression,
		BooleanExpression,
		FloatExpression,
		Constant,
		IdentifierExpression,

		Addition,
		Subtraction,
		Multiplication,
		Division,

		Negation,

		//Types
		SimpleType,
		ParameterizedType
	};

	AstNode(NodeType type);
	AstNode(NodeType type, std::vector<std::unique_ptr<AstNode>>&& children);
	virtual ~AstNode() = default;

	AstNode(const AstNode&) = delete;
	AstNode(AstNode&&) = delete;
	AstNode& operator =(const AstNode&) = delete;
	AstNode& operator =(AstNode&&) = delete;

	NodeType type() const {return m_type;}

	size_t childCount() const {return m_children.size();}
	bool hasChildren() const {return !m_children.empty();}

	virtual void output(std::ostream& stream) const = 0;
	void outputTree(std::ostream& stream) const;

	friend std::ostream& operator <<(std::ostream& stream, const AstNode& node);

protected:
	AstNode() = default;
	void outputTreeInternal(std::ostream& stream, const std::string& prefixString) const;

	void setAsParent(AstNode* node) {node->m_parent = this;}

	std::vector<std::unique_ptr<AstNode>> m_children;

	NodeType m_type = NodeType::None;
	AstNode* m_parent = nullptr;
};

}
}

#endif
