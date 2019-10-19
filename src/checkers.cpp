#include <string>
#include "checkers.hpp"
#include "checkersMove.hpp"

bool Checkers::isMoveValid(Move m) const
{
    CheckersMove move(m);
    const bool isStoneOnTheLeftEdge = 6 == move.getStartingField() %10;
    const bool isMoveToTheDownLeft = 4 == move.getFieldDifference();
    const bool isMoveToTheDownRight = 5 == move.getFieldDifference();
    return ( isMoveToTheDownRight or (isMoveToTheDownLeft and !isStoneOnTheLeftEdge) );
}

void Checkers::receiveFromOpponent(Move move)
{
    uiUpdater.updateGameState(move);
}

bool Checkers::tryLocalMove(Move move)
{
    if (isMyTurn && isMoveValid(move))
    {
        networkClientSender.sendToOpponent(move);
        isMyTurn = false;
        return true;
    }
    return false;
}
