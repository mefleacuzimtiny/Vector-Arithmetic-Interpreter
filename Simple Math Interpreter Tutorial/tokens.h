#ifndef TOKENS_H
#define TOKENS_H
#include <string>
#include <iostream>

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
		
		void printType(){
		
			switch (type){
				case TokenType::ILLEGAL:
					std::cout << "Type: " << "ILLEGAL" <<'\n';
					break;
				case TokenType::NUMBER:
					std::cout << "Type: " << "NUMBER" <<'\n';
					break;
				case TokenType::PLUS:
					std::cout << "Type: " << "PLUS" <<'\n';
					break;
				case TokenType::MINUS:
					std::cout << "Type: " << "MINUS" <<'\n';
					break;
				case TokenType::MULTIPLY:
					std::cout << "Type: " << "MULTIPLY" <<'\n';
					break;
				case TokenType::DIVIDE:
					std::cout << "Type: " << "DIVIDE" <<'\n';
					break;
				case TokenType::LPAREN:
					std::cout << "Type: " << "LPAREN" <<'\n';
					break;
				case TokenType::RPAREN:
					std::cout << "Type: " << "RPAREN" <<'\n';
					break;
				case TokenType::END_OF_LINE:
					std::cout << "Type: " << "END_OF_LINE" <<'\n';
					break;
				case TokenType::START_OF_LINE:
					std::cout << "Type: " << "START_OF_LINE" <<'\n';
					break;
			};
		}
};


#endif
