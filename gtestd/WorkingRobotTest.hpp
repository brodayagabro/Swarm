#ifndef _WORKING_TEST_H_
#define _WORKING_TEST_H_

#include <gtest/gtest.h>
#include "../hdr/Robot.h"
#include "../hdr/WorkingRobot.h"
#include "../hdr/CommanderRobot.h"

class WorkingRobotTest: public ::testing::Test{
    public:
        WorkingRobot *WR1, *WR2;
        CommanderRobot *CR1, *CR2;

        void SetUp(){
            WR1 = new WorkingRobot(1.0, 1.0, 1.0, "A", NULL);
            WR2 = new WorkingRobot(1.0, 1.0, 1.0, "B", NULL);
            CR1 = new CommanderRobot(1.0, 1.0, 1.0, "C", NULL);
            CR2 = new CommanderRobot(1.0, 1.0, 1.0, "D", NULL);
        };

        void TearDown(){delete WR1; delete WR2; delete CR1;};
};

TEST_F(WorkingRobotTest, comparing_test){
    //Assert
    EXPECT_TRUE(*WR2 > *WR1);
    EXPECT_TRUE(*WR2 >= *WR1);
    EXPECT_TRUE(*WR1 < *WR2);
    EXPECT_TRUE(*WR1 <= *WR2);
    EXPECT_FALSE(*WR2 == *WR1);
}

TEST_F(WorkingRobotTest, change_commander_test){
    WR1->change_commander(CR1);
    WR1->change_commander(CR2);
    WR1->change_commander(NULL);
    //WR2->change_commander((CommanderRobot*) WR2);

    EXPECT_THROW({
        WR1->change_commander((CommanderRobot*)WR1);
    }, RecursiveException);
}

TEST_F(WorkingRobotTest, get_commander){
    // Act
    WR1->change_commander(CR1);
    // Assert
    ASSERT_TRUE(*WR1->get_commander() == *CR1);
    ASSERT_TRUE(WR1->get_commander() == CR1);
    ASSERT_TRUE(WR2->get_commander() == NULL);
}

#endif
