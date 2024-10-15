#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <vector>
using namespace std;

#define PI 3.14159265


void divider(){
	cout << "===============================================\n";
}

bool isAlpha(char chr){
	return ((96 < chr) and (chr < 123));
}


bool isDigit(char chr){
	return (47 < chr and chr < 58);
}

string stripExcessSpaces(string str){
	char chr;
	int start = 0;
	chr = str[start];
	while (chr == ' '){
		chr = str[++start];
	}
	
	int end =  str.length() - 1;
	chr = str[end];
	while (chr == ' '){
		chr = str[--end];
	}
	
	
	return str.substr(start, end-start +1);
}



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
	
	PolarVector toPolar(){
		PolarVector toReturn;
		toReturn.magnitude = sqrt((pow(x, 2)) + (pow(y, 2)));
		toReturn.angle = atan(y/x) * 180/PI;
		
		return toReturn;
	}
	
	CardinalVector toCardinal(){
		CardinalVector toReturn;
		toReturn.magnitude = sqrt((pow(x, 2)) + (pow(y, 2)));
		
		float angle = atan(y/x) * 180/PI;
		string cardinal;
		
	
		map<float, string> angles {
			{0, "e"},
			{90, "n"},
			{180, "w"},
			{270, "s"}
		};
	
		if (angle < 90){
			if (angle <= 45){
				cardinal = "NoE";
				
			}
			else{
				cardinal = "EoN";
			}
		}
		else if (angle < 180){
			if (angle <= 135){
				cardinal = "WoN";
				angle -= 90;
			}
			else{
				cardinal = "NoW";
				angle = 180 - angle;
			}
		}
		else if (angle < 270){
			if (angle <= 225){
				cardinal = "SoW";
				angle -= 180;
			}
			else{
				cardinal = "WoS";
				angle = 270 - angle;
			}
		}
		else if (angle < 360){
			if (angle <= 315){
				cardinal = "EoS";
				angle -= 270;
			}
			else{
				cardinal = "SoE";
				angle = 360 - angle;
			}
		}
		else{
			cardinal = angles[angle];
		}
	
		toReturn.cardinal = cardinal;
		toReturn.angle = angle;
		
		return toReturn;
	}
	
};

/*CardinalVector parseCVector(char unary, string vect){
	CardinalVector toReturn;
	int eol = vect.length();
	int tokenpos = 0;
//	string magnitude = "";
//	string angle = "";
	string cardinal = "";
	string numerical = "";
	char chr;
	int i = 0;
	while (i < eol){
		// digit(s), optional dot, digit(s), word, digit(s), optional dot, digit(s)
		chr = vect[i];
		
		if (isDigit(chr)){
			chr = vect[++i];
			cout << chr << i << endl;
			while (isDigit(chr)){
				numerical += chr;
				chr = vect[++i];
			}
			tokenpos++;
		}
		else if (chr == '.'){ 
			numerical += '.';
			chr = vect[++i];
			while (isDigit(chr)){
				numerical += chr;
				chr = vect[++i];
			}
			tokenpos++;
		}
		else if (isAlpha(chr) and tokenpos == 1){
			chr = vect[++i];
			while (isAlpha(chr)){
				cardinal += chr;
				chr = vect[++i];
			}
			tokenpos++;
		}
		else if (chr != ' '){
			cout << "Error: Invalid character for cardinal vector" << endl;
			toReturn.angle = 0;
			toReturn.cardinal = "";
			toReturn.magnitude = 0;
			
			return toReturn;
			break;
		}
		
		i++;
	}
	
	if (tokenpos != 2){
		cout << "Error: Invlalid number of tokens" << endl;
		toReturn.angle = 0;
		toReturn.cardinal = "";
		toReturn.magnitude = 0;
		
		return toReturn;
	}
	else if (tokenpos == 0){
		toReturn.magnitude = stof(numerical);
	}
	else if (tokenpos == 2){
		toReturn.angle = stof(numerical);
	}
	
	toReturn.cardinal = cardinal;
	
	return toReturn;
}*/

PolarVector toPolarVector(CardinalVector inVector){
	PolarVector toReturn;
	string card = inVector.cardinal;
	float angle = inVector.angle;
	float mag = inVector.magnitude;
	
	map<string, float> angles {
		{"soe" , 360 - angle},
		{"e" , 0},
		{"noe" , angle},
		{"eon" , 90 - angle},
		{"n" , 90},
		{"won" , 90 + angle},
		{"now" , 180 - angle},
		{"w" , 180},
		{"sow" , 180 + angle},
		{"wos" , 270 - angle},
		{"s" , 270},
		{"eos" , 270 + angle}
	};
	if (angles.find(card) == angles.end()){
		cout << "That is not a valid Cardinal direction!" << endl;
		toReturn.angle = -1;
		toReturn.magnitude = -1;
		
		return toReturn;
	} else {
		toReturn.angle = angles[card];
		toReturn.magnitude = mag;
		return toReturn;
	};
}


