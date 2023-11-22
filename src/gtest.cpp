#include <gtest/gtest.h>

#include "../hdr/Robot.h"
#include "../hdr/WorkingRobot.h"
#include "../hdr/CommanderRobot.h"
#include "../hdr/Swarm.h"

#include "../gtestd/RobotTest.hpp"
#include "../gtestd/WorkingRobotTest.hpp"
#include "../gtestd/CommanderRobotTest.hpp"
#include "../gtestd/SwarmTest.hpp"

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
