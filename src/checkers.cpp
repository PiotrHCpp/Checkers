#include <string>
#include "checkers.hpp"

Checkers::Checkers(NetworkClientSender& ncs, UiUpdater& uIU, Color color) : networkClientSender(ncs), uiUpdater(uIU), color(color), fields(std::vector<bool>(51, false))
{ 
    isMyTurn = color == Color::white;
}

bool Checkers::isMoveValid(const CheckersMove& move) const
{
    const bool isStoneOnTheLeftEdge = 6 == move.getStartingField() %10;
    const bool isMoveToTheDownLeft = 4 == move.getFieldDifference();
    const bool isMoveToTheDownRight = 5 == move.getFieldDifference();
    const bool isMoveToTheUpLeft = -5 == move.getFieldDifference();
    const bool isMoveToTheUpRight = -4 == move.getFieldDifference();
    const bool isStoneOnTheRightEdge = 5 == move.getStartingField() %10;
    const bool allConditionsForWhites = isMoveToTheDownRight or (isMoveToTheDownLeft and !isStoneOnTheLeftEdge);
    const bool allConditionsForBlacks = isMoveToTheUpLeft or (isMoveToTheUpRight and !isStoneOnTheRightEdge);
    return ((allConditionsForWhites and color == Color::white) or (allConditionsForBlacks and color == Color::black));
}

void Checkers::receiveFromOpponent(Move m)
{
    CheckersMove move(m);
    fields[move.getLandingField()] = true;
    uiUpdater.updateGameState(m);
    isMyTurn = true;
}

bool Checkers::tryLocalMove(Move move)
{
    CheckersMove m(move);
    const bool isLandingFieldEmpty = false == fields[m.getLandingField()];
    if (isMyTurn && isMoveValid(m) && isLandingFieldEmpty)
    {
        fields[m.getLandingField()] = true;
        networkClientSender.sendToOpponent(move);
        isMyTurn = false;
        return true;
    }
    return false;
}
