#include <iostream>
#include "lexer.h"

int main(){
	std::string input = "2 + (69.420- 12.3 )/88.123) + .23321            z";
	Lexer(input).printTokens();
//	Lexer("+ (())- +/*").printTokens();
	
	
	return 0;
}