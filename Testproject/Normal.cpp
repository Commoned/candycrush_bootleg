#include "Normal.h"

Normal::Normal(int x, int y, std::string c)
{
	setx(x);
	color = c;
}

std::string Normal::getstr()
{
	return color;
}
