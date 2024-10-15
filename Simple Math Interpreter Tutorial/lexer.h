#ifndef LEXER_H
#define LEXER_H
#include "tokens.h"
#include <string>
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>

class Lexer{
	public:
		int pos, eol;
		char chr;
		std::string str;
		
		Lexer(std::string input_str){
			str = input_str;
			pos = 0;
			eol = str.length();
			chr = str[pos];
		}
		
		void advance(){
			if (pos == eol) return;
			chr = str[++pos];
		}
		
		Token genNumber(){
			std::string valstr = "";
			
			int dots = 0;
			while (pos < eol && (chr == '.' || std::isdigit(chr))){
				if (chr == '.'){
					dots++;
				}
				if (dots > 1){
					// break;
					throwSyntaxError();
				}
				valstr += chr;
				advance();
			}
			if (valstr[0] == '.'){
				valstr = "0" + valstr;
			}
			if (valstr.back() == '.'){
				valstr += "0";
			}
			
			chr = str[--pos];				// decrementing to prevent genNumber() skipping over the character after the NUMBER
											// needs to be done for every token that has more than one characters or needs an internal loop
			
			return Token(TokenType::NUMBER, valstr);
			
		}
		
		void throwSyntaxError(){
				std::string errmsg = "Invalid token '";
				errmsg += chr;
				errmsg += "' at position ";
				errmsg += std::to_string(pos);
				throw std::invalid_argument(errmsg);
		}
		
		Token lexToken(){
			Token curToken(TokenType::ILLEGAL, "");		// Illegal token by default if none of the tokens are recognized
			
			while (pos < eol && chr == ' '){		// skips all immediate spaces
				advance();
			}
			
			if (pos == eol){
				curToken.type = TokenType::END_OF_LINE;
			}
			else{
				if (std::isdigit(chr) or chr == '.'){
					curToken = genNumber();
				}
				else if (chr == '+'){
					curToken = Token(TokenType::PLUS, std::string(1, chr));
				}
				else if (chr == '-'){
					curToken = Token(TokenType::MINUS, std::string(1, chr));
				}
				else if (chr == '*'){
					curToken = Token(TokenType::MULTIPLY, std::string(1, chr));
				}
				else if (chr == '/'){
					curToken = Token(TokenType::DIVIDE, std::string(1, chr));
				}
				else if (chr == '('){
					curToken = Token(TokenType::LPAREN, std::string(1, chr));
				}
				else if (chr == ')'){
					curToken = Token(TokenType::RPAREN, std::string(1, chr));
				}
/*				else if (chr == '+'){
					curToken.type = TokenType::MULTIPLY;
					curToken.value = chr;
				}
				else if (chr == '+'){
					curToken.type = TokenType::MULTIPLY;
					curToken.value = chr;
				}
				else if (chr == '+'){
					curToken.type = TokenType::MULTIPLY;
					curToken.value = chr;
				}
				else if (chr == '+'){
					curToken.type = TokenType::MULTIPLY;
					curToken.value = chr;
				}
				else if (chr == '+'){
					curToken.type = TokenType::MULTIPLY;
					curToken.value = chr;
				}
				else if (chr == '+'){
					curToken.type = TokenType::MULTIPLY;
					curToken.value = chr;
				}
				*/
			}
			
			
			if (curToken.type == TokenType::ILLEGAL){
				throwSyntaxError();
			}
			
			advance();
			
			return curToken;
		}
		
		std::vector<Token> getTokens(){
			std::vector<Token> toReturn;
			Token token = Token(TokenType::START_OF_LINE, "");
			while (token.type != TokenType::END_OF_LINE){
				token = lexToken();
				toReturn.push_back(token);
			}
			return toReturn;
		}
		
		void printTokens(){
			
			std::map<TokenType, std::string> typetostr{
				{TokenType::ILLEGAL , "ILLEGAL"},
				{TokenType::NUMBER , "NUMBER"},
				{TokenType::PLUS , "PLUS"},
				{TokenType::MINUS , "MINUS"},
				{TokenType::MULTIPLY , "MULTIPLY"},
				{TokenType::DIVIDE , "DIVIDE"},
				{TokenType::LPAREN , "LPAREN"},
				{TokenType::RPAREN , "RPAREN"},
				{TokenType::END_OF_LINE , "END_OF_LINE"},
				{TokenType::START_OF_LINE , "START_OF_LINE"}
			};
			
			
			std::vector<Token> toPrint = getTokens();
			for (int i = 0; i < toPrint.size(); i++){
				Token curToken = toPrint.at(i);
				std::cout << "Type: " << typetostr[curToken.type] << ", Value: " << curToken.value << '\n';
//				std::cout << "Value: " << curToken.value << '\n';
			}
		}
	
};

#endif




