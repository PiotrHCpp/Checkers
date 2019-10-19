#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/gameInterfaces.hpp"
#include "../src/checkers.hpp"

struct NetworkClientSenderMock : public NetworkClientSender
{
    MOCK_METHOD1(sendToOpponent, void(Move));
};

struct UiUpdaterMock : public UiUpdater
{
    MOCK_METHOD1(updateGameState, void(Move));
};

struct CheckersTests : public testing::Test
{
    testing::StrictMock<NetworkClientSenderMock> networkClientSenderMock;
    testing::StrictMock<UiUpdaterMock> uiUpdaterMock;
    MoveExecutor& moveExecutor = checkers;
    NetworkClientReceiver& networkClientReceiver = checkers;

    Checkers checkers;
    
    CheckersTests() : checkers(Checkers(networkClientSenderMock, uiUpdaterMock))
    { }

    void checkLocalValidMove(const Move& move)
    {
        EXPECT_CALL(networkClientSenderMock, sendToOpponent(move));
        ASSERT_TRUE(moveExecutor.tryLocalMove(move));
    }

    void checkReceivedMove(Move move)
    {
        EXPECT_CALL(uiUpdaterMock, updateGameState(move));
        networkClientReceiver.receiveFromOpponent(move);
    }
};

TEST_F(CheckersTests, checkersMusntAllowInvalidMove)
{
    Move someInvalidMove = "18-29";
    ASSERT_FALSE(moveExecutor.tryLocalMove(someInvalidMove));
}

TEST_F(CheckersTests, cantAllowMoveOutOfLeftEdge)
{
    Move someInvalidMove = "16-20";
    ASSERT_FALSE(moveExecutor.tryLocalMove(someInvalidMove));
}

struct CheckersTestValidMoves : public CheckersTests, public ::testing::WithParamInterface<Move>
{
};

TEST_P(CheckersTestValidMoves, test)
{
    checkLocalValidMove(GetParam());
}

INSTANTIATE_TEST_SUITE_P(P, CheckersTestValidMoves, ::testing::Values("18-23", "16-21", "19-23"));

TEST_F(CheckersTests, whiteCantMoveTwoTimesInARow)
{
    Move whiteValidMove = "19-23";
    Move secondWhiteValidMove = "18-22";
    checkLocalValidMove(whiteValidMove);
    ASSERT_FALSE(moveExecutor.tryLocalMove(secondWhiteValidMove));    
}

TEST_F(CheckersTests, moveFromNetworkShouldUpdateUi)
{
    Move whiteValidMove = "19-23";
    checkReceivedMove(whiteValidMove);
}

TEST_F(CheckersTests, whiteCanMoveSecondTimeAfterBlacksMove)
{
    Move whiteValidMove = "19-23";
    Move blackValidMove = "33-28";
    Move secondWhiteValidMove = "18-22";

    checkLocalValidMove(whiteValidMove);
    checkReceivedMove(blackValidMove);
    checkLocalValidMove(secondWhiteValidMove);
}

TEST_F(CheckersTests, BlacksCanMoveAfterReceivingWhitesMoveFromTheNetwork)
{
    Move whiteValidMove = "19-23";
    Move blackValidMove = "33-28";

    checkReceivedMove(whiteValidMove);
    checkLocalValidMove(blackValidMove);
}

TEST_F(CheckersTests, BlacksCanMoveToTheRight)
{
    Move whiteValidMove = "19-23";
    Move blackValidMove = "33-29";

    checkReceivedMove(whiteValidMove);
    checkLocalValidMove(blackValidMove);
}

TEST_F(CheckersTests, cantAllowMoveOutOfTheRightEdge)
{
    Move someInvalidMove = "35-31";
    ASSERT_FALSE(moveExecutor.tryLocalMove(someInvalidMove));
}
