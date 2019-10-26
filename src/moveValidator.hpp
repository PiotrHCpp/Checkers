#pragma once 
#include "checkersMove.hpp"
#include "checkers.hpp"

class MoveValidator
{
public:
    MoveValidator(const CheckersMove& move, const Board& occupiedFields, Color color);
    bool operator()();
    
private:
    bool isMoveValid(const CheckersMove& move) const;
        
    const CheckersMove& move;
    const Board& occupiedFields;
    const Color color;
};