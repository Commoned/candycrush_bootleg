
#include "Bubble.h"
#include <string>
#include <iostream>

using std::string;
Bubble::Bubble(){}
Bubble::Bubble(int x,int y, string color)
{
	//xvar = x;
	//yvar = y;
	col = color;
}
Bubble::Bubble(int x, int y, string color, int nb)
{
	//xvar = x;
	//yvar = y;
	col = color;
	sameneighbours = nb;
}

// getter and setter
/*
int Bubble::getx() 
{
	return xvar;
}
void Bubble::setx(int x)
{
	xvar = x;
}
int Bubble::gety()
{
	return yvar;
}
void Bubble::sety(int y)
{
	yvar = y;
}
*/

string Bubble::getcol()
{
	return col;
}

void Bubble::setcol(string c)
{
	col = c;
}

void Bubble::setneighbours(int count,vector<void*> neighbX, vector<void*> neighbY)
{
	sameneighbours = count;
	neighboursX = neighbX; 
	neighboursY = neighbY;
}

int Bubble::getneighbours()
{
	return sameneighbours;
}


vector<void*> Bubble::getXneighbours()
{
	return neighboursX;
}
vector<void*> Bubble::getYneighbours()
{
	return neighboursY;
}

bool Bubble::getwasmoved()
{
	return wasmoved;
}

void Bubble::setwasmoved(bool moved)
{
	wasmoved = moved;
}