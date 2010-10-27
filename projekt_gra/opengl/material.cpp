#include "material.h"

using namespace std;

Material::Material()
{
    emission = ambient = diffuse = specular = transparent = reflective = 0;
}

void Material::setTextureName(const Texture::Type &type, const std::string &name)
{
    mTextureNames[ type ] = name;
}

string Material::textureName(const Texture::Type &type) const
{
    return mTextureNames[ type ];
}
