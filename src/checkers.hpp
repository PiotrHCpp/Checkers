#pragma once
#include "gameInterfaces.hpp"

class Checkers : public MoveExecutor
{
public:
    bool tryLocalMove(Move);
};
