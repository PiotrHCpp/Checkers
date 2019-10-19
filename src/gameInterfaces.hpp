#pragma once
#include <string>

typedef std::string Move;

struct NetworkClientSender
{
    virtual void sendToOpponent(Move) = 0;
};

struct NetworkClientReceiver
{
    virtual void receiveFromOpponent(Move) = 0;
};

struct MoveExecutor
{
    virtual bool tryLocalMove(Move) = 0;
};

struct UiUpdater
{
    virtual void updateGameState(Move) = 0;
};
