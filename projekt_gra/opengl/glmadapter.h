#ifndef GLMADAPTER_H
#define GLMADAPTER_H

#include <iostream>

#include "glm/glm/glm.hpp"
#include "glm/glm/ext.hpp"

class GLMAdapter
{
public:
    static glm::mat4 mat4( const float *array );
    static glm::vec4 vec4( const float *array );
    static glm::vec3 vec3( const float *array );
    static glm::vec2 vec2( const float *array );
};

std::ostream& operator<<( std::ostream& out, const glm::mat4 &mat );
std::ostream& operator<<( std::ostream& out, const glm::vec4 &mat );
std::ostream& operator<<( std::ostream& out, const glm::vec3 &mat );

#endif // GLMADAPTER_H
