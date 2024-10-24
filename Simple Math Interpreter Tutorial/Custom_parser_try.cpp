//parser2.cpp
//#include "nodes.h"
#include "tokens.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*Idea #1: Simulated memory
	Let n be the number of non-bracket tokens, and create an array of the tokens. The pointers to manage
	are just going to be indexes in this array rather than in memory. Managed by a binary tree structure
	a set number of nodes.
	
Idea #2: Upside-Down Tree [Bad idea. Traversal too difficult]
	Instead of leading a parent to two child nodes, you create two child nodes first, and then create the parent
	node to connect them using Node.setParent(ParentNode). To determine the direction of the node, have a 
	Node.direction attribute that determines if the node is left or right.
	
Idea #3: Unique classes for directions [Bad idea. Recursion becomes annoying]
	Let LeftNode and RightNode be separate classes. Instead of pointers, the subsbequent binary nodes should be
	a left node and a right node object that are uniquely created whenever a new node is made. 
*/

enum struct Type{
	ADD, SUB, MUL, DIV, NUM, DEFAULT
};

struct Node{
	Type type;
	std::string value;
	int left;
	int right;
	
	Node(Type t = Type::DEFAULT, std::string str = "", int l = 0, int r = 0)
	: value{str}
	, type{t}
	, left{l}
	, right{r}{
	}
};

/*	////////////////////////////// REFERENCE CODE //////////////////////////
class Node:
    def __init__(self, data, nextPtr):
        self.data = data
        self.nextPtr = nextPtr

class RAM:
    def __init__(self, size):
        self.size = size
        self.contents = [Node(data = '', nextPtr=i) for i in range(1, self.size+1)]
        self.contents[self.size-1].nextPtr = -1
        self.__freePtr = 0

    def malloc(self):
        current = self.__freePtr
        self.__freePtr = self.contents[self.__freePtr].nextPtr
        return current
    def free(self, addr):
        old_FreePtr = self.__freePtr
        self.__freePtr = addr
        self.contents[self.__freePtr].nextPtr = old_FreePtr
    def isFull(self):
        return self.__freePtr == -1
        
//////////////////////////// END OF REFERENCE CODE //////////////////////////*/

class RAM{
	int FREE = 0;
public:
	int size;
	vector <Node> memory;
	
	RAM(int s){
		size = s;
	
		for (int i = 0; i < size; i++){
			memory.push_back(Node(Type::DEFAULT, "", i+1, FREE));
		}
		memory[size-1].left = -1;		// set final pointer to -1
	}
	
	
	int alloc(){
		if (not isFull()){
			int current = FREE;
			FREE = memory[FREE].left;
			return current;
		}
		else{
			cout << "No more space in RAM\n";
			return -1;
		}
	}
	void free(int addr){
		int old_freeptr = FREE;
		FREE = addr;
		memory[FREE].left = old_freeptr;
	}
	bool isFull(){
		return (FREE == -1);
	}
};

struct Tree{
	RAM memory(10);
	int pRoot = ram.alloc();
	
	void inOrder(Node start_node){
		int pCurNode = pRoot;
		cout << TreeBlock[pCurNode] <<'\n';
		
		if (pCurNode != -1){
			inOrder(Start)
		}
	}
/*	Node ADDnode(string data, int lChild, int rChild){
		return Node(NodeType::ADD, data, lChild, rChild);
	}
	Node SUBnode(string data, int lChild, int rChild){
		return Node(NodeType::SUB, data, lChild, rChild);
	}
	Node MULnode(string data, int lChild, int rChild){
		return Node(NodeType::MUL, data, lChild, rChild);
	}
	Node DIVnode(string data, int lChild, int rChild){
		return Node(NodeType::DIV, data, lChild, rChild);
	}
	Node NUMnode(string data){
		return Node(NodeType::NUM, data, nullptr, nullptr);
	}*/
	
};



struct Parsed{
	Tree binTree;
	int count_nodeTokens;
	
	
	Parsed(vector<Token> t){
		for (int i = 0; i < t.size(); i++){
			if (isNodeType(t[i].type)){
				count_nodeTokens++;
			}
		}
	}
	
	bool isNodeType(TokenType query){
		TokenType nodeTypes[] = {TokenType::PLUS, TokenType::MINUS, TokenType::DIVIDE, TokenType::MULTIPLY, TokenType::NUMBER};
		
		for(int i = 0; i < *inside.size(); i++){
			if (nodeTypes[i] == query){
				return true;
			}
		return false;
		}
	}
	
};




/**************** TESTING ***************
# print(Memory._RAM__freePtr)

# address = Memory.malloc()
# print(Memory._RAM__freePtr)

# Memory.contents[address].data = 'peepeepoopoo'
# print(Memory.contents[address].data)

# Memory.free(address)
# print(Memory._RAM__freePtr)
****************************************/

int main(){
/*	Node root (NodeDir::ROOT, Type::ADD, nullptr);
	Node a (NodeDir::LEFT, Type::MUL, &root);
	Node b (NodeDir::RIGHT, Type::NUM, &root, "12");
	Node c (NodeDir::LEFT, Type::NUM, &a, "6");
	Node d (NodeDir::LEFT, Type::NUM, &a, "3");*/
//	c, a, d, root, b
	
/*	RAM ram(5);
	
	int rootAddr = ram.alloc();
	ram.memory[rootAddr].value = "abc";
	
	int pA = ram.alloc();
	int pB = ram.alloc();
	ram.memory[rootAddr].left = pA;
	ram.memory[rootAddr].right = pB;
	
	
	cout << ram.memory[rootAddr].left <<'\n';
	cout << ram.memory[rootAddr].right <<'\n';
	ram.free(pA);
	cout <<ram.alloc() << '\n';
	cout <<ram.alloc() << '\n';
	cout <<ram.alloc() << '\n';*/
	
	Parsed tree(tokens);
	tree.
	
	
	
	return 0;
}

