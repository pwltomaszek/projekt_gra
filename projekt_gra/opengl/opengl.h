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

private:
    GLWrapper();
    GLWrapper(const GLWrapper&);
    GLWrapper& operator=(const GLWrapper&);

    static GLWrapper mGLWrapper;

    void checkGLError(const std::string &message);

    GLuint mShaderProgramIds[ ShaderProgramsCount ];
    GLuint mShaderIds[ ShaderProgramsCount * ShaderTypeCount ];

    glm::mat4 mModelViewMatrix;
    glm::mat4 mProjectionMatrix;
    
    std::stack< glm::mat4 > mModelViewMatrixStack;
};

#endif // OPENGLWRAPPER_H
