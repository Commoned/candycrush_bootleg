#pragma once
#include "Bubble.h"
class Special :
    public Bubble
{
private:
    string ability;
public:
    Special(int x, int y, string c,string sp);
    string getability();
    void setability(string sp);
};

