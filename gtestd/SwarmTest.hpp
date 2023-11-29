#ifndef _SWARM_TEST_HPP_
#define _SWARM_TEST_HPP_

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
        CommanderRobot *CR = new CommanderRobot(1, 2, 3, "CR2", NULL, {});
        Swarm* swarm;
        void SetUp(){
            robots = {new WorkingRobot(1, 2, 3, "A", NULL),
                        new CommanderRobot(1, 2, 4, "B", NULL, {})};
            swarm = new Swarm(robots);
        };
        void TearDown(){
            robots.clear();
            delete swarm;
            delete CR;
        }
};

TEST(SwarmTest1, Swarm_Swarm_Test){
    std::vector<WorkingRobot*> robots = {
        new WorkingRobot(1, 2, 3, "A", NULL),
        new WorkingRobot(1, 2, 4, "B", NULL)
    };
    Swarm *swarm = new Swarm(robots);
    EXPECT_TRUE(swarm->get_robots().size() == 2);
}

TEST_F(SwarmTest, is_included_test){
    ASSERT_TRUE(swarm->is_included(robots[1]));
    ASSERT_TRUE(swarm->is_included(robots[0]));

}

TEST_F(SwarmTest, get_robots_test){
    EXPECT_TRUE(swarm->get_robots().size() == 2);

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

TEST_F(SwarmTest, change_commander_test4){
    // Test4
    dynamic_cast<CommanderRobot*>(robots[1])->add_dep(CR);
    EXPECT_THROW(swarm->change_commander(robots[1], CR), RecursiveException);
}

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

#endif
