
#include "Bubble.h"
#include <string>
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

void Bubble::setneighbours(int a)
{
	sameneighbours = a;
}

int Bubble::getneighbours()
{
	return sameneighbours;
}
