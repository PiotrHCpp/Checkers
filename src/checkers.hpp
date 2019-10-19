#pragma once
#include "gameInterfaces.hpp"

class Checkers : public MoveExecutor
{
    NetworkClientSender* networkClientSender;
    bool isMyTurn;

public:
    Checkers(NetworkClientSender* n) : networkClientSender(n), isMyTurn(true)
    { };
    bool isMoveValid(Move m) const;
    bool tryLocalMove(Move) override;
};
