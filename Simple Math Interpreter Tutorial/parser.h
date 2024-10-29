#ifndef PARSER_H
#define PARSER_H
#include "nodes.h"
#include "tokens.h"
#include <vector>
#include <string>
#include <iostream>


struct Parser{
	std::vector<Token> token_list;
	Token curToken;
	int token_index = 0;
	size_t endoftokens;
	
	public:
		Parser(const std::vector<Token> &t):
			token_list{ t },
			curToken{ t.at(0) },
	   		endoftokens{ t.size() - 1 } {}
	
		void raiseError(string errmsg){
			std::cout << "\nError output:\n";
			//curToken.printType();
			throw std::invalid_argument(errmsg);
		}
		void advance(){
			if (token_index == endoftokens){
				return;
			}
			curToken = token_list.at(++token_index);
		}
		// DOCSTR [1] here.
	
		BinaryNode* parse(){
			BinaryNode* root = nullptr;
			
			if (endoftokens == 0){				// if no input, just return a null pointer
				return root;
			}
			root = expression();			// begin parsing
			
			if (token_index != endoftokens){	// if we're done parsing the main outer expression and there's leftover tokens, throw an error
				if (curToken.type == TokenType::RPAREN){			// ')' ends the current expression regardless of the existence of a '('
					raiseError("Syntax Error: Uninitiated ')'");	// so an unbalanced ')' would mean the main outer expression ends prematurely,
				}													// causing residual tokens which triggers this error.
				raiseError("Invalid Syntax");
			}
			
			return root;
		}
		
		
		BinaryNode* expression(){				// addition or subtraction
			BinaryNode* rChild; 
			BinaryNode* result;
			result = term();
			
			while (token_index != endoftokens && (curToken.type == TokenType::PLUS || curToken.type == TokenType::MINUS)){
				switch (curToken.type) {
				case TokenType::PLUS:
					advance();
					rChild = term();
					// result = new BinaryNode(NodeType::ADD, result->data + rChild->data, result, rChild);
					result = ADDnode(result->data + rChild->data, result, rChild);
					break;
				case TokenType::MINUS:
					advance();
					rChild = term();
					// result = new BinaryNode(NodeType::SUB, result->data - rChild->data, result, rChild);
					result = SUBnode(result->data - rChild->data, result, rChild);
					break;
				default: break;
				}
			}
			return result;
		}
	
		BinaryNode* term(){				// addition or subtraction
			BinaryNode* rChild;
			BinaryNode* result;
			result = factor();
			
			while (token_index != endoftokens && (curToken.type == TokenType::MULTIPLY || curToken.type == TokenType::DIVIDE)){
				switch (curToken.type) {
				case TokenType::MULTIPLY:
					advance();
					rChild = factor();
					// result = new BinaryNode(NodeType::MUL, result->data * rChild->data, result, rChild);
					result = MULnode(result->data * rChild->data, result, rChild);
					break;
				case TokenType::DIVIDE:
					advance();
					rChild = factor();
					// result = new BinaryNode(NodeType::DIV, result->data / rChild->data, result, rChild);
					result = DIVnode(result->data / rChild->data, result, rChild);
					break;
				default:break;
				}
			}
			return result;
		}
		
		BinaryNode* factor(){					// Number
			BinaryNode leaf;
			BinaryNode* pleaf = &leaf;
			
			switch (curToken.type) {
			case TokenType::LPAREN:
				advance();
				pleaf = expression();
				if(curToken.type != TokenType::RPAREN){
					raiseError("Unterminated '('");
				}
				advance();		// to go past right parenthesis
				return pleaf;
				break;
			case TokenType::NUMBER:
				// pleaf = new BinaryNode(NodeType::NUM, stod(curToken.value));
				pleaf = NUMnode(stod(curToken.value));
				advance();
				return pleaf;
				break;
			case TokenType::PLUS:
				advance();
				pleaf = UNARY_PLUSnode(0,factor());
				//pleaf = NUMnode(stod(curToken.value));
				return pleaf;
				break;
			case TokenType::MINUS:
				advance();
				pleaf = UNARY_MINUSnode(0,factor());
				//pleaf = NUMnode(- stod(curToken.value));
				return pleaf;
				break;
			default:
				raiseError("SyntaxError. Bad Token");
				return nullptr;
				break;
			}
		}
	
};
#endif
