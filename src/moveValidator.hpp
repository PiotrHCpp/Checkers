#pragma once 
#include "checkersMove.hpp"
#include <vector>
#include <memory>

typedef std::vector<bool> Board;
enum class Color {white, black};
typedef std::unique_ptr<Board> BoardPtr;

class MoveValidator
{
public:
    MoveValidator(BoardPtr occupiedFields, Color color);
    void setLandingfieldOccupied(const CheckersMove& move);
    bool operator()(const CheckersMove& move);
    
private:
    bool isMoveValid(const CheckersMove& move) const;
    BoardPtr occupiedFields;
    const Color color;
};