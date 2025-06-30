#include "lexer.h"
#include "tokens.h"
#include "parser.h"
#include "nodes.h"
#include <iostream>
//using namespace std;

enum struct TraversalMode{
	POST_ORDER, PRE_ORDER, IN_ORDER
};

void traverseTree(Node cur_node, TraversalMode mode = TraversalMode::IN_ORDER){
	// if current node is leaf, return
	// print first child
	// print second child
	// print operator
	if(cur_node.children.size() == 0){
		cur_node.printNode();
		return;
	}
	
	using enum TraversalMode;
	
	switch (mode) {
	case PRE_ORDER:
		if(cur_node.type != NodeType::LEAF){
			std::cout << cur_node.getNodeSymbol();
		}
		std::cout << "(";
		traverseTree(cur_node.children[0], PRE_ORDER);
		std::cout << ", ";
		traverseTree(cur_node.children[1], PRE_ORDER);
		std::cout << ")";
		break;
	case IN_ORDER:
		std::cout << "(";
		traverseTree(cur_node.children[0]);
		if(cur_node.type != NodeType::LEAF){
			std::cout << " " << cur_node.getNodeSymbol() << " ";
		}
		traverseTree(cur_node.children[1]);
		std::cout << ")";
		break;
	case POST_ORDER:
		traverseTree(cur_node.children[0], POST_ORDER);
		std::cout << ", ";
		traverseTree(cur_node.children[1], POST_ORDER);
		if(cur_node.type != NodeType::LEAF){
			std::cout << " " << cur_node.getNodeSymbol();
		}
		break;
	default:
		break;
	}
}

Vect evaluate(Node cur_node){
	Vect toReturn, left, right;
	if(cur_node.hasChildren()){						
		left = evaluate(cur_node.children[0]);		// keep going left recursively until no more left nodes (i.e unary parent)
		right = evaluate(cur_node.children[1]);		// go right then keep going left recursively until no more left nodes
	}
	
	switch (cur_node.type) {
	case NodeType::ADD:
		toReturn = left + right;
		break;
	case NodeType::SUB:
		toReturn = left - right;
		break;
	case NodeType::LEAF:
		toReturn.setX(cur_node.x);
		toReturn.setY(cur_node.y);
		break;
	default:
		toReturn.setX(0);
		toReturn.setY(0);
		break;
	}
	return toReturn;
}

int main(){
	Lexer testinput(  "(12.3 9.11) + ({911 WoS 456} - [420.23 .69]) - ((1 45) + {9 now 18})"  );
//	Lexer testinput(  "(12.3 9.11) - [-420.23 .69]"  );
//	Lexer testinput(  "{911 WoS 456} - [420.23 .69]"  );
	Parser abc(testinput);
	
	Node root = abc.generateTree();
	traverseTree(root, TraversalMode::PRE_ORDER);
	std::cout << '\n';
	traverseTree(root, TraversalMode::IN_ORDER);
	std::cout << '\n';
	traverseTree(root, TraversalMode::POST_ORDER);
	std::cout << '\n';
	
	std::cout << "------------------ RESULT -----------------" << '\n';
	evaluate(root).printVect(VectMode::CVECT);
	evaluate(root).printVect(VectMode::PVECT);
	evaluate(root).printVect(VectMode::RVECT);
	return 0;
}
