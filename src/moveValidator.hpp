#pragma once 
#include "checkersMove.hpp"
#include <vector>

typedef std::vector<bool> Board;
enum class Color {white, black};

class MoveValidator
{
public:
    MoveValidator(Board& occupiedFields, Color color);
    void setLandingfieldOccupied(const CheckersMove& move);
    bool operator()(const CheckersMove& move);
    
private:
    bool isMoveValid(const CheckersMove& move) const;
    Board& occupiedFields;
    const Color color;
};