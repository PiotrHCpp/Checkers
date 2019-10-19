#include <string>
#include "checkers.hpp"
#include "checkersMove.hpp"

bool Checkers::tryLocalMove(Move m)
{
    CheckersMove move(m);
    if ( 5 == move.getLandingField() - move.getStartingField() )
    {
        networkClientSender->sendToOpponent(m);
        return true;
    }
    return false;
}
