#ifndef PARAMETERIZEDTYPE_H_
#define PARAMETERIZEDTYPE_H_

#include "Type.h"

namespace pidl
{
namespace ast
{
class TypeList;
class ParameterizedType: public pidl::ast::Type
{
public:
	ParameterizedType(std::unique_ptr<Type> primaryType, std::unique_ptr<TypeList> typeList);
	virtual ~ParameterizedType();

	Type* primaryType() {return m_primaryType;}
	TypeList* typeList() {return m_typeList;}

	virtual std::string name() const override {return m_primaryType->name();}

	virtual void output(std::ostream& stream) const override;

protected:
	Type* m_primaryType = nullptr;
	TypeList* m_typeList = nullptr;
};

}
}

#endif /* PARAMETERIZEDTYPE_H_ */
