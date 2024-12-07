#ifndef CVECTCALC_HEADER_PARSER
#define CVECTCALC_HEADER_PARSER
#include "tokens.h"
#include "lexer.h"
#include "nodes.h"
#include "vects.h"
#include <vector>
#include <iostream>
#include <string>
#include <array>

std::string multStr(std::string str, int size){
	std::string toReturn = "";
	for(int i=0; i < size; i++){
		toReturn += str;
	}
	return toReturn;
}

struct Parser {
	Lexer lexer;
	int tokIndex = 0;
	Token curToken = lexer.tokens[tokIndex];
	size_t tokEnd = lexer.tokens.size();

	Parser(Lexer L):
		lexer{L}
	{}
	void raiseError(std::string errmsg) {
		std::cout << "\nError output:\n\t";
		//curToken.printType();
		std::cout << lexer.getStr() << '\n';
		std::cout << '\t' << multStr(" ", std::stoi(curToken.cur_pos)) << "^" << '\n';
		errmsg += " at " + curToken.cur_pos;
		throw std::invalid_argument(errmsg);
	}
	void nextToken() {
		if (curToken.type == TokType::EOL) return;
		curToken = lexer.tokens[++tokIndex];
	}
	void prevToken() {
		if (tokIndex == 0) return;
		curToken = lexer.tokens[--tokIndex];
	}

	Node generateTree(){
		Node root_node;
		if(tokEnd == 0){
			return root_node;
		}
		root_node = expression();
		
		if(curToken.type != TokType::EOL){
			raiseError("Syntax Error: Uninitiated ')'");
		}
		return root_node;
	}
	
	Node expression(){
		using enum TokType;
		Node result, new_result;
		result = factor();
		
		while(curToken.type != EOL && (curToken.type == PLUS || curToken.type == MINUS)){	// recursively creates child nodes for operators
			switch (curToken.type) {
			case PLUS:
				nextToken();
				new_result.type = NodeType::ADD;
				new_result.children.push_back(result);
				new_result.children.push_back(factor());
				std::cout << "Created an ADD NODE" << '\n';
				break;
			case MINUS:
				nextToken();
				new_result.type = NodeType::SUB;
				new_result.children.push_back(result);
				new_result.children.push_back(factor());	
				std::cout << "Created an SUB NODE" << '\n';
				break;
			default:break;
			}
		}
		if(result.type != NodeType::DEFAULT) return new_result; 
		return result;
	}
	
	Node factor(){
		Node result;
		bool neg_sign = false;
		switch (curToken.type) {
		// unaryMINUS or unaryPLUS with first (and only) child expression()
		case TokType::PLUS:		// skip arbitrary number of plus signs
			while(curToken.type == TokType::PLUS) nextToken();
			result = factor();
			break;
		case TokType::MINUS:	// skip negative signs while alternating a boolean
			while(curToken.type == TokType::MINUS){
				neg_sign = not neg_sign;
				nextToken();
			}
			result = factor();
			if(neg_sign) result.flipsign();
			
			neg_sign = false;	// resetting neg_sign to default state just in case. Though I don't think this is inherently necessary.
			break;
		case TokType::CURLY_S:
			nextToken();
			result = parseCVECT();
			
			if (curToken.type != TokType::CURLY_E) raiseError("unterminated CVECT"); 
			nextToken();
			break;
		case TokType::SQUARE_S:
			nextToken();
			result = parseRVECT();
			
			if (curToken.type != TokType::SQUARE_E) raiseError("unterminated RVECT"); 
			nextToken();
			break;
		case TokType::ROUND_S:
			nextToken();
			
			if (curToken.type == TokType::NUMBER){
				result = parsePVECT();
				if (curToken.type != TokType::ROUND_E) raiseError("unterminated PVECT"); 
			}
			else if (curToken.type == TokType::ROUND_S){
				result = expression();
				if (curToken.type != TokType::ROUND_E) raiseError("Incomplete Expression. Unterminated '('");
			}
			nextToken();
			break;
		default:
			raiseError("Syntax error: Invalid expression. Unexpected token");
			break;
		}
		return result;
	}
	
