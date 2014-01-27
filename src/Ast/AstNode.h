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
	typedef std::vector<std::unique_ptr<AstNode>>::iterator iterator;
	typedef std::vector<std::unique_ptr<AstNode>>::const_iterator const_iterator;

	enum class NodeType
	{
		None,

		Module,

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

	iterator childrenBegin() {return m_children.begin();}
	const_iterator childrenBegin() const {return m_children.begin();}
	iterator childrenEnd() {return m_children.end();}
	const_iterator childrenEnd() const {return m_children.end();}

	AstNode* firstChild() {return m_children.front().get();}
	AstNode* lastChild() {return m_children.back().get();}

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
