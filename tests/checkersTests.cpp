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
    // NetworkClientSenderMock networkClientSenderMock;
    testing::StrictMock<NetworkClientSenderMock> networkClientSenderMock;
    Checkers checkers;
    
    CheckersTests() : checkers(Checkers(&networkClientSenderMock))
    { }

    void checkValidMove(const Move& move)
    {
        EXPECT_CALL(networkClientSenderMock, sendToOpponent(move));
        ASSERT_TRUE(checkers.tryLocalMove(move));
    }
};

TEST_F(CheckersTests, MoveExecutorInterfaceIsImplemented)
{
    MoveExecutor& moveExecutor = checkers;
    Move someMove = "10-50";
    moveExecutor.tryLocalMove(someMove);
}

TEST_F(CheckersTests, checkersMusntAllowInvalidMove)
{
    Move someInvalidMove = "18-29";
    ASSERT_FALSE(checkers.tryLocalMove(someInvalidMove));
}

TEST_F(CheckersTests, cantAllowMoveOutOfEdge)
{
    Move someInvalidMove = "16-20";
    ASSERT_FALSE(checkers.tryLocalMove(someInvalidMove));
}

struct CheckersTestValidMoves : public CheckersTests, public ::testing::WithParamInterface<Move>
{
};

TEST_P(CheckersTestValidMoves, test)
{
    checkValidMove(GetParam());
}

INSTANTIATE_TEST_CASE_P(P, CheckersTestValidMoves, ::testing::Values("18-23", "16-21", "19-23"));
