#include <string>
#include "checkers.hpp"
#include "moveValidator.hpp"

Checkers::Checkers(NetworkClientSender& ncs, UiUpdater& uIU, Color color) : networkClientSender(ncs), uiUpdater(uIU), color(color)
{ 
    isMyTurn = color == Color::white;
    initializeBoard();
}

void Checkers::setLandingfieldOccupied(const CheckersMove& move)
{
    occupiedFields[move.getLandingField()] = true;
}

void Checkers::receiveFromOpponent(Move m)
{
    CheckersMove move(m);
    setLandingfieldOccupied(m);
    uiUpdater.updateGameState(m);
    isMyTurn = true;
}

bool Checkers::tryLocalMove(Move move)
{
    CheckersMove m(move);
    MoveValidator moveValidator(m, occupiedFields, color);
    if (isMyTurn && moveValidator())
    {
        setLandingfieldOccupied(m);
        networkClientSender.sendToOpponent(move);
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
