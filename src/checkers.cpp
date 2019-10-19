#include <string>
#include "checkers.hpp"
#include "checkersMove.hpp"

bool Checkers::tryLocalMove(Move m)
{
    CheckersMove move(m);
    if ( 5 == move.getFieldDifference() or (4 == move.getFieldDifference() and move.getStartingField() %10 != 6))
    {
        networkClientSender->sendToOpponent(m);
        return true;
    }
    return false;
}
