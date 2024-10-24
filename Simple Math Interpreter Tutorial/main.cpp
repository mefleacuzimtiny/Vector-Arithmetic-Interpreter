#include "lexer.h"
#include "parser.h"
#include <iostream>
using namespace std;

int main() {
	Lexer lexer("7.234 + 123 * 345 - 2.4 / 12");
	//	lexer.printTokens();
	Parser parser(lexer.getTokens());
	BinaryNode *tree = parser.parse();
	
	printInOrder(*tree);
	divider(100);
	printPostOrder(*tree);
	divider(100);
	printPreOrder(*tree);
	divider(100);
	
	cout << evaluate(*tree).data;		// expected output: 42439.834
	
	//	std::string input = "2 + (69.420- 12.3 )/88.123) + .23321            ";
	//	Lexer(input).printTokens();
	//	Lexer("+ (())- +/*").printTokens();
	
return 0;
}
