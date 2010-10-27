#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>

#include "texture.h"

class Material {
public:
    Material();

    void setTextureName( const Texture::Type &type, const std::string &name );
    std::string textureName( const Texture::Type &type ) const;

    // RGBA arrayd
    float *emission, *ambient, *diffuse, *specular, *transparent, *reflective;

    // single floats
    float shininess, reflectivity, transparency;

    std::string mTextureNames[ 2 ];
};

#endif // MATERIAL_H
