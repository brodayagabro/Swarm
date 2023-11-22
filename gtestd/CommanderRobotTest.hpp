#ifndef _COMMANDER_TEST_H_
#define _COMMANDER_TEST_H_

#include <exception>
#include <gtest/gtest.h>
#include "../hdr/WorkingRobot.h"
#include "../hdr/CommanderRobot.h"

class CommanderRobotTest : public ::testing::Test{
    public:
        CommanderRobot *CR1, *CR2;
        WorkingRobot *WR1, *WR2;
        std::vector<WorkingRobot*> WRS;
        void SetUp(){
            WR1 = new WorkingRobot(1.0, 1.0, 1.0, "WR1", NULL);
            WR2 = new WorkingRobot(1.0, 1.0, 1.0, "WR2", NULL);
            WRS = {WR1, WR2};
            CR1 = new CommanderRobot(1.0, 1.0, 1.0, "CR1", NULL, {});
            CR2 = new CommanderRobot(1.0, 1.0, 1.0, "CR2", NULL, WRS);
        };

        void TearDown(){delete WR1; delete WR2; delete CR1; delete CR2;}    
};

TEST_F(CommanderRobotTest, Constructor_Test){
    EXPECT_TRUE(CR2->get_deps().size() == 2);
    EXPECT_TRUE(CR1->get_deps().size() == 0);
}

TEST_F(CommanderRobotTest, contains_dep_test){
    //Act
    WorkingRobot* WR3;
    WR3 = new WorkingRobot(1.0, 1.0, 1.0, "WR3", CR1);
    //Assert
    ASSERT_TRUE(CR2->contains_dep(WR1));
    ASSERT_TRUE(CR2->contains_dep(WR2));
    ASSERT_FALSE(CR2->contains_dep(WR3));
}

TEST_F(CommanderRobotTest, add_dep_test){
    CR1->add_dep(WR1);
    CR1->add_dep(WR2);

    ASSERT_TRUE(CR1->contains_dep(WR1));
    ASSERT_TRUE(CR1->contains_dep(WR2));
}
//
TEST_F(CommanderRobotTest, erase_dep_test){
    CR2->erase_dep(WR1);
    ASSERT_FALSE(CR2->contains_dep(WR1));
}

TEST_F(CommanderRobotTest, change_commander_test){
    CR1->change_commander(CR2);
    //std::cout<<CR1->get_commander()->get_name()<<std::endl;
    EXPECT_TRUE(CR1->get_commander() == CR2);
}
#endif
