#ifndef _ROBOT_TEST_H_
#define _ROBOT_TEST_H_

#include <gtest/gtest.h>
#include "../hdr/Robot.h"
class RobotTest: public ::testing::Test{
    public:
        Robot *R1, *R2;
        void SetUp(){
            R1 = new Robot(1.0, 1.0, 1.0, "A");
            R2 = new Robot(1.0, 1.1, 70.8, "B");
            //std::cout << R1->get_name() << R2->get_name() <<std::endl;
        };
        void TearDown(){delete R1; delete R2;};
};

TEST_F(RobotTest, get_x_test){
    // Assert
    ASSERT_TRUE(R1->get_x() == 1.0);
}

TEST_F(RobotTest, get_y_test){
    //Assert
    ASSERT_TRUE(R1->get_x() == 1.0);
}

TEST_F(RobotTest, get_angle_test){
    //Assert
    ASSERT_TRUE(R1->get_angle() == 1.0);
}

TEST_F(RobotTest, get_name_test){
    //Assert
    ASSERT_TRUE(R1->get_name() == "A");
}

TEST_F(RobotTest, move_to_test){
    //Act
    R1->move_to(1.1, 1.5);
    //Assert
    ASSERT_TRUE(R1->get_x() == 2.1);
    ASSERT_TRUE(R1->get_y() == 2.5);
}

TEST_F(RobotTest, rotate_test){
    //Act
    R1->rotate(45.0);

    //Assert
    ASSERT_TRUE(R1->get_angle() == 46.0);
}

TEST_F(RobotTest, operator_GT_test){
    //Assert
    EXPECT_FALSE(*R1 > *R2);
}

TEST_F(RobotTest, operator_LT_test){
    //Assert
    EXPECT_TRUE(*R1 < *R2);
}

TEST_F(RobotTest, operator_GE_test){
    //Assert
    EXPECT_FALSE(*R1 >= *R2);
}

TEST_F(RobotTest, operator_LE_test){
    //Assert
    EXPECT_TRUE(*R1 <= *R2 );
}

#endif
