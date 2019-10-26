#include <string>
#include "checkers.hpp"
#include "moveValidator.hpp"

Checkers::Checkers(NetworkClientSender& ncs, UiUpdater& uIU, Color color) : networkClientSender(ncs), uiUpdater(uIU), color(color), occupiedFields(std::vector<bool>(51, false))
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
    for (int i=1; i<=20; ++i)
        occupiedFields[i]=true;

    for (int j=31; j<=50; ++j)
        occupiedFields[j]=true;
}
