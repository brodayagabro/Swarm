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
            CR1 = new CommanderRobot(1.0, 1.0, 1.0, "C", nullptr, {});
            CR2 = new CommanderRobot(1.0, 1.0, 1.0, "D", nullptr, {});
            WR1 = new WorkingRobot(1.0, 1.0, 1.0, "A", CR1);
            WR2 = new WorkingRobot(1.0, 1.0, 1.0, "B", CR2);
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


TEST_F(WorkingRobotTest, get_commander){
    // Assert
    
    // WR1
    ASSERT_TRUE(*WR1->get_commander() == *CR1);
    ASSERT_TRUE(WR1->get_commander() == CR1);
    //ASSERT_TRUE(WR2->get_commander() == NULL);
    
    // WR2
    ASSERT_TRUE(*WR2->get_commander() == *CR2);
    ASSERT_TRUE(WR2->get_commander() == CR2);
    //ASSERT_TRUE(WR2->get_commander() == NULL);
}

TEST_F(WorkingRobotTest, change_commander_test){
    WR1->change_commander(CR2);
    ASSERT_TRUE(WR1->get_commander() == CR2);
    
    WR2->change_commander(nullptr);
    ASSERT_TRUE(WR2->get_commander() == nullptr);
    EXPECT_THROW({
        WR1->change_commander((CommanderRobot*)WR1);
    }, RecursiveException);
}
#endif
