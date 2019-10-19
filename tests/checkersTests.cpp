#include <gtest/gtest.h>
#include "../src/gameInterfaces.hpp"
#include "../src/checkers.hpp"

TEST(CheckersTests, checkersMusntAllowInvalidMove)
{
    Checkers checkers;
    Move someInvalidMove = "18-29";
    ASSERT_FALSE(checkers.tryLocalMove(someInvalidMove));
}

TEST(CheckersTests, MoveExecutorInterfaceIsImplemented)
{
    Checkers checkers;
    MoveExecutor& moveExecutor = checkers;
    Move someMove = "";
    moveExecutor.tryLocalMove(someMove);
}
