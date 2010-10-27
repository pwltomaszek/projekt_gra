#include <cstring>

#include "triangles.h"

using namespace std;

Triangles::Triangles()
{
    mIndices = 0;
}

Triangles::~Triangles()
{
    delete []mIndices;
    mIndices = 0;
}

Triangles::Triangles(const Triangles &other)
{
    mMaterialName = other.mMaterialName;
    mIndicesCount = other.mIndicesCount;
    mIndices = new unsigned int[ mIndicesCount ];
    memcpy( mIndices, other.mIndices, mIndicesCount * sizeof( unsigned int ) );
}

unsigned int Triangles::indicesCount() const
{
    return mIndicesCount;
}

unsigned int* Triangles::indices() const
{
    return mIndices;
}

void Triangles::setIndices(const unsigned int &count, unsigned int *array)
{
    mIndicesCount = count;
    mIndices = array;
}

void Triangles::setMaterialName(const std::string &name)
{
    mMaterialName = name;
}

string Triangles::materialName() const
{
    return mMaterialName;
}
