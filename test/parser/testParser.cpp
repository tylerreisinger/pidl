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

[id = 1, channel = 1]
packet PlayerJoinPacket
{
    req f32 x : 1,
    req f32 y : 2,
    [default = Color.Blue]
    opt Color color : 3,
    opt int32 team : TEAM_INDEX,    
    req array<int32> flags : 10,
    [default = "MyName"]
    opt string name : 6,

    opt bytearray extra : 7,
    [default = true]
    opt bool isPrimary : 8
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
