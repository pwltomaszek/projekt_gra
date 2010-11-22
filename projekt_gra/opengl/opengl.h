#ifndef OPENGLWRAPPER_H
#define OPENGLWRAPPER_H

#include <stack>
#include <string>
#include <vector>

//#include "GL/glew.h"

//#define GLUT_DISABLE_ATEXIT_HACK
//#include "GL/glut.h"

#define GL3_PROTOTYPES 1
#include "GL3/gl3.h"

#include "glmadapter.h"

class Mesh;
class Texture;

struct LightSource {
    GLfloat position[ 4 ], ambient[ 4 ], diffuse[ 4 ], specular[ 4 ];

    LightSource( float posX, float posY, float posZ,
                 float ambientR = 1.f, float ambientG = 1.f, float ambientB = 1.f,
                 float diffuseR = 1.f, float diffuseG = 1.f, float diffuseB = 1.f,
                 float specularR = 1.f, float specularG = 1.f, float specularB = 1.f,
                 float ambientA = 1.f, float diffuseA = 1.f, float specularA = 1.f ) {
        position[ 0 ] = posX;
        position[ 1 ] = posY;
        position[ 2 ] = posZ;
        position[ 3 ] = 1.f;

        ambient[ 0 ] = ambientR;
        ambient[ 1 ] = ambientG;
        ambient[ 2 ] = ambientB;
        ambient[ 3 ] = ambientA;

        diffuse[ 0 ] = diffuseR;
        diffuse[ 1 ] = diffuseG;
        diffuse[ 2 ] = diffuseB;
        diffuse[ 3 ] = diffuseA;

        specular[ 0 ] = specularR;
        specular[ 1 ] = specularG;
        specular[ 2 ] = specularB;
        specular[ 3 ] = specularA;
    }
};

class GLWrapper
{
public:
    static GLWrapper& instance();

    enum ShaderProgramType {
//        ColorShader,
        TextureShader,
//        ColorAndTextureShader,
        ShaderProgramsCount
    };

    enum ShaderType {
        VertexShader,
        FragmentShader,
        ShaderTypeCount
    };

    void assignShader(GLuint programId, ShaderType shaderType, const std::string &fileName);
    void clear( float r = 1.f, float g = 1.f, float b = 1.f );
    void createShader(GLuint program, GLenum type, ShaderType shaderType, const std::string &fileName);
    void deleteBuffers( Mesh *mesh );
    void draw( Mesh *mesh );
    void flush();
    void generateTexture( Texture *texture );
    void init( int argc, char *argv[]);
    void initShaderPrograms();
    void loadIdentity();
    void loadMatrix( const glm::mat4 &matrix );
    void loadMeshData( Mesh *mesh );
    void multMatrix( const glm::mat4 &matrix );
    void popMatrix();
    void processKeyboard( int key, int /*x*/, int /*y*/ );
    void pushMatrix();
    void rotate( const float &angle, const glm::vec3 &vec );
    void scale( const float &ratio );
    void scale( const float &x, const float &y, const float &z );
    void setPerspective( float angle, float aspectRatio, float near, float far );
    void translate( const glm::vec3 &vec );
    void updateBuffer( const int &dataPosition, Mesh *mesh,
                              bool createBuffer = false );

    LightSource *light;
    glm::mat4 mModelViewMatrix;

private:
    GLWrapper();
    GLWrapper(const GLWrapper&);
    GLWrapper& operator=(const GLWrapper&);

    static GLWrapper mGLWrapper;

    void checkGLError(const std::string &message);

    GLuint mShaderProgramIds[ ShaderProgramsCount ];
    GLuint mShaderIds[ ShaderProgramsCount * ShaderTypeCount ];

    glm::mat4 mProjectionMatrix;
    
    std::stack< glm::mat4 > mModelViewMatrixStack;
};

#endif // OPENGLWRAPPER_H
