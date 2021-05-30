#pragma once
#include "Bubble.h"
class Special :
    public Bubble
{
private:
    int ability;
    
public:
    Special(int x, int y, string c,int sp);
    int getability();
    void setability(int sp);
};

