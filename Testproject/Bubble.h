#pragma once
#include <string>
using std::string;
class Bubble
{
private:
	int xvar=0;
	int yvar=0;
	string col="";
public:
	Bubble();
	Bubble(int x, int y,string color);
	int getx();
	void setx(int x);
	int gety();
	void sety(int y);
	string getcol();
	void setcol(string c);
};
