#include <string>
#include "checkers.hpp"

Checkers::Checkers(NetworkClientSender& ncs, UiUpdater& uIU, Color color) : networkClientSender(ncs), uiUpdater(uIU), color(color)
{ 
    isMyTurn = color == Color::white;
    initializeBoard();
    moveValidator = std::make_unique<MoveValidator>(occupiedFields, color);
}

void Checkers::receiveFromOpponent(Move m)
{
    CheckersMove move(m);
    moveValidator->setLandingfieldOccupied(move);
    uiUpdater.updateGameState(m);
    isMyTurn = true;
}

bool Checkers::tryLocalMove(Move m)
{
    CheckersMove move(m);

    if (isMyTurn && moveValidator->operator()(move))
    {
        moveValidator->setLandingfieldOccupied(move);
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
