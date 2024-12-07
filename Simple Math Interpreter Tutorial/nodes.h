#ifndef NODES_H
#define NODES_H
#include <iostream>
#include <string>
#include <map>

using namespace std;

void raiseError(string errmsg){
	std::cout << "\nError output:\n";
	//curToken.printType();
	throw std::invalid_argument(errmsg);
}


enum class NodeType{
	ADD, SUB, MUL, DIV, NUM, DEFAULT, UNARY_PLUS, UNARY_MINUS
};

struct BinaryNode{
	public:
		NodeType type;
		double data;
		BinaryNode* left;
		BinaryNode* right;
		
		BinaryNode(NodeType t = NodeType::DEFAULT, double d = 0, BinaryNode* l = nullptr, BinaryNode* r = nullptr){
//			data = d; type = t; left = nullptr; right = nullptr;
			data = d; type = t; left = l; right = r;
		}
	
	string strNodeType(){
		std::map <NodeType, std::string> nodetypestr{
			{NodeType::ADD, "ADD"},
			{NodeType::SUB, "SUB"},
			{NodeType::MUL, "MUL"},
			{NodeType::DIV, "DIV"},
			{NodeType::NUM, "NUM"},
			{NodeType::DEFAULT, "DEFAULT"},
			{NodeType::UNARY_PLUS, "UNARY_PLUS"},
			{NodeType::UNARY_MINUS, "UNARY_MINUS"},
		};
		return nodetypestr[type];
	}
	
	string getNodeSymbol(){
		switch (type) {
		case NodeType::ADD:
			return "+";
			break;
		case NodeType::SUB:
			return "-";
			break;
		case NodeType::MUL:
			return "*";
			break;
		case NodeType::DIV:
			return "/";
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
	
	void print(){
		switch (type){
			case NodeType::ADD:
				cout << "(" << left->data << "+" << right->data << ")\n";
				break;
			case NodeType::SUB:
				cout << "(" << left->data << "-" << right->data << ")\n";
				break;
			case NodeType::MUL:
				cout << "(" << left->data << "*" << right->data << ")\n";
				break;
			case NodeType::DIV:
				cout << "(" << left->data << "/" << right->data << ")\n";
				break;
			default:
			;
		}
	}
};


void printInOrder(BinaryNode start_node){
	BinaryNode* pCurNode = &start_node;
	
	if (pCurNode->left != nullptr){
		cout << "(";
		printInOrder(*pCurNode->left);
		cout << " ";
	}
	
	if(pCurNode->type == NodeType::NUM){
		// cout << "[" << pCurNode->data <<  "]";
		cout << pCurNode->data;
	}
	else{
		cout << pCurNode->getNodeSymbol();
	}
	
	if (pCurNode->right != nullptr){
		cout << " ";
		printInOrder(*pCurNode->right);
		if (pCurNode->type != NodeType::UNARY_PLUS && pCurNode->type != NodeType::UNARY_MINUS){
			cout << ")";
		}
	}
}
void printPreOrder(BinaryNode start_node){
	BinaryNode* pCurNode = &start_node;
	
	if(pCurNode->type == NodeType::NUM){
		// cout << "[" << pCurNode->data <<  "]";
		cout << pCurNode->data;
	}
	else{
		cout << pCurNode->getNodeSymbol();
	}
	
	if (pCurNode->left != nullptr){
		cout << "(";
		printPreOrder(*pCurNode->left);
		cout << ", ";
	}
	
	if (pCurNode->right != nullptr){
		printPreOrder(*pCurNode->right);
		if (pCurNode->type != NodeType::UNARY_PLUS && pCurNode->type != NodeType::UNARY_MINUS){
			cout << ")";
		}
	}
}
void printPostOrder(BinaryNode start_node){
	BinaryNode* pCurNode = &start_node;
	
	if (pCurNode->left != nullptr){
		printPostOrder(*pCurNode->left);
//		cout << ", ";
	}
	if (pCurNode->right != nullptr){
		printPostOrder(*pCurNode->right);
	}
	
	if(pCurNode->type == NodeType::NUM){
		// cout << "[" << pCurNode->data <<  "]";
		cout << pCurNode->data << ", ";
	}
	else{
		cout << pCurNode->getNodeSymbol() << ", ";
	}
}

double evaluate(BinaryNode* start_node){	// get left, get right, combine with middle
	BinaryNode* pCurNode = start_node;
	double toReturn, leftval, rightval;
	
	if (pCurNode->left != nullptr){	
		leftval = evaluate(pCurNode->left);
	}
	if (pCurNode->right != nullptr){
		rightval = evaluate(pCurNode->right);
	}
	switch (pCurNode->type){
	case NodeType::ADD:
		toReturn = leftval + rightval;
		break;
	case NodeType::SUB:
		toReturn = leftval - rightval;
		break;
	case NodeType::MUL:
		toReturn = leftval * rightval;
		break;
	case NodeType::DIV:
		if (rightval == 0){
			raiseError("Cannot divide by zero!");
		}
		toReturn = leftval / rightval;
		break;
	case NodeType::NUM:
		toReturn = pCurNode->data;
		break;
	case NodeType::UNARY_PLUS:
		toReturn = rightval;
		break;
	case NodeType::UNARY_MINUS:
		toReturn = - rightval;
		break;
	default:
		toReturn = 0;
		break;
	}
	return toReturn;
}


BinaryNode* ADDnode(double data, BinaryNode* lChild, BinaryNode* rChild){
	return new BinaryNode(NodeType::ADD, data, lChild, rChild);
}
BinaryNode* SUBnode(double data, BinaryNode* lChild, BinaryNode* rChild){
	return new BinaryNode(NodeType::SUB, data, lChild, rChild);
}
BinaryNode* MULnode(double data, BinaryNode* lChild, BinaryNode* rChild){
	return new BinaryNode(NodeType::MUL, data, lChild, rChild);
}
BinaryNode* DIVnode(double data, BinaryNode* lChild, BinaryNode* rChild){
	return new BinaryNode(NodeType::DIV, data, lChild, rChild);
}
BinaryNode* UNARY_PLUSnode(double data, BinaryNode* rChild){
	return new BinaryNode(NodeType::UNARY_PLUS, data, nullptr, rChild);
}
BinaryNode* UNARY_MINUSnode(double data, BinaryNode* rChild){
	return new BinaryNode(NodeType::UNARY_MINUS, data, nullptr, rChild);
}
BinaryNode* NUMnode(double data){
	return new BinaryNode(NodeType::NUM, data, nullptr, nullptr);
}

int deleted_nodes = 0;

void wipeTree(BinaryNode*& pCurNode){
	if (pCurNode == nullptr){
		return;
	}
	
	wipeTree(pCurNode->left);
	wipeTree(pCurNode->right);
	
	std::cout << "\t| Now deleting: " << pCurNode->strNodeType() << " ";
	delete pCurNode;
	pCurNode = nullptr;
	deleted_nodes++;
	std::cout << "\nDeleted nodes: [" << deleted_nodes << "] ";
}

//void wipeTree(BinaryNode*& pCurNode){
//	if (pCurNode->left != nullptr){
//		wipeTree(pCurNode->left);
//		
//		std::cout << pCurNode->strNodeType();
////		pCurNode->print();
//		
//		delete pCurNode;
//		pCurNode = nullptr;
//	}
//	if (pCurNode->right != nullptr){
//		wipeTree(pCurNode->right);
//		
//		std::cout << pCurNode->strNodeType();
////		pCurNode->print();
//		
//		delete pCurNode;
//		pCurNode = nullptr;
//	}
//}

#endif
