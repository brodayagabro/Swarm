#ifndef _COMMANDER_TEST_H_
#define _COMMANDER_TEST_H_

#include <gtest/gtest.h>
#include "../hdr/WorkingRobot.h"
#include "../hdr/CommanderRobot.h"
//  Эти тестя не все дописаны так как везде нужно ловить исключения
class CommanderRobotTest : public ::testing::Test{
    public:
        CommanderRobot *CR1, *CR2;
        WorkingRobot *WR1, *WR2;
        std::vector<WorkingRobot*> WRS = {WR1, WR2};
        void SetUp(){
            WR1 = new WorkingRobot(1.0, 1.0, 1.0, "WR1", NULL);
            WR2 = new WorkingRobot(1.0, 1.0, 1.0, "WR1", NULL);
            CR1 = new CommanderRobot(1.0, 1.0, 1.0, "CR1", NULL);
            CR2 = new CommanderRobot(1.0, 1.0, 1.0, "CR2", NULL, WRS);
        }
        void TearDown(){delete WR1; delete WR2; delete CR1; delete CR2;}    
};
// тут будет кэтч исключеня с использованием EXCEPT_THROW
//TEST_F(CommanderRobotTest, change_commander_test){
//    //Act
//    CR1->change_commander(CR2);
//
//    // Assert
//    // сравниваются указатели
//    ASSERT_TRUE(CR1->get_commander() == CR2);
//    // сравниваются объекты Robot 
//    ASSERT_TRUE(*CR1->get_commander() == *CR2);
//}
//

TEST_F(CommanderRobotTest, contains_dep_test){
    //Act
    WorkingRobot* WR3;
    //PRINTF("%d", CR2->get_deps().size());
    WR3 = new WorkingRobot(1.0, 1.0, 1.0, "WR3", CR1);
    //Assert
    //ASSERT_TRUE(CR2->contains_dep(WR1));
    ASSERT_FALSE(CR2->contains_dep(WR3));
    //ASSERT_TRUE(CR2->contains_dep(WR2));
}

TEST_F(CommanderRobotTest, add_dep_test){
    CR1->add_dep(WR1);

    ASSERT_TRUE(CR1->contains_dep(WR1));
}

TEST_F(CommanderRobotTest, erase_dep_test){
    CR2->erase_dep(WR1);

    ASSERT_TRUE(CR2->contains_dep(WR1));
}

#endif
