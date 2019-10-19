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

TEST_F(CheckersTests, checkersMusntAllowInvalidMove)
{
    Move someInvalidMove = "18-29";
    ASSERT_FALSE(checkers.tryLocalMove(someInvalidMove));
}

TEST_F(CheckersTests, MoveExecutorInterfaceIsImplemented)
{
    MoveExecutor& moveExecutor = checkers;
    Move someMove = "10-50";
    moveExecutor.tryLocalMove(someMove);
}

TEST_F(CheckersTests, checkersMustAllowValidMove)
{
    checkValidMove("18-23");
}

TEST_F(CheckersTests, checkersMustAllowAnotherValidMove)
{
    checkValidMove("16-21");
}
