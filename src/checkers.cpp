#include <string>
#include "checkers.hpp"
#include "moveValidator.hpp"

Checkers::Checkers(NetworkClientSender& ncs, UiUpdater& uIU, Color color) : networkClientSender(ncs), uiUpdater(uIU), color(color)
{ 
    isMyTurn = color == Color::white;
    initializeBoard();
}

void Checkers::receiveFromOpponent(Move m)
{
    CheckersMove move(m);
    MoveValidator moveValidator(move, occupiedFields, color);
    moveValidator.setLandingfieldOccupied(move);
    uiUpdater.updateGameState(m);
    isMyTurn = true;
}

bool Checkers::tryLocalMove(Move m)
{
    CheckersMove move(m);
    MoveValidator moveValidator(move, occupiedFields, color);
    if (isMyTurn && moveValidator())
    {
        moveValidator.setLandingfieldOccupied(move);
        networkClientSender.sendToOpponent(m);
        isMyTurn = false;
        return true;
    }
    return false;
}

void Checkers::initializeBoard()
{
    occupiedFields = std::vector<bool>(51, true);
    for (int i=21; i<=30; ++i)
        occupiedFields[i]=false;
}
