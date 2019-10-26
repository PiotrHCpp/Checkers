#pragma once
#include "gameInterfaces.hpp"
#include "checkersMove.hpp"
#include <memory>
#include <vector>

typedef std::vector<bool> Board;
enum class Color {white, black};

class Checkers : public MoveExecutor, public NetworkClientReceiver
{
public:
    Checkers(NetworkClientSender& ncs, UiUpdater& uIU, Color color);
    bool tryLocalMove(Move) override;
    void receiveFromOpponent(Move) override;
    
private:
    void initializeBoard();
    NetworkClientSender& networkClientSender;
    UiUpdater& uiUpdater;
    bool isMyTurn;
    Color color;
    Board occupiedFields;
};
