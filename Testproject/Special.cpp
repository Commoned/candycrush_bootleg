#include "Special.h"
#include <string>
using std::string;

Special::Special(int x, int y, string c, string sp):Bubble(x,y,c)
{
	ability = sp;
}

string Special::getability()
{
	return ability;
}

void Special::setability(string sp)
{
	ability = sp;
}