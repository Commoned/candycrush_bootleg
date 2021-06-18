#include "Special.h"
#include <string>
using std::string;

Special::Special(int x, int y, string c, int sp):Bubble(x,y,c)
{
	ability = sp;
}

int Special::getability()
{
	return ability;
}

void Special::setability(int sp)
{
	ability = sp;
}
/// <summary>
/// only relevant for colorbomb special Bubble
/// </summary>
/// <param name="col"></param>
void Special::setprevcolor(string col)
{
	prevcolor = col;
}

string Special::getprevcolor()
{
	return prevcolor;
}
