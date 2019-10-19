#pragma once
#include "gameInterfaces.hpp"

class Checkers : public MoveExecutor
{
    NetworkClientSender* networkClientSender;

public:
    Checkers(NetworkClientSender* n) : networkClientSender(n) {};
    bool tryLocalMove(Move) override;
};
