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

#endif 
