#include "checkers.hpp"

bool Checkers::tryLocalMove(Move moveInput)
{
    
    if ((moveInput == "18-23") || (moveInput == "16-21"))
    {
        networkClientSender->sendToOpponent(moveInput);
        return true;
    }
    return false;
}
