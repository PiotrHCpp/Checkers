#pragma once
#include "gameInterfaces.hpp"
#include "checkersMove.hpp"
#include <memory>
#include <vector>

class Checkers : public MoveExecutor, public NetworkClientReceiver
{
public:
    enum class Color {white, black};
    Checkers(NetworkClientSender& ncs, UiUpdater& uIU, Color color);
    bool tryLocalMove(Move) override;
    void receiveFromOpponent(Move) override;
    
private:
    bool isMoveValid(const CheckersMove& move) const;
    NetworkClientSender& networkClientSender;
    UiUpdater& uiUpdater;
    bool isMyTurn;
    Color color;
    std::vector<bool> fields;
};
