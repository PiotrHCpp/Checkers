#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/gameInterfaces.hpp"
#include "../src/checkers.hpp"

struct NetworkClientSenderMock : public NetworkClientSender
{
    MOCK_METHOD1(sendToOpponent, void(Move));
};

TEST(CheckersTests, checkersMusntAllowInvalidMove)
{
    NetworkClientSenderMock networkClientSenderMock;
    Checkers checkers(&networkClientSenderMock);
    Move someInvalidMove = "18-29";
    ASSERT_FALSE(checkers.tryLocalMove(someInvalidMove));
}

TEST(CheckersTests, MoveExecutorInterfaceIsImplemented)
{
    NetworkClientSenderMock networkClientSenderMock;
    Checkers checkers(&networkClientSenderMock);
    MoveExecutor& moveExecutor = checkers;
    Move someMove = "";
    moveExecutor.tryLocalMove(someMove);
}

TEST(CheckersTests, checkersMustAllowValidMove)
{
    NetworkClientSenderMock networkClientSenderMock;
    Checkers checkers(&networkClientSenderMock);
    Move someValidMove = "18-23";
    EXPECT_CALL(networkClientSenderMock, sendToOpponent(someValidMove));
    ASSERT_TRUE(checkers.tryLocalMove(someValidMove));
}
