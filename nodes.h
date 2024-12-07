#ifndef CVECTCALC_HEADER_NODES
#define CVECTCALC_HEADER_NODES

#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

enum struct NodeType{
	ADD, SUB, DOT, CROSS, VECT, UNARY_MINUS, UNARY_PLUS, DEFAULT
};
std::unordered_map <NodeType, std::string> NodeTypeNames {
	{NodeType::ADD, "ADD"},
	{NodeType::SUB, "SUB"},
	{NodeType::DOT, "DOT"},
	{NodeType::CROSS, "CROSS"},
	{NodeType::VECT, "VECT"},
	{NodeType::UNARY_MINUS, "UNARY_MINUS"},
	{NodeType::UNARY_PLUS, "UNARY_PLUS"},
	{NodeType::DEFAULT, "DEFAULT"}
};

struct Node{
	NodeType type;
	float x;
	float y;
	std::vector <Node> children;
	
	Node(NodeType t = NodeType::DEFAULT, float X = 0, float Y = 0):
		type{t},
		x{X},
		y{Y}
	{}
	
	void flipsign(){
		x = -x;
		y = -y;
	}
	
	std::string getNodeTypeName(){
		return NodeTypeNames[type];
	}
	
	std::string getNodeSymbol(){
		switch (type) {
		case NodeType::ADD:
			return "+";
			break;
		case NodeType::SUB:
			return "-";
			break;
		case NodeType::UNARY_PLUS:
			return "+";
			break;
		case NodeType::UNARY_MINUS:
			return "-";
			break;
		default:
			return "";
			break;
		}
	}
	
	std::string repr(){
		return "[" + std::to_string(x) + " " + std::to_string(y) + "]";
	}
	void printNode(){
		// std::cout << " [" << x << " " << y <<"] ";
		std::cout << " " << repr() << " ";
	}
	std::string strType(){
		return NodeTypeNames[type];
	}
	void showChildren(){
		std::cout << children.size() << '\n';
		for(int i=0; i < children.size(); i++){
			std::cout << children[i].strType() << '\n';
		}
	}
};
#endif
