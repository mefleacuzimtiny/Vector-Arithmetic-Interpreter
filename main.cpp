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
	traverseTree(cur_node.children[0]);
	traverseTree(cur_node.children[1]);
	if(cur_node.type == NodeType::VECT){
		cur_node.printNode();
		return;
	}
}

int main(){
	Lexer peepee(  "(12.3 9.11) + {911 WoS 456} - [420.23 .69] + {12361 now 456}"  );
	Parser abc(peepee);
	
	Node root = abc.generateTree();
//	std::cout << root.children[0].strType() << '\n';;
	root.showChildren();
//	traverseTree(root, TraversalMode::IN_ORDER);
	
	return 0;
}
