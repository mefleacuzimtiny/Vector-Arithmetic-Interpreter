#ifndef CVECTCALC_HEADER_LEXER
#define CVECTCALC_HEADER_LEXER
#include <string>
#include "tokens.h"


class Lexer {
	std::string str;
	int pos;
	size_t eol;
	char chr;
public:
	std::vector<Token> tokens;
//	Lexer(std::string input_str): 
//		str{input_str},
//		pos{0},
//		eol{input_str.length()-1},
//		chr{str[pos]}
//	{}
	Lexer(std::string input_str){
		str = input_str;
		pos = 0;
		eol = input_str.length();
		chr = str[pos];
		assembleTokens();
	}
	std::string getStr(){
		return str;
	}
	bool end(){
		return pos == eol;
	}
	void nextChr() {
		if (pos == eol) return;
		chr = str[++pos];
	}
	void prevChr() {
		if (pos == 0) return;
		chr = str[--pos];
	}
	void tokenError(std::string errmsg){
		throw std::invalid_argument(errmsg);
	}
	Token genNumber(){
		Token toReturn(TokType::NUMBER, "", pos);
		int dots = 0;
		while(pos!=eol && (std::isdigit(chr) || chr == '.')){
			if(chr == '.'){
				dots++;
			}
			if(dots > 1){
				toReturn.type = TokType::ILLEGAL;
				tokenError("Number cannot have more than 1 decimal");
				break;
			}
			toReturn.data += chr;
			nextChr();
		}
		prevChr();				// decrementing to prevent genNumber() skipping over the character after the NUMBER
		
		if(toReturn.data[0] == '.'){
			toReturn.data = '0' + toReturn.data;
		}
		if(toReturn.data.back() == '.'){
			toReturn.data += '0';
		}
		return toReturn;
	}
	Token genBareword(){
		Token toReturn(TokType::BAREWORD, "", pos);
		while(pos!=eol && (std::isalpha(chr))){
			toReturn.data += chr;
			nextChr();
		}
		prevChr();				// decrementing to prevent genBareword() skipping over the character after the BAREWORD
		return toReturn;
	}
	
	
	//______________OUTLINE_______________
	
	// current token is illegal by default
	
	// skip all initial spaces
	
	// if eol, eol token
	
	// else, token cases
	
	// if illegal token, error
	
	// advance to next char
	
	// return current token
	//------------------------------------
	
	Token lexToken(){
		
		Token curToken(TokType::ILLEGAL, "", pos);
		
		while(pos < eol && chr == ' '){
			nextChr();
		}
		
		if(pos == eol){
			curToken.type = TokType::EOL;
		}else{
			if(std::isdigit(chr) || chr == '.'){
				curToken = genNumber();
				
			}else if(std::isalpha(chr)){
				curToken = genBareword();
				
			}else if(symboltotype.count(chr)){
				curToken.type = symboltotype[chr];
				curToken.data += chr;
			}
		}
		
		if(curToken.type == TokType::ILLEGAL){
			tokenError("Unknown token " + curToken.data);
		}
		nextChr();
		return curToken;
	}
	
	void assembleTokens(){
		Token curToken(TokType::DEFAULT, "", pos);
		while(curToken.type != TokType::EOL){
			curToken = lexToken();
//			curToken.printType();
			tokens.push_back(curToken);
		}
	}
	
	void printTokens(){
		// assembleTokens();
		for(int i=0;i<tokens.size();i++){
			Token curToken = tokens[i];
			std::cout << "Type: " << TokenTypeNames[curToken.type] << ", Value: " << curToken.data << '\n';
		}
	}
};

#endif
