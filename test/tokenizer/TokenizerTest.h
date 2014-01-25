/*
 * TokenizerTest.h
 *
 *  Created on: Jan 24, 2014
 *      Author: tyler
 */

#ifndef TOKENIZERTEST_H_
#define TOKENIZERTEST_H_

#include "gtest/gtest.h"

#include "Tokenizer.h"

namespace pidl
{

class TokenizerTest: public ::testing::Test
{
public:
	TokenizerTest() = default;
	virtual ~TokenizerTest() {};

protected:

	virtual void SetUp();

	pidl::Tokenizer tokenizer;
};

}

#endif /* TOKENIZERTEST_H_ */
