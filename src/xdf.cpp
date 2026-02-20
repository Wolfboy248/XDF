#include <iostream>
#include <xdf/xdf.h>

#include <sstream>

namespace xdf {

Vec3 strToVec3(const std::string& str) {
  std::istringstream iss{str};
  Vec3 v;
  if (!(iss >> v.x >> v.y >> v.z)) {
    std::cout << "Invalid Vec3 format" << std::endl;
    return Vec3{0.0f, 0.0f, 0.0f};
  }
  return v;
}

// Format: "x y z"
std::string Vec3ToStr(Vec3 v) {
  std::stringstream oss;
  oss << v.x << " " << v.y << " " << v.z;
  return oss.str();
}

Vec4 strToVec4(const std::string& str) {
  std::istringstream iss{str};
  Vec4 v;
  if (!(iss >> v.w >> v.x >> v.y >> v.z)) {
    return Vec4{0.0f, 0.0f, 0.0f, 0.0f};
  }
  return v;
}

// Format: "w x y z"
std::string Vec4ToStr(Vec4 v) {
  std::stringstream oss;
  oss << v.w << " " << v.x << " " << v.y << " " << v.z;
  return oss.str();
}

}

