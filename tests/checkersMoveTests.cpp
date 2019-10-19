#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/checkersMove.hpp"

TEST(toCheckersMoveTests, canConvertMoveWithTwoDigitsValues)
{
    CheckersMove converted("16-21");
    EXPECT_EQ(16, converted.getStartingField());
    EXPECT_EQ(21, converted.getLandingField());
}
