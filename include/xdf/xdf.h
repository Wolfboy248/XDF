#pragma once

#include "node.h"

namespace xdf {

struct Vec3 {
  float x;
  float y;
  float z;
};

struct Vec4 {
  float w;
  float x;
  float y;
  float z;
};

extern Vec3 strToVec3(const std::string& str);
extern std::string Vec3ToStr(Vec3 v);

extern Vec4 strToVec4(const std::string& str);
extern std::string Vec4ToStr(Vec4 v);

}

