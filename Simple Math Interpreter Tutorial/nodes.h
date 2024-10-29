#ifndef NODES_H
#define NODES_H
#include <iostream>
#include <string>

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
		cout << ")";
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
		cout << ")";
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




/*int main(){
//	BinaryNode a(12);
//	BinaryNode b(69);
//	BinaryNode c(420);
//	BinaryNode d(2000);
//	BinaryNode e(10);
	
//	a.left = &b;
//	a.right = &d;
//	b.right = &c;
//	b.left = &e;
	
	BinaryNode a(NodeType::MUL);
	BinaryNode b(NodeType::NUM, 12321);
	BinaryNode c(NodeType::NUM, 78909);
	
	a.left =  &b;
	a.right = &c;
	a.print();
	
	printInOrder(a);
	divider(100);
	printPreOrder(a);
	divider(100);
	printPostOrder(a);
	divider(100);
	
//	cout << (*a.left).data << endl;

//	cout << (*(*a.left).right).data << endl;		// this is why we use the arrow instead
//	cout << a.left->right->data << endl;

	
	
}*/


#endif





