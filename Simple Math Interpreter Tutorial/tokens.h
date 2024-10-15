#ifndef TOKENS_H
#define TOKENS_H
#include <string>

enum class TokenType{
	ILLEGAL, NUMBER, PLUS, MINUS, MULTIPLY, DIVIDE, LPAREN, RPAREN, END_OF_LINE, START_OF_LINE
};

struct Token{
	public:
		TokenType type;
		std::string value;
		
		Token(TokenType t, std::string v){
			type = t;
			value = v;
		}
};


#endif