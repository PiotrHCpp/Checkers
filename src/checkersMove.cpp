#include "checkersMove.hpp"

CheckersMove::CheckersMove(const Move& move)
{
    startingField = std::stoi(move.substr(0, 2));
    landingField = std::stoi(move.substr(3, 2));
}

unsigned CheckersMove::getStartingField() const
{
    return startingField;
}

unsigned CheckersMove::getLandingField() const
{
    return landingField;
}

unsigned CheckersMove::getFieldDifference() const
{
    return landingField - startingField;
}
