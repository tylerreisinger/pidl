#include "Parser.h"
#include "Tokenizer.h"

#include <iostream>

#include "Exceptions/TokenizerError.h"
#include "Exceptions/ParserError.h"

int main(int argc, char** argv)
{
	std::string input =\
R"(
namespace pk.stuff

constant TEAM_INDEX = 5

enum Color
{
    Red = 1,
    Blue = 2,
    Green = 3
}

packet PlayerJoinPacket
{
    req f32 x : 1,
    req f32 y : 2,
    opt uint32 color : 0x3,
    opt int32 team : TEAM_INDEX,    

    opt string name : 6,

    opt bytearray extra : 7
}
)";

	try
	{
		pidl::Tokenizer tokenizer(input);
		while(!tokenizer.isEndOfInput())
		{
			pidl::Token token = tokenizer.nextToken();
			std::cout << token << std::endl;
		}
	}
	catch(pidl::TokenizerError& ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	std::cout << "---" << std::endl;
	try
	{
		pidl::Parser parser(std::unique_ptr<pidl::Tokenizer>(new pidl::Tokenizer(input)));
		while(!parser.isEndOfStream())
		{
			auto node = parser.readNext();
			if(node)
			{
				node->outputTree(std::cout);
			}
		}
	}
	catch(pidl::ParserError& ex)
	{
		std::cerr << ex.what() << std::endl;
	}



}
