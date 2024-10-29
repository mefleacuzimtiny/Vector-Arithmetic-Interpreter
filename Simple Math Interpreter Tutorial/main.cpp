#include "lexer.h"
#include "parser.h"
#include <iostream>
using namespace std;

void divider(int size, char chr = '-'){
	cout << '\n' + string(size, chr) + '\n';
}

int main() {
	Lexer lexer("(7.234 + 123) * 345 --- -+(-2.4 / 1)");
//	Lexer lexer(   "1-(-1+2)"   );
	//	lexer.printTokens();
	Parser parser(lexer.getTokens());
	BinaryNode *tree = parser.parse();
	
	printInOrder(*tree);
	divider(100);
	printPostOrder(*tree);
	divider(100);
	printPreOrder(*tree);
	divider(100);
	
	cout << to_string(evaluate(tree));		// expected output: 42442.034
//	printf("%f",evaluate(tree));
	
	//	std::string input = "2 + (69.420- 12.3 )/88.123) + .23321            ";
	//	Lexer(input).printTokens();
	//	Lexer("+ (())- +/*").printTokens();
	
return 0;
}
