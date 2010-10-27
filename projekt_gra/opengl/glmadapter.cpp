#include "glmadapter.h"

glm::mat4 GLMAdapter::mat4(const float *array)
{
    return glm::mat4( array[ 0 ], array[ 4 ], array[ 8 ], array[ 12 ],
                      array[ 1 ], array[ 5 ], array[ 9 ], array[ 13 ],
                      array[ 2 ], array[ 6 ], array[ 10 ], array[ 14 ],
                      array[ 3 ], array[ 7 ], array[ 11 ], array[ 15 ] );
}

glm::vec4 GLMAdapter::vec4(const float *array)
{
    return glm::vec4( array[ 0 ], array[ 1 ], array[ 2 ], array[ 3 ] );
}

glm::vec3 GLMAdapter::vec3(const float *array)
{
    return glm::vec3( array[ 0 ], array[ 1 ], array[ 2 ] );
}

glm::vec2 GLMAdapter::vec2(const float *array)
{
    return glm::vec2( array[ 0 ], array[ 1 ] );
}

std::ostream& operator<<( std::ostream& out, const glm::mat4 &mat ) {
    for( int i = 0; i < 4; ++i ) {
        for( int j = 0; j < 4; ++j )
            out << mat[ j ][ i ] << " ";
        out << "\n";
    }
    return out;
}

std::ostream& operator<<( std::ostream& out, const glm::vec4 &mat ) {
    for( int i = 0; i < 4; ++i ) {
        out << mat[ i ] << " ";
    }
    return out;
}

std::ostream& operator<<( std::ostream& out, const glm::vec3 &mat ) {
    for( int i = 0; i < 3; ++i ) {
        out << mat[ i ] << " ";
    }
    return out;
}
