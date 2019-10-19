#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/gameInterfaces.hpp"
#include "../src/checkers.hpp"

struct NetworkClientSenderMock : public NetworkClientSender
{
    MOCK_METHOD1(sendToOpponent, void(Move));
};

struct CheckersTests : public testing::Test
{
    NetworkClientSenderMock networkClientSenderMock;
    Checkers checkers;
    CheckersTests() : checkers(Checkers(&networkClientSenderMock))
    { }
};

TEST_F(CheckersTests, checkersMusntAllowInvalidMove)
{
    Move someInvalidMove = "18-29";
    ASSERT_FALSE(checkers.tryLocalMove(someInvalidMove));
}

TEST_F(CheckersTests, MoveExecutorInterfaceIsImplemented)
{
    MoveExecutor& moveExecutor = checkers;
    Move someMove = "";
    moveExecutor.tryLocalMove(someMove);
}

TEST_F(CheckersTests, checkersMustAllowValidMove)
{
    Move someValidMove = "18-23";
    EXPECT_CALL(networkClientSenderMock, sendToOpponent(someValidMove));
    ASSERT_TRUE(checkers.tryLocalMove(someValidMove));
}
