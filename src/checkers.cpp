#include "checkers.hpp"

bool Checkers::tryLocalMove(Move moveInput)
{
    networkClientSender->sendToOpponent(moveInput);
    if (moveInput == "18-23")
        return true;
    return false;
}
