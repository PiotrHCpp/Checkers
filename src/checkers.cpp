#include <string>
#include "checkers.hpp"
#include "checkersMove.hpp"

bool Checkers::tryLocalMove(Move m)
{
    CheckersMove move = toCheckersMove(m);
    if ( 5 == move.landingField - move.startingField )
    {
        networkClientSender->sendToOpponent(m);
        return true;
    }
    return false;
}
