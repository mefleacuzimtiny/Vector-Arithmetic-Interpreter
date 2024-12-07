#ifndef CVECTCALC_HEADER_TOKENS
#define CVECTCALC_HEADER_TOKENS
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

enum struct TokType{
	DEFAULT, CURLY_S, CURLY_E, SQUARE_S, SQUARE_E, ROUND_S, ROUND_E, PLUS, MINUS, ADD, SUB, NUMBER, BAREWORD, ILLEGAL, EOL
};
std::unordered_map <TokType, std::string> TokenTypeNames {
	{TokType::DEFAULT, "DEFAULT"},
	{TokType::CURLY_S, "CURLY_S"},
	{TokType::CURLY_E, "CURLY_E"},
	{TokType::SQUARE_S, "SQUARE_S"},
	{TokType::SQUARE_E, "SQUARE_E"},
	{TokType::ROUND_S, "ROUND_S"},
	{TokType::ROUND_E, "ROUND_E"},
	{TokType::PLUS, "PLUS"},
	{TokType::MINUS, "MINUS"},
	{TokType::NUMBER, "NUMBER"},
	{TokType::BAREWORD, "BAREWORD"},
	{TokType::ILLEGAL, "ILLEGAL"},
	{TokType::EOL, "EOL"}
};


std::unordered_map <char, TokType> symboltotype {
	{'{', TokType::CURLY_S},
	{'}', TokType::CURLY_E},
	{'[', TokType::SQUARE_S},
	{']', TokType::SQUARE_E},
	{'(', TokType::ROUND_S},
	{')', TokType::ROUND_E},
	{'+', TokType::PLUS},
	{'-', TokType::MINUS},
	{'+', TokType::ADD},
	{'-', TokType::SUB}
};
std::unordered_map <TokType, char> typetosymbol {		//for when I need to print out stuff during traversal (mostly for debugging)
	{TokType::CURLY_S, '{'},
	{TokType::CURLY_E, '}'},
	{TokType::SQUARE_S, '['},
	{TokType::SQUARE_E, ']'},
	{TokType::ROUND_S, '('},
	{TokType::ROUND_E, ')'},
	{TokType::PLUS, '+'},
	{TokType::MINUS, '-'},
	{TokType::ADD, '+'},
	{TokType::SUB, '-'}
};

struct Token{
	TokType type = TokType::DEFAULT;
	std::string data;
	std::string cur_pos;
	
	Token(TokType t, std::string d, int cpos):
		type{t},
		data{d},
		cur_pos{std::to_string(cpos)}
	{}
	
	void printType(){
		std::cout << TokenTypeNames[type] << '\n';
	}
	void print(){
		int column_size = 10;
		int num_of_spaces = column_size - TokenTypeNames[type].size();
		
		std::cout << 
			"Type: " << TokenTypeNames[type] << std::string(num_of_spaces, ' ') <<
			"| at: " << cur_pos << 
			" | Value: " << data << 
		'\n';
	}
};

#endif
