#ifndef _TASK_TEST_H_
#define _TASK_TEST_H_

#include <gtest/gtest.h>
#include <stdexcept>
#include "../hdr/Task.h"

class DistrictTest: public ::testing::Test{
    public:
        district <float>* Feild;
        void SetUp(){
            Feild = new district<float>(1.0, 2.0, 1.0, 5.0);
        }
        void TearDown(){
            delete Feild;
        }

};

TEST(DistrictTest1, Test1){
    EXPECT_THROW(new district<float>(1.0, 1.0, 2.0, 3.0), std::range_error); 
}

TEST_F(DistrictTest, get_X_lims_Test){
    EXPECT_TRUE(Feild->get_X_lims().first == 1.0);
    EXPECT_TRUE(Feild->get_X_lims().second == 2.0);
}


TEST_F(DistrictTest, get_Y_lims_Test){
    EXPECT_TRUE(Feild->get_Y_lims().first == 1.0);
    EXPECT_TRUE(Feild->get_Y_lims().second == 5.0);
}

TEST_F(DistrictTest, get_center){
    point* p = Feild->get_center();
    EXPECT_TRUE(p->x == 1.5);
    EXPECT_TRUE(p->y = 3.0);
}

class TaskTest: public ::testing::Test{
    public:
        Task* testing_task;
        CommanderRobot* LiableCommander;
        district<float>* feild;
        Swarm *swarm;
        void SetUp(){
            std::vector<WorkingRobot*> robots;
            swarm = new Swarm(robots);
            feild = new district<float>(0.0, 10.0, 0.0, 7.0);
            LiableCommander = new CommanderRobot(1.0, 2.0, 45.0, "CR_main", NULL, {});
            swarm->add_robot((WorkingRobot*) LiableCommander);
            std::string name="Task1";
            testing_task = new Task(name, LiableCommander, feild, 10, 20, *swarm); 
        };
        void TearDown(){
            delete feild;
            delete LiableCommander;
            delete testing_task;
            delete swarm;
        }
};


TEST(TaskTest1, ConstructorTest){ 
    district<float>* feild = new district<float>(0.0, 10.0, 0.0, 7.0);
    CommanderRobot* LiableCommander = new CommanderRobot(1.0, 2.0, 45.0, "CR_main", NULL, {});
    std::string name="Task1";
    std::vector<WorkingRobot*> robots{(WorkingRobot*)LiableCommander};
    Swarm swarm(robots);
    EXPECT_THROW(new Task("", LiableCommander, feild, 10, 20, swarm), std::range_error);
    EXPECT_THROW(new Task(name, nullptr, feild, 10, 10, swarm), std::runtime_error);
    EXPECT_THROW(new Task(name, LiableCommander, nullptr, 10, 10, swarm), std::runtime_error);
    EXPECT_THROW(new Task(name, LiableCommander, feild, -10, 7, swarm), std::range_error);
    EXPECT_THROW(new Task(name, LiableCommander, feild, 10, -2, swarm), std::range_error); 

}

TEST_F(TaskTest, get_name_test){
    ASSERT_TRUE(testing_task->get_name()=="Task1");
}

TEST_F(TaskTest, get_time_test){
    ASSERT_TRUE(testing_task->get_time() == 10);
}

TEST_F(TaskTest, get_countR_test){
    ASSERT_TRUE(testing_task->get_countR() ==20);
}

TEST_F(TaskTest, get_feild_test){
    district<float>* feild = testing_task->get_feild();
    ASSERT_TRUE(feild->get_X_lims().first == 0.0);    
    ASSERT_TRUE(feild->get_X_lims().second == 10.0);
    ASSERT_TRUE(feild->get_Y_lims().first == 0.0);
    ASSERT_TRUE(feild->get_Y_lims().second == 7.0);

}
#endif 
