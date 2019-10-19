#pragma once
#include "gameInterfaces.hpp"
#include <memory>

class Checkers : public MoveExecutor, public NetworkClientReceiver
{
    NetworkClientSender& networkClientSender;
    UiUpdater& uiUpdater;
    bool isMyTurn;
    std::unique_ptr<bool> isMyColorWhite;

public:
    Checkers(NetworkClientSender& ncs, UiUpdater& uIU) : networkClientSender(ncs), uiUpdater(uIU), isMyTurn(true) { };
    bool isMoveValid(Move m) const;
    bool tryLocalMove(Move) override;
    void receiveFromOpponent(Move) override;
};
