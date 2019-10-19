#include <string>
#include "checkers.hpp"

bool Checkers::tryLocalMove(Move move)
{
    if ((move == "18-23") || (move == "16-21"))
    {
        networkClientSender->sendToOpponent(move);
        return true;
    }
    return false;
}