	Node parseCVECT(){
		Node result;
		Vect toStore;
		std::array<TokType, 3> format = {TokType::NUMBER, TokType::BAREWORD, TokType::NUMBER};
		std::array<std::string, format.size()> captured;
		
		for(int i=0; i < format.size(); i++){
			TokType type = format[i];
			if(curToken.type == type){
				captured[i] = curToken.data;
				nextToken();
			}else{
				raiseError("expected " + TokenTypeNames[type]);
			}
		}
		
		toStore.setMag(std::stof(captured[0]));
		toStore.setCardinal(captured[1]);
		toStore.setAng(std::stof(captured[2]));
		result.x = toStore.getX();
		result.y = toStore.getY();
		std::cout << "Stored CVECT {" << toStore.getMag() << " " << toStore.getCardinal() << " " << toStore.getAng() << "} as " << "[" << result.x << " " << result.y << "]"<< '\n';
		return result;
	}
	Node parsePVECT(){
		// just use basic trig and stuff to convert to RVECT
		Node result;
		Vect toStore;
		std::array<TokType, 2> format = {TokType::NUMBER, TokType::NUMBER};
		std::array<std::string, format.size()> captured;
		
		for(int i=0; i < format.size(); i++){
			TokType type = format[i];
			if(curToken.type == type){
				captured[i] = curToken.data;
				nextToken();
			}else{
				raiseError("expected " + TokenTypeNames[type]);
			}
		}
		toStore.setMag(std::stof(captured[0]));
		toStore.setAng(std::stof(captured[1]));
		
		result.x = toStore.getX();
		result.y = toStore.getY();
		std::cout << "Stored PVECT (" << toStore.getMag() << " " << toStore.getAng() << ") as " << "[" << result.x << " " << result.y << "]"<< '\n';
		return result;
	}
	Node parseRVECT(){
		// get x and y directly
		Node result;
		Vect toStore;
		std::array<TokType, 2> format = {TokType::NUMBER, TokType::NUMBER};
		std::array<std::string, format.size()> captured;
		
		for(int i=0; i < format.size(); i++){
			TokType type = format[i];
			if(curToken.type == type){
				captured[i] = curToken.data;
				nextToken();
			}else{
				raiseError("expected " + TokenTypeNames[type]);
			}
		}
		toStore.setX(std::stof(captured[0]));
		toStore.setY(std::stof(captured[1]));
		result.x = toStore.getX();
		result.y = toStore.getY();
		std::cout << "Stored RVECT [" << toStore.getX() << " " << toStore.getY() << "] as " << "[" << result.x << " " << result.y << "]"<< '\n';
		return result;
	}


//	void printthemtokens() {
//		while(curToken.type != TokType::EOL){
////		while(i < 20){
////		while (tokIndex != tokEnd) {
//			curToken.print();
//			nextToken();
//		}
//	}
};



#endif
/*
PLAN:

first function:
	if empty input, return node with nothing
	root is an expression (addition or subtraction)
	We're done parsing, so if leftover tokens, throw unitiated ')' error because ')' ends the current expression regardless of the existence of a '('

sescond function i.e expression:
	result is a factor()
	while addition or subtraction:
		new_result is operation with first child result and second child factor()

third function i.e factor:
	if MINUS or PLUS:
		unaryMINUS or unaryPLUS with first (and only) child expression()
	elif CURLY_S:
		nextToken()
		parseCVECT()
		if not CURLY_E: error, unterminated CVECT
	elif SQUARE_S:
		nextToken()
		parseRVECT()
		if not SQUARE_E: error, unterminated RVECT
	elif ROUND_S:
		nextToken()
		if NUMBER:
			parsePVECT()
		if not ROUND_E: error, unterminated PVECT
		elif ROUND_S:
			expression()
		if not ROUND_E: error, Incomplete Expression. Unterminated '('.
	else: error, Syntax error: unexpected token. Invalid expression.

def parseCVECT() -> Vector Node
	format = [NUMBER, BAREWORD, NUMBER]
	for item in format:
		if token.type == item:
			capture
			nextToken()
		else:
			error, missing {item}
	if CURLY_E, return
	else, error, too many values for Cardinal Vector

def parsePVECT() -> Vector Node
	format = [NUMBER , NUMBER]
	for item in format:
		if token.type == item:
			capture
			nextToken()
		else:
			error, missing {item}
	if CURLY_E, return
	else, error, unterminated '('

def parseRVECT() -> Vector Node
	format = [NUMBER , NUMBER]
	for item in format:
		if token.type == item:
			capture
			nextToken()
		else:
			error, missing {item}
	if CURLY_E, return
	else, error, unterminated '('

*/
