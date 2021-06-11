#pragma once
#include "Bubble.h"
#include <string>
using std::string;
class Special :
    public Bubble
{
private:
    int ability;
    string prevcolor;
public:
    Special(int x, int y, string c,int sp);
    int getability();
    void setability(int sp);
    void setprevcolor(string col);
    string getprevcolor();
};

