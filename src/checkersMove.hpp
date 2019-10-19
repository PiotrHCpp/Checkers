#pragma once
#include "gameInterfaces.hpp"

struct CheckersMove
{
    unsigned startingField;
    unsigned landingField;    
};

CheckersMove toCheckersMove(const Move& move);