RectangularVector toRectangularVector(char unary, PolarVector pol){
	RectangularVector toReturn;
	
	toReturn.x = pol.magnitude * cos(pol.angle * PI/180);
	toReturn.y = pol.magnitude * sin(pol.angle * PI/180);
	
	if (unary == '-'){
		toReturn.x = -toReturn.x;
		toReturn.y = -toReturn.y;
	}
	
	return toReturn;
}



CardinalVector parseCVector(string vect){
	vect = stripExcessSpaces(vect);
	CardinalVector toReturn;
	int eol = vect.length();
	int tokenpos = 0;
	int dots = 0;
	string cardinal = "";
	string numerical = "";
	char chr;
	int i = 0;
	while (i < eol){
		// digit(s), optional dot, digit(s), word, digit(s), optional dot, digit(s)
		cardinal = "";
		numerical = "";
		dots = 0;
	
		chr = vect[i];
		
		while (isDigit(chr)){
//			cout << "pos: " << i << " chr: " << chr << endl;
			numerical += chr;
			chr = vect[++i];
			if (chr == '.'){
				numerical += chr;
				dots++;
				chr = vect[++i];
			}
		}
		
		if (dots <= 1){
			if (tokenpos == 0){
				toReturn.magnitude = stof(numerical);
				tokenpos++;
			}
			else if (tokenpos == 2){
				toReturn.angle = stof(numerical);
				tokenpos++;
			}
			else{
				cout << "Error: Number in invalid position." << endl;
			}
		}
		else{
			cout << "Error: Invalid decimal." << endl;
			// return vector with empty values
		}
		
		while (isAlpha(chr)){
			cardinal += chr;
			chr = vect[++i];
		}
		
		if (cardinal != ""){
			if (tokenpos == 1){
				toReturn.cardinal = cardinal;
				tokenpos++;
			}
			else{
				cout << "Error: Word in invalid position" << endl;
			}
		}
		else{
			cout << "Error: Empty cardinal." << endl;
		}
		
		i++;
	}
	
	return toReturn;
}

RectangularVector parseRVector(char unary, string vect){
	RectangularVector toReturn;
	
	int i = 0;
	string numerical;
	int eol = vect.length();
	int dots;
	int tokenpos = 0;
	char chr;
	
	while (i < eol){
		chr = vect[i];
		dots = 0;
		numerical = "";
		
		
		if (chr == ' '){
			chr = vect[++i];
		}
		
		while (isDigit(chr)){
			numerical += chr;
			chr = vect[++i];
			if (chr == '.'){
				numerical += chr;
				chr = vect[++i];
				dots++;
			}
		}
		
		if (dots < 2){
			if (tokenpos == 0){
				toReturn.x = stof(numerical);
				tokenpos++;
			}
			else if(tokenpos == 1){
				toReturn.y = stof(numerical);
				tokenpos++;
			}
			else{
				cout << "Error: Too many tokens." << endl;
			}
		}
		else{
			cout  << "Error: Invalid decimal." << endl;
		}
		
		i++;
	}
	if (unary == '-'){
		toReturn.x = -toReturn.x;
		toReturn.y = -toReturn.y;
	}
	return toReturn;
}

PolarVector parsePVector(string vect){
	PolarVector toReturn;
	
	int i = 0;
	string numerical;
	int eol = vect.length();
	int dots;
	int tokenpos = 0;
	char chr;
	
	while (i < eol){
		chr = vect[i];
		dots = 0;
		numerical = "";
		
		
		if (chr == ' '){
			chr = vect[++i];
		}
		
		while (isDigit(chr)){
			numerical += chr;
			chr = vect[++i];
			if (chr == '.'){
				numerical += chr;
				chr = vect[++i];
				dots++;
			}
		}
		
		if (dots < 2){
			if (tokenpos == 0){
				toReturn.magnitude = stof(numerical);
				tokenpos++;
			}
			else if(tokenpos == 1){
				toReturn.angle = stof(numerical);
				tokenpos++;
			}
			else{
				cout << "Error: Too many tokens." << endl;
			}
		}
		else{
			cout  << "Error: Invalid decimal." << endl;
		}
		
		i++;
	}
	return toReturn;
}


