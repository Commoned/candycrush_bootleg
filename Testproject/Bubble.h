#pragma once
#include <string>
using std::string;
class Bubble
{
private:
	//int xvar=0;
	//int yvar=0;
	string col="";
	int sameneighbours=0;
public:
	Bubble();
	Bubble(int x, int y,string color);
	int getx();
	void setx(int x);
	int gety();
	void sety(int y);
	void setneighbours(int a);
	int getneighbours();
	string getcol();
	void setcol(string c);
};
