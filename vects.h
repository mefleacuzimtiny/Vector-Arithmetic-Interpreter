#ifndef CVECTCALC_HEADER_VECTS
#define CVECTCALC_HEADER_VECTS
#include <iostream>
#include <string>
#include <map>
#include <cmath>

#define PI 3.14159265

std::string lowerStr(std::string str){
	for(int i=0; i < str.length(); i++){
		str[i] = std::tolower(str[i]);
	}
	return str;
}
inline bool dom(float left, float val, float right){
	return (left < val && val < right);
}

struct Cardinal{
	enum Type{
		NoE, EoN, WoN, NoW, SoW, WoS, EoS, SoE, N, E, S, W
	};
	Type type;
	
	Cardinal(Type t):
		type{t}
	{}
public:
	float calcAngle(float angle){
		std::map <Type, float> angles {
			{SoE , 360 - angle},
			{E , 0},
			{NoE , angle},
			{EoN , 90 - angle},
			{N , 90},
			{WoN , 90 + angle},
			{NoW , 180 - angle},
			{W , 180},
			{SoW , 180 + angle},
			{WoS , 270 - angle},
			{S , 270},
			{EoS , 270 + angle}
		};
		return angles[type];
	}
	std::string repr(){
		std::map<Type, std::string> string_repr {
			{NoE, "NoE"},
			{EoN, "EoN"},
			{WoN, "WoN"},
			{NoW, "NoW"},
			{SoW, "SoW"},
			{WoS, "WoS"},
			{EoS, "EoS"},
			{SoE, "SoE"},
			{N, "N"},
			{E, "E"},
			{S, "S"},
			{W, "W"}
		};
		return string_repr[type];
	}
};

//Cardinal cardinals[8] = {Cardinal::NoE, Cardinal::EoN, Cardinal::WoN, Cardinal::NoW, Cardinal::SoW, Cardinal::WoS, Cardinal::EoS, Cardinal::SoE};
//Cardinal main_cardinals[4] = {Cardinal::E, Cardinal::N, Cardinal::W, Cardinal::S};

enum struct VectMode{
	CVECT, PVECT, RVECT
};

class Vect{
//	std::string cardinals[8] = {"NoE", "EoN", "WoN", "NoW", "SoW", "WoS", "EoS", "SoE"};
//	std::string main_cardinals[4] = {"E", "N", "W", "S"};
	
	std::string cardinals[8] = {"noe", "eon", "won", "now", "sow", "wos", "eos", "soe"};
	std::string main_cardinals[4] = {"e", "n", "w", "s"};
	
	float x = 0;
	float y = 0;
	float magnitude = 0;
	float angle = 0;
	float c_angle = 0;
	std::string cardinal = "noe";
	
//	float x;
//	float y;
//	float magnitude;
//	float angle;
//	float c_angle;
//	std::string cardinal;
	
public:
//	Vect(float X = 0, float Y = 0, float mag = 0, float ang = 0, float c_ang = 0, std::string card = "e"):
//		x{Y},
//		y{Y},
//		magnitude{mag},
//		angle{ang},
//		c_angle{c_ang},
//		cardinal{card}
//	{}
	
	float getX(){
		return magnitude * cos(angle * PI/180);
	}
	float getY(){
		return magnitude * sin(angle * PI/180);
	}
	float getMag(){
		return sqrt((x*x) + (y*y));
	}
	float getAng(){
		return atan(y/x) * 180/PI;
	}
	float getCAng(){
		return c_angle;
	}
	std::string getCardinal(){
		int div = angle / 45;
		int quad = angle / 90;
		if(angle == quad*90){
			return main_cardinals[quad];
		}else{
			return cardinals[div];
		}
	}
	
	void updateRec(){			// updates vector's rectangular  coordinates
		x = getX();
		y = getY();
	}
	void updatePol(){			// updates vector's polar coordinates
		magnitude = getMag();
		angle = getAng();
	}
	
	void setX(float X){
		x = X;
		updatePol();
	}
	void setY(float Y){
		y = Y;
		updatePol();
	}
	void setMag(float mag){
		magnitude = mag;
		updateRec();
	}
	void setAng(float ang){
		if(ang >= 360){
			ang -= 360;
		}
		c_angle = ang;
		std::map <std::string, float> angles {
			{"soe" , 360 - ang},
			{"e" , 0},
			{"noe" , ang},
			{"eon" , 90 - ang},
			{"n" , 90},
			{"won" , 90 + ang},
			{"now" , 180 - ang},
			{"w" , 180},
			{"sow" , 180 + ang},
			{"wos" , 270 - ang},
			{"s" , 270},
			{"eos" , 270 + ang}
		};
		angle = angles[cardinal];
		
		updateRec();
	}
	void setCardinal(std::string c){
		c = lowerStr(c);
		for(int i=0; i < std::size(cardinals); i++){
			if(cardinals[i] == c){
				cardinal = c;
				return;
			}
		}
		std::cout << c << " is not a valid cardinal direction." << '\n';
		return;
	}
	void printVect(VectMode mode){
		std::string mag, c_ang, ang, X, Y;
		mag = std::to_string(magnitude);
		c_ang = std::to_string(c_angle);
		ang = std::to_string(angle);
		X = std::to_string(x);
		Y = std::to_string(y);
		switch (mode) {
		case VectMode::CVECT:
			std::cout << "{" << mag << " " << cardinal << " " << c_ang << ")" << '\n';
			break;
		case VectMode::PVECT:
			std::cout << "(" << mag << " " << ang << ")" << '\n';
			break;
		case VectMode::RVECT:
			std::cout << "[" << X << " " << Y << "]" << '\n';
			break;
		default:
			break;
		}
//		switch (mode) {
//		case VectMode::CVECT:
//			std::cout << "{" << magnitude << " " << cardinal << " " << c_angle << ")" << '\n';
//			break;
//		case VectMode::PVECT:
//			std::cout << "(" << magnitude << " " << angle << ")" << '\n';
//			break;
//		case VectMode::RVECT:
//			std::cout << "[" << x << " " << y << "]" << '\n';
//			break;
//		default:
//			break;
//		}
	}
};
Vect operator+(Vect vect1, Vect vect2){
	Vect toReturn {};
	toReturn.setX(vect1.getX() + vect2.getX());
	toReturn.setY(vect1.getY() + vect2.getY());
	return toReturn;
}
Vect operator-(Vect vect1, Vect vect2){
	Vect toReturn {};
	toReturn.setX(vect1.getX() - vect2.getX());
	toReturn.setY(vect1.getY() - vect2.getY());
	return toReturn;
}

#endif
