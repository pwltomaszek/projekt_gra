#ifndef MESH_H
#define MESH_H

#include <string>

#include "node.h"
#include "opengl.h"
#include "pairvector.h"
#include "texture.h"

class Material;
class Triangles;

class Mesh : public Node {
public:
    enum DataPosition {
        Vertex,
        Normal,
        Color,
        TexCoord,
        DataPositionCount
    };

    Mesh( const std::string &name );
    Mesh( const Mesh &other );
    ~Mesh();

    void addTriangles( Triangles *triangles );
    float* data( const DataPosition &position );
    unsigned int dataCount() const;
    virtual void draw();
    Material* material( const unsigned int &trianglesIndex ) const;
    std::string name() const;
    void setData( const DataPosition &dataPosition, float *data );
    void setDataCount( const unsigned int &count );
    void setIndices( unsigned int *array );
    Texture* texture( const Texture::Type &textureType, const unsigned int &trianglesIndex ) const;
    Triangles* triangle( const unsigned int &index ) const;
    unsigned int triangleCount() const;

    static void addMaterial( const std::string &name, Material *material );
    static void addMesh( const std::string &name, Mesh *mesh );
    static void addTexture( const std::string &name, Texture *texture );
    static bool isMesh( const std::string &name );
    static Material* material( const std::string &name );
    static Mesh* mesh( const std::string &name );

    // OpenGL thingies
    unsigned int elementArrayBufferId;
    unsigned int vaoId, vboIds[ DataPositionCount ];
    GLWrapper::ShaderProgramType shaderProgramType;

private:
    std::string mName;
    std::vector< Triangles* > mTriangles;

    unsigned int mDataCount;
    float* mData[ DataPositionCount ];

    static PairVector< std::string, Material* > mMaterials;
    static PairVector< std::string, Mesh* > mMeshes;
    static PairVector< std::string, Texture* > mTextures;
};

#endif // MESH_H
