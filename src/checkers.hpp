#pragma once
#include "gameInterfaces.hpp"

class Checkers : public MoveExecutor, public NetworkClientReceiver
{
    NetworkClientSender& networkClientSender;
    UiUpdater& uiUpdater;
    bool isMyTurn;

public:
    Checkers(NetworkClientSender& ncs, UiUpdater& uIU) : networkClientSender(ncs), uiUpdater(uIU), isMyTurn(true) { };
    bool isMoveValid(Move m) const;
    bool tryLocalMove(Move) override;
    void receiveFromOpponent(Move) override;
};
