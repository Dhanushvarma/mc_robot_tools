#include "callm_eef_mount.h"
#include "config.h"

#include <RBDyn/parsers/urdf.h>

#include <filesystem>
namespace fs = std::filesystem;

namespace mc_robots
{

CallMEefMountRobotModule::CallMEefMountRobotModule(const std::string & name)
: mc_robot_tools::ConnectableRobotModule(MC_DATA_PATH, name)
{
  bool fixed = false;
  init(rbd::parsers::from_urdf_file(urdf_path, fixed));
  rsdf_dir = (fs::path(MC_RSDF_DIR) / name).string();
}

std::string CallMEefMountRobotModule::baseFrame() const
{
  return "callm_eef_mount_base_link";
}

std::string CallMEefMountRobotModule::wrenchFrame() const
{
  return "callm_eef_mount_gripper_link";
}

std::vector<std::string> CallMEefMountRobotModule::collisionLinks() const
{
  return {"callm_eef_mount_base_link", "callm_eef_mount_bar_link", "callm_eef_mount_camera_link"};
}

} // namespace mc_robots
