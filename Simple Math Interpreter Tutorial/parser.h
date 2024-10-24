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
   		
		/*Parser(std::vector<Token> t){
			token_list = t;
			curToken = token_list.at(0);
			endoftokens = token_list.size();
		}*/
		
		void advance(){
			if (token_index == endoftokens){
				return;
			}
			curToken = token_list.at(++token_index);
		}
		
		void raiseError(){
			std::cout << "\nError output:\n";
			curToken.printType();
			
			std::string errmsg = "Bad Token '";
			errmsg += curToken.value;
			errmsg += "'.";
			
			throw std::invalid_argument(errmsg);
		}
		
		// DOCSTR [1] here.
		
		BinaryNode* parse(){
			BinaryNode* root = nullptr;
			
			if (endoftokens == 0){
				return root;
			}
			
			root = expression();			// addition or subtraction
			
			return root;
		}
		
		
		BinaryNode* expression(){				// addition or subtraction
			BinaryNode* rChild; 
			BinaryNode* result;
			result = term();
			
			while (not (token_index == endoftokens) && (curToken.type == TokenType::PLUS || curToken.type == TokenType::MINUS)){
				if (curToken.type == TokenType::PLUS){
					advance();
					rChild = term();
					result = new BinaryNode(NodeType::ADD, 0, result, rChild);
//					result = new ADDnode("*", result, rChild);
					
				}
				else if (curToken.type == TokenType::MINUS){
					advance();
					rChild = term();
					result = new BinaryNode(NodeType::SUB, 0, result, rChild);
				}
			}
			return result;
		}
		BinaryNode* term(){				// addition or subtraction
			BinaryNode* rChild;
			BinaryNode* result;
			result = factor();
			
			while (not (token_index == endoftokens) && (curToken.type == TokenType::MULTIPLY || curToken.type == TokenType::DIVIDE)){
				if (curToken.type == TokenType::MULTIPLY){
					advance();
					rChild = factor();
					result = new BinaryNode(NodeType::MUL, 0, result, rChild);
				}
				else if (curToken.type == TokenType::DIVIDE){
					advance();
					rChild = factor();
					result = new BinaryNode(NodeType::DIV, 0, result, rChild);
				}
			}
			return result;
		}
		
		BinaryNode* factor(){					// Number
//			Token token = curToken;
			BinaryNode leaf;
			BinaryNode* pleaf = &leaf;
			
			if (curToken.type == TokenType::NUMBER){
				pleaf = new BinaryNode(NodeType::NUM, stof(curToken.value));
				advance();
				return pleaf;
			}
			
			raiseError();
			return nullptr;
		}
	
};
#endif




