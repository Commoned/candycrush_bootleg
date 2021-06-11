#pragma once
#include <string>
#include <vector>
using std::vector;
using std::string;
class Bubble
{
private:
	//int xvar=0;
	//int yvar=0;
	string col="";
	int sameneighbours=0;
	vector<void*> neighbours;
public:
	Bubble();
	Bubble(int x, int y,string color);
	Bubble(int x, int y, string color,int nb);
	int getx();
	void setx(int x);
	int gety();
	void sety(int y);
	void setneighbours(int count,vector<void*> neighb);
	int getneighbours();
	string getcol();
	void setcol(string c);
};
