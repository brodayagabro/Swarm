#ifndef _SWARM_TEST_HPP_
#define _SWARM_TEST_HPP_
#define DEBUG
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include <vector>
#include "../hdr/WorkingRobot.h"
#include "../hdr/CommanderRobot.h"
#include "../hdr/Swarm.h"

class SwarmTest: public ::testing::Test{
    public:
        std::vector<WorkingRobot*> robots;
        Swarm* swarm;
        CommanderRobot *CR;
        void SetUp(){
            CR = new CommanderRobot(1, 2, 3, "CR2", nullptr, {});
            
            // CommanderRobot*R1 = new CommanderRobot(1, 2, 3, "R1", nullptr, {});
            // CommanderRobot*R2 = new CommanderRobot(1, 2, 4, "R2", nullptr, {}); 
            // CommanderRobot*R3 = new CommanderRobot(1, 2, 3, "R3", nullptr, {});
            // CommanderRobot*R4 = new CommanderRobot(1, 2, 3, "R4", nullptr, {});
            CommanderRobot*R5 = new CommanderRobot(1, 2, 3, "R5", CR, {});    
            CommanderRobot*R6 = new CommanderRobot(1, 2, 4, "R6", nullptr, {}); 
            // CommanderRobot*R7 = new CommanderRobot(1, 2, 3, "R7", nullptr, {});
            /*
            R2->change_commander(nullptr);
            R3->change_commander(R1);
            */
            //R1->add_dep((WorkingRobot*)R2); R1->add_dep((WorkingRobot*)R3);
            //R4->change_commander(R2);
            //R5->change_commander(R2);
            //R2->add_dep((WorkingRobot*)R4); R2->add_dep((WorkingRobot*)R5);
            //R6->change_commander(R3);
            //R7->change_commander(R3);
            //R3->add_dep((WorkingRobot*)R6);
            //R3->add_dep((WorkingRobot*)R7);
            //R1->change_commander(R7);            
            //R7->add_dep((WorkingRobot*)R1);
            
            robots = {R5, R6};

            swarm = new Swarm(robots);
        };
        void TearDown(){
            robots.clear();
            delete swarm;
            delete CR;
        }
};

//TEST(SwarmTest1, Swarm_Swarm_Test){
 //   std::vector<WorkingRobot*> robots = {
  //      new WorkingRobot(1, 2, 3, "A", NULL),
 //       new WorkingRobot(1, 2, 4, "B", NULL)
 ////   };
   // Swarm *swarm = new Swarm(robots);
   // EXPECT_TRUE(swarm->get_robots().size() == 2);
//}

//TEST_F(SwarmTest, is_included_test){
 //   //printf("%d\n", 0);
  //  EXPECT_TRUE(swarm->is_included(robots[0]));
    //printf("%d\n", 1);
//    EXPECT_TRUE(swarm->is_included(robots[1]));
//    //printf("%d\n", 2);
//    EXPECT_FALSE(swarm->is_included((WorkingRobot*)CR));
//    //printf("%d\n", 3);
//}
/*
TEST_F(SwarmTest, get_robots_test){
    EXPECT_TRUE(swarm->get_robots().size() == 7);

}

TEST_F(SwarmTest, add_robot_test){
    WorkingRobot* R = new WorkingRobot(1.0, 3.0, 40.0, "B", NULL);
    swarm->add_robot(R);
    ASSERT_TRUE(swarm->is_included(R));
}

TEST_F(SwarmTest, exclude_robot_test){
    swarm->exclude_robot(robots[0]);
    EXPECT_FALSE(swarm->is_included(robots[0]));
    EXPECT_TRUE(swarm->exclude_robot(nullptr) == 1);
}


TEST_F(SwarmTest, change_commander_test1){
    // Test1
    CR->add_dep(robots[1]);
    //std::cout<<CR->get_deps()[0]->get_name()<<std::endl;
    EXPECT_THROW(swarm->change_commander((WorkingRobot*)robots[1],(CommanderRobot*)CR), std::runtime_error);
}

TEST_F(SwarmTest, change_commander_test2){
    // Test2
    robots[1]->change_commander(CR);
    EXPECT_THROW(swarm->change_commander(robots[1], CR), std::runtime_error);
}
TEST_F(SwarmTest, change_commander_test3){
    // Test3
    CR->add_dep(robots[1]);
    robots[1]->change_commander(CR);
    EXPECT_THROW(swarm->change_commander(robots[1], CR), std::runtime_error);
}
*/
TEST_F(SwarmTest, change_commander_test4){
    // Test4
    //dynamic_cast<CommanderRobot*>(robots[5])->add_dep(robots[2]);
    //robots[2]->change_commander((CommanderRobot*)robots[2]);
    //std::cout<<robots[6]->get_name()<<std::endl;
    swarm->get_robots()[0]->change_commander(nullptr);
    swarm->get_robots()[1]->change_commander((CommanderRobot*)robots[0]);
    EXPECT_THROW(swarm->change_commander(robots[0], (CommanderRobot*)robots[1]), RecursiveException);
}
/*
TEST_F(SwarmTest, change_commander_test5){
    // Test5
    swarm->change_commander(robots[0], CR);
    EXPECT_TRUE(robots[0]->get_commander() == CR);
    EXPECT_TRUE(CR->contains_dep(robots[0]));
}

TEST_F(SwarmTest, change_commander_test6){
    // Test6
    CR->change_commander((CommanderRobot*)robots[1]);
    dynamic_cast<CommanderRobot*>(robots[1])->add_dep(CR);
    EXPECT_THROW(swarm->change_commander(robots[1], CR), RecursiveException);
}
*/
#endif
