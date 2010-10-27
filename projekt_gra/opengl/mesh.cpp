#include <cstring>

#include "material.h"
#include "mesh.h"
#include "triangles.h"

using namespace std;

// static members initialization
PairVector< string, Material* > Mesh::mMaterials;
PairVector< string, Mesh* > Mesh::mMeshes;
PairVector< string, Texture* > Mesh::mTextures;

Mesh::Mesh(const std::string &name)
    : mName( name ),
      vaoId( 0 )
{
    for( unsigned int i = 0; i < DataPositionCount; ++i )
        mData[ i ] = 0;
}

Mesh::~Mesh()
{
    for( unsigned int i = 0; i < DataPositionCount; ++i ) {
        delete []mData[ i ];
        mData[ i ] = 0;
    }
}

Mesh::Mesh(const Mesh &other)
{
    for( unsigned int i = 0; i < DataPositionCount; ++i )
        mData[ i ] = 0;

    mDataCount = other.mDataCount;

    if( other.mData[ Vertex ]) {
        mData[ Vertex ] = new float[ 3 * mDataCount ];
        memcpy( mData[ Vertex ], other.mData[ Vertex ], 3 * mDataCount * sizeof( float ) );
    }

    if( other.mData[ Normal ] ) {
        mData[ Normal ] = new float[ 3 * mDataCount ];
        memcpy( mData[ Normal ], other.mData[ Normal ], 3 * mDataCount * sizeof( float ) );
    }

    if( other.mData[ Color ] ) {
        mData[ Color ] = new float[ 4 * mDataCount ];
        memcpy( mData[ Color ], other.mData[ Color ], 4 * mDataCount * sizeof( float ) );
    }

    if( other.mData[ TexCoord ] ) {
        mData[ TexCoord ] = new float[ 3 * mDataCount ];
        memcpy( mData[ TexCoord ], other.mData[ TexCoord ], 2 * mDataCount * sizeof( float ) );
    }

    mName = other.mName;

    for( unsigned int i = 0; i < other.mTriangles.size(); ++i )
        mTriangles.push_back( new Triangles( *other.mTriangles.at( i ) ) );

    elementArrayBufferId = other.elementArrayBufferId;
    vaoId = other.vaoId;
    copy( other.vboIds, other.vboIds + DataPositionCount, vboIds );
    shaderProgramType = other.shaderProgramType;
}

Material* Mesh::material(const unsigned int &trianglesIndex) const
{
    return mMaterials.find( mTriangles.at( trianglesIndex )->materialName() );
}

Texture* Mesh::texture(const Texture::Type &textureType, const unsigned int &trianglesIndex) const
{
    return mTextures.find( material( trianglesIndex )->textureName( textureType ) );
}

Triangles* Mesh::triangle(const unsigned int &index) const
{
    return mTriangles.at( index );
}

unsigned int Mesh::triangleCount() const
{
    return mTriangles.size();
}

float* Mesh::data(const DataPosition &position)
{
    return mData[ position ];
}

std::string Mesh::name() const
{
    return mName;
}

unsigned int Mesh::dataCount() const
{
    return mDataCount;
}

void Mesh::addTriangles(Triangles *triangles)
{
    mTriangles.push_back( triangles );
}

void Mesh::setData(const DataPosition &dataPosition, float *data)
{
    mData[ dataPosition ] = data;
}

Material* Mesh::material(const std::string &name)
{
    return mMaterials.find( name );
}

void Mesh::addMaterial(const std::string &name, Material *material)
{
    mMaterials.push_back( name, material );
}

void Mesh::setDataCount(const unsigned int &count)
{
    mDataCount = count;
}

void Mesh::addTexture(const std::string &name, Texture *texture)
{
    mTextures.push_back( name, texture );
}

void Mesh::addMesh(const std::string &name, Mesh *mesh)
{
    mMeshes.push_back( name, mesh );
}

bool Mesh::isMesh(const std::string &name)
{
    return mMeshes.contains( name );
}

Mesh* Mesh::mesh(const std::string &name)
{
    return new Mesh( *mMeshes.find( name ) );
}

void Mesh::draw()
{
    GLWrapper &gl = GLWrapper::instance();

    gl.pushMatrix();
    gl.multMatrix( mTransformationMatrix );

    gl.draw( this );

    Node::draw();

    gl.popMatrix();
}
