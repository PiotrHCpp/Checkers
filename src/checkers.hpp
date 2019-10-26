#pragma once
#include "gameInterfaces.hpp"
#include "checkersMove.hpp"
#include "moveValidator.hpp"
#include <memory>

class Checkers : public MoveExecutor, public NetworkClientReceiver
{
public:
    Checkers(NetworkClientSender& ncs, UiUpdater& uIU, Color color);
    bool tryLocalMove(Move) override;
    void receiveFromOpponent(Move) override;
    
private:
    NetworkClientSender& networkClientSender;
    UiUpdater& uiUpdater;
    bool isMyTurn;
    std::unique_ptr<MoveValidator> moveValidator;
};
