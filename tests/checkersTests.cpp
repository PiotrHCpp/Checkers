#include <gtest/gtest.h>
#include "../src/gameInterfaces.hpp"
#include "../src/checkers.hpp"

TEST(CheckersTests, checkersShouldAllowGoodMove)
{
    Checkers checkers;
    Move someGoodMove = "18-23";
    ASSERT_EQ(true, checkers.tryLocalMove(someGoodMove));
}

TEST(CheckersTests, MoveExecutorInterfaceIsImplemented)
{
    Checkers checkers;
    MoveExecutor& moveExecutor = checkers;
    Move someMove = "";
    moveExecutor.tryLocalMove(someMove);
}
