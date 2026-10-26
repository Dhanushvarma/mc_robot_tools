#pragma once

#include <mc_robot_tools/ConnectableRobotModule.h>

#include <mc_rbdyn/RobotModuleMacros.h>
#include <mc_robots/api.h>
#include <mc_rtc/logging.h>

namespace mc_robots
{

/** CALL-M's wrist mount: adapter plate, the bar with the wrist RealSense D435i, and the seat of the Robotiq 2F-85.
 *  It mounts on the UR flange (tool0) and carries the gripper on wrenchFrame(). */
struct MC_ROBOTS_DLLAPI CallMEefMountRobotModule : public mc_robot_tools::ConnectableRobotModule
{
  CallMEefMountRobotModule(const std::string & name);

  std::string baseFrame() const override;
  std::string wrenchFrame() const override;
  std::vector<std::string> collisionLinks() const override;
};

} // namespace mc_robots

extern "C"
{
  ROBOT_MODULE_API void MC_RTC_ROBOT_MODULE(std::vector<std::string> & names) // NOLINT(readability-identifier-naming)
  {
    names = {"CallMEefMount"};
  }

  ROBOT_MODULE_API void destroy(mc_rbdyn::RobotModule * ptr)
  {
    mc_robot_tools::destroyConnectableRobotModule(ptr);
  }

  ROBOT_MODULE_API mc_rbdyn::RobotModule * create(const std::string & n)
  {
    ROBOT_MODULE_CHECK_VERSION("CallMEefMount")

    if(n == "CallMEefMount")
    {
      return new mc_robots::CallMEefMountRobotModule("callm_eef_mount");
    }

    mc_rtc::log::error("CallMEefMount module cannot create an object of type {}", n);
    return nullptr;
  }
}
