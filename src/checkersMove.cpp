#include "checkersMove.hpp"

CheckersMove toCheckersMove(const Move& move)
{
    CheckersMove retValue;
    retValue.startingField = std::stoi(move.substr(0, 2));
    retValue.landingField = std::stoi(move.substr(3, 2));
    return retValue;
}
