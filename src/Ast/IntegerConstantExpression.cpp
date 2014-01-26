/*
 * IntegerConstantExpression.cpp
 *
 *  Created on: Jan 25, 2014
 *      Author: tyler
 */

#include "IntegerConstantExpression.h"

namespace pidl
{
namespace ast
{

IntegerConstantExpression::IntegerConstantExpression(int64_t value) : Expression(NodeType::IntegerConstant),
	m_value(value)
{
}

IntegerConstantExpression::~IntegerConstantExpression()
{

}

void IntegerConstantExpression::output(std::ostream& stream) const
{
	stream << "<integer_constant value=" << m_value << ">";
}

}
}
