#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <string>

#include "glmadapter.h"

struct Transformation {
    Transformation();

    enum {
        Translation,
        Rotation,
        Scale
    } type;

    float *data;
    std::string name;
};

#endif // TRANSFORMATION_H
