#include <iostream>
#include <string>
using namespace std;

struct CardinalVector {
	float magnitude;
	float angle;
	string cardinal;
};

struct PolarVector {
	float magnitude;
	float angle;
};

struct RectangularVector {
	float x;
	float y;
};

CardinalVector parseCVector(char unary, string vect){
	
}

RectangularVector parseRVector(char unary, string vect){
	
}

PolarVector parsePVector(char unary, string vect){
	
}

int parseParen(string vect){
	int eol = vect.length();
	int i = 0;
	string cVect = "";
	string rVect = "";
	string pVect = "";
	char chr;
	char unary;
	bool hasUnary = false;
	
	while (i < eol){
		chr = vect[i];
		if (chr == '+'){
			hasUnary = true;
			unary = chr;
		}
		else if (chr == '-'){
			hasUnary = true;
			unary = chr;
		}
		
		if (hasUnary){
			
			if (chr == '{'){
				chr = vect[++i];
				while (chr != '}'){
					cVect += chr;
					chr = vect[++i];
					if (i == eol){
						cout << "Error: Unterminated {" << endl;
						return 0;
						break;
					}
				}
				hasUnary = false;
				cout << unary << cVect << endl;
				// parseCVector(unary, cVect);
			}
			else if (chr == '['){
				chr = vect[++i];
				while (chr != ']'){
					rVect += chr;
					chr = vect[++i];
					if (i == eol){
						cout << "Error: Unterminated ]" << endl;
						return 0;
						break;
					}
				}
				hasUnary = false;
				cout << unary << rVect << endl;
				// parseRVector(unary, rVect);
			}
			else if (chr == '('){
				chr = vect[++i];
				while (chr != ')'){
					pVect += chr;
					chr = vect[++i];
					if (i == eol){
						cout << "Error: Unterminated )" << endl;
						return 0;
						break;
					}
				}
				hasUnary = false;
				cout << unary << pVect << endl;
				// parsePVector(unary, pVect);
			}
		}
		i++;
	}
	return 0;
}


int main(){
//	string input;
//	cout << "Input: "; cin >> input;
	parseParen("  + [num num] + (num ang) - {num car ang}");
	
	// special case: two vectors cannot be side by side without an operator between them
	return 0;
}