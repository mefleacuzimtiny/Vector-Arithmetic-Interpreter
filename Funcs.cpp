#include <iostream>
#include <string>
using namespace std;

// ignorables: '.'


bool isDigit(char chr){
	return (47 < chr) and (chr < 58);
}

bool isAlpha(char chr){
	chr = tolower(chr);
	return (96 < chr) and (chr < 123);
}

bool isFloat(string str){
	int endofline = str.length();
//	string strOfTokens = "";
	char chr;
	
	for (int i = 0; i < endofline; i++) {
		chr = str[i];
		
		while (isDigit(chr)) {
			chr = str[++i]; 
		}
		if (not isDigit(chr) and (chr == '.')) {
			chr = str[++i];
			while (isDigit(chr)) {
				chr = str[++i];
			}
		}
		else {
			cout << "INVALID SYNTAX" << endl;
			return false;
		}
	}
	return true;
}

/* two issues: 
	ints don't return true
	invalid character at the very end does not return error
*/

int main(){
	
	cout << isFloat("2342") << endl;		// should be valid
	
	cout << isFloat("0.2342i") << endl;		// should be invalid
	
	return 0;
}