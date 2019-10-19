#pragma once
#include "gameInterfaces.hpp"

class CheckersMove
{
public:
    CheckersMove(const Move& move);
    unsigned getStartingField() const;
    unsigned getLandingField() const;
    int getFieldDifference() const;

private:
    unsigned startingField;
    unsigned landingField;    
};
