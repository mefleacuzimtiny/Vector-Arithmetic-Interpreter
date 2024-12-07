#include "lexer.h"
#include "parser.h"
#include <iostream>
#include <string>
using namespace std;

void divider(int size, char chr = '-'){
	cout << '\n' + string(size, chr) + '\n';
}

int main() {
	string input = "Welcome to CodePulse's Simple Math Interpreter (in C++ by MeFlea). Type in your expression or enter 'q' to quit.";
	cout << input << '\n';
	while (input != "q"){
		cout << "> "; getline(cin, input);
		Lexer lexer(input);
//		lexer.printTokens()
		Parser parser(lexer.getTokens());
		BinaryNode *tree = parser.parse();
//		printInOrder(*tree);
//		divider(100);
//		printPreOrder(*tree);
//		divider(100);
//		printPostOrder(*tree);
//		divider(100);
		cout << '\n' << to_string(evaluate(tree)) << '\n';
		divider(100);
		wipeTree(tree);
		divider(100);
	}
	return 0;
	
	
//	Lexer lexer("(7.234 + 123) * 345 --- -+(-2.4 / 1) - -69");
////	Lexer lexer("3/3*4");
////	Lexer lexer(   "1-(-1+2)"   );
//	//	lexer.printTokens();
//	Parser parser(lexer.getTokens());
//	BinaryNode *tree = parser.parse();
	
//	
//	cout << to_string(evaluate(tree)) << '\n';		// expected output: 42442.034
//	divider(100);
//	
////	printInOrder(*tree);
////	divider(100);
//	printPostOrder(*tree);
////	divider(100);
////	printPreOrder(*tree);
//	divider(100);
//	
//	wipeTree(tree);
//	if (tree == nullptr){
//		cout << "\ntree became null\n";
//	}
//	
////	printPreOrder(*tree);
//	divider(100);
////	cout << to_string(evaluate(tree)) << '\n';		// expected output: 42442.034
//	
////	printInOrder(*tree);
////	divider(100);
////	printPostOrder(*tree);
////	divider(100);
//	
////	divider(100);
////	printf("%f",evaluate(tree));
//	
//	//	std::string input = "2 + (69.420- 12.3 )/88.123) + .23321            ";
//	//	Lexer(input).printTokens();
//	//	Lexer("+ (())- +/*").printTokens();
//	
//	return 0;
}
