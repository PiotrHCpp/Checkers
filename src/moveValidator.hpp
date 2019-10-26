#pragma once 
#include "checkersMove.hpp"
#include "checkers.hpp"

class MoveValidator
{
public:
    MoveValidator(const CheckersMove& move, Board& occupiedFields, Color color);
    void setLandingfieldOccupied(const CheckersMove& move);
    bool operator()();
    
private:
    bool isMoveValid(const CheckersMove& move) const;
        
    const CheckersMove& move;
    Board& occupiedFields;
    const Color color;
};