void calcAndPrint(vector <RectangularVector> rectVects){
	RectangularVector vect;
	RectangularVector resultant;
	PolarVector resultantPolar;
	CardinalVector resultantCardinal;
	
	resultant.x = 0;
	resultant.y = 0;
	for (int i = 0; i < rectVects.size(); i++){
		vect = rectVects.at(i);
		
		resultant.x += vect.x;
		resultant.y += vect.y;
	}
	
	resultantPolar = resultant.toPolar();
	resultantCardinal = resultant.toCardinal();
	divider();
	cout << "Resultant Vector: [" << resultant.x << " " << resultant.y << "]" << endl;
	cout << "Polar Form: (" << resultantPolar.magnitude << " " << resultantPolar.angle << ")" << endl;
	cout << "Cardinal Form: (" << resultantCardinal.magnitude << " " << resultantCardinal.cardinal << " " << resultantCardinal.angle << ")" << endl;
	divider();
}


vector <RectangularVector> parseParen(string vect){
	
	// TODO: The parsing part is "done". Now to create an array of vectors that pools the vectors
	// Then convert all the objects in the array to rectangular vectors... perform arithmetic with them, 
	// and then print out the resultant vector in all three forms.
	
//	rectArray
	vector <RectangularVector> rectVects;
	
	
	int eol = vect.length();
	int i = 0;
	string cVect = "";
	string rVect = "";
	string pVect = "";
	char chr;
	char unary;
	bool hasUnary = false;
	int vectArrSize = 0;
	
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
						throw runtime_error("Error: Unterminated {\n");
						break;
					}
				}
				hasUnary = false;
//				cout << unary << cVect << endl;
				vectArrSize++;
				rectVects.push_back(toRectangularVector(unary, toPolarVector(parseCVector(cVect))));
			}
			else if (chr == '['){
				chr = vect[++i];
				while (chr != ']'){
					rVect += chr;
					chr = vect[++i];
					if (i == eol){
						throw runtime_error("Error: Unterminated [\n");
						break;
					}
				}
				hasUnary = false;
//				cout << unary << rVect << endl;
				vectArrSize++;
				rectVects.push_back(parseRVector(unary, rVect));
			}
			else if (chr == '('){
				chr = vect[++i];
				while (chr != ')'){
					pVect += chr;
					chr = vect[++i];
					if (i == eol){
						throw runtime_error("Error: Unterminated (\n");
						break;
					}
				}
				hasUnary = false;
//				cout << unary << pVect << endl;
				vectArrSize++;
				rectVects.push_back(toRectangularVector(unary, parsePVector(pVect)));
			}
		}
		i++;
	}
	
	
	
	
	return rectVects;
}


int main(){
	
	string input;
	string toProcess = " + ";
	cout << "Input: "; cin >> input;
	toProcess += input;
	
	calcAndPrint(parseParen("  + [123 123] + (123 270) - {123 soe 30}"));
	calcAndPrint(parseParen(toProcess));
	
	return 0;
	
	
/* ////////////////////////////////// TESTING /////////////////////////////
//	calcAndPrint(parseParen("  + [123 69.420] + (123 69.420) - {123 now 69.420}"));


	peepee = toRectangularVector('-', toPolarVector(parseCVector("123.456 now 69.423")));
	cout << "\nx: " << peepee.x << ", y: " << peepee.y << endl;
	divider();
	
	
	cout << "Now Debugging " << "123.456 cow 69.420 " << endl;
	CardinalVector peepee;
	PolarVector peepeeconverted;
	RectangularVector convertedpeepee;
	
	peepee = parseCVector('+', "123.456 now 69.423");
	cout << "magnitude: " << peepee.magnitude << endl;
	cout << "cardinal: " << peepee.cardinal << endl;
	cout << "angle: " << peepee.angle << endl;
	divider();
	
	peepeeconverted = toPolarVector(peepee);
	cout << "Polar form: " << endl;
	cout << "magnitude: " << peepeeconverted.magnitude << endl;
	cout << "angle: " << peepeeconverted.angle << endl;
	divider();
	
	convertedpeepee = toRectangularVector(peepeeconverted);
	cout << "Rectangular form: " << endl;
	cout << "x: " << convertedpeepee.x << ", y: " << convertedpeepee.y << endl;

	RectangularVector abc;
	abc = parseRVector('+', "123.456 69.423");
	cout << "x: " << abc.x << ", y: " << abc.y << endl;
	
	PolarVector def;
	def = parsePVector('+', "123.456 69.423");
	cout << "mag: " << def.magnitude << ", ang: " << def.angle << endl;
	// special case: two vectors cannot be side by side without an operator between them
*/
}