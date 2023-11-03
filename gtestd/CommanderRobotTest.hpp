#ifndef _COMMANDER_TEST_H_
#define _COMMANDER_TEST_H_

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
            CR1 = new CommanderRobot(1.0, 1.0, 1.0, "CR1", NULL);
            CR2 = new CommanderRobot(1.0, 1.0, 1.0, "CR2", NULL, WRS);
            std::cout<< "\n[ size = " << WRS.size()<< " ]\n"
                << std::endl;
            for (int i =0; i<(int)WRS.size(); i++){
                WRS[i]->print();
                CR2->get_deps()[i]->print(); 
             };
        };

        void TearDown(){delete WR1; delete WR2; delete CR1; delete CR2;}    
};

TEST(CommanderRobotTest1, Constructor_Test){
    WorkingRobot *W1, *W2;
    W1 = new WorkingRobot(1.0, 1.0, 1.0, "WR1", NULL);
    W2 = new WorkingRobot(1.0, 1.0, 1.0, "WR2", NULL);
    std::vector<WorkingRobot*> WRS = {W1, W2};
    CommanderRobot *CR = new CommanderRobot(1.0, 1.0, 2.0, "CR", nullptr, WRS);

    EXPECT_TRUE(CR->get_deps().size() == 2);

    std::cout<< "\n[ size = " << CR->get_deps().size()<< " ]\n"
                << std::endl;
    for (int i =0; i<(int)WRS.size(); i++){
        WRS[i]->print();
        CR->get_deps()[i]->print(); 
    }
}

TEST_F(CommanderRobotTest, contains_dep_test){
    //Act
    WorkingRobot* WR3;
    WR3 = new WorkingRobot(1.0, 1.0, 1.0, "WR3", CR1);
    //Assert
    ASSERT_TRUE(CR2->contains_dep(WR1));
    ASSERT_FALSE(CR2->contains_dep(WR3));
    ASSERT_TRUE(CR2->contains_dep(WR2));
}
//
//TEST_F(CommanderRobotTest, add_dep_test){
//    CR1->add_dep(WR1);
//    CR1->add_dep(WR2);
//    for (int it = 0; it<(int)CR1->get_deps().size(); it++){
//        CR1->get_deps()[it]->print();
//        }
//    ASSERT_TRUE(CR1->contains_dep(WR1));
//    ASSERT_TRUE(CR1->contains_dep(WR2));
//}
//
//TEST_F(CommanderRobotTest, erase_dep_test){
//    CR2->erase_dep(WR1);
//    ASSERT_FALSE(CR2->contains_dep(WR1));
//}
//
//TEST_F(CommanderRobotTest, change_commander_test){
//    //Act
//    CR1->change_commander(CR2);
//    EXPECT_THROW({
//            CR2->change_commander(CR1);
//            }, RecursiveException);
//}
////
#endif
