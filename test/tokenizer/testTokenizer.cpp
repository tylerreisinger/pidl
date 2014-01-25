#include <iostream>

#include "Tokenizer.h"
#include "Exceptions/TokenizerError.h"



int main(int argc, char** argv)
{
	try
	{
		pidl::Tokenizer tokenizer("0x55 \"Hi\" //A comment\n /*Blocky*/ myIdenty ()");
		while(!tokenizer.endOfInput())
		{
			pidl::Token token = tokenizer.nextToken();
			std::cout << token << std::endl;
		}
	}
	catch(pidl::TokenizerError& ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	return 0;
}
