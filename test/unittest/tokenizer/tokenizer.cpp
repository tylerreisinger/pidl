#include <gtest/gtest.h>

#include "Tokenizer.h"
#include "Exceptions/TokenizerError.h"

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	::testing::FLAGS_gtest_death_test_style = "fast";
	return RUN_ALL_TESTS();
}

TEST(TokenizerTest, HandlesSimpleString)
{
	pidl::Tokenizer tk("\"Testing 1,2,3\"");
	ASSERT_NO_THROW(
	{
		auto token = tk.nextToken();
		ASSERT_EQ(pidl::Token::TokenType::String, token.type());
		ASSERT_EQ(token.string(), "Testing 1,2,3");
	}
	);
	ASSERT_NO_THROW(
	{
		auto token = tk.nextToken();
		ASSERT_EQ(pidl::Token::TokenType::None, token.type());
		ASSERT_TRUE(tk.isEndOfInput());
	});
}

TEST(TokenizerTest, HandlesMalformedString)
{
	pidl::Tokenizer tk("\"Testing 1,2,3");
	ASSERT_THROW({tk.nextToken();}, pidl::TokenizerError);
}
