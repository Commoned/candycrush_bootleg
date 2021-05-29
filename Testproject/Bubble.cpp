
#include "Bubble.h"
Bubble::Bubble(){}
Bubble::Bubble(int x,int y)
{
	xvar = x;
	yvar = y;
}

int Bubble::getx() 
{
	return xvar;
}

void Bubble::setx(int x)
{
	xvar = x;
}