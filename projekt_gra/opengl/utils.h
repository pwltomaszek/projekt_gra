#ifndef UTILS_H
#define UTILS_H

#include <string>

float clamp( float value, float min = 0.f, float max= 1.f );
std::string readTextFile(const std::string &fileName);

#endif // UTILS_H
