#include <GL/glew.h>
#include <GL/glext.h>

#include <QDebug>

#include <iostream>
#include <stdexcept>

#include "IL/il.h"

#include "material.h"
#include "mesh.h"
#include "opengl.h"
#include "triangles.h"
#include "utils.h"

GLWrapper GLWrapper::mGLWrapper;

using namespace std;

struct LightSource {
    GLfloat position[ 4 ], ambient[ 4 ], diffuse[ 4 ];

    LightSource( float posX, float posY, float posZ,
                 float ambientR = 1.f, float ambientG = 1.f, float ambientB = 1.f,
                 float diffuseR = 1.f, float diffuseG = 1.f, float diffuseB = 1.f,
                 float ambientA = 1.f, float diffuseA = 1.f ) {
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
    }
};

GLWrapper::GLWrapper()
{

}

GLWrapper& GLWrapper::instance()
{
    return mGLWrapper;
}

void GLWrapper::init(int /*argc*/, char */*argv*/[])
{
//    glutInitWindowSize( 800, 800 );
//    glutInitWindowPosition(64, 64);
//    glutInit(&argc, argv);
//    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
//    glutCreateWindow(argv[0]);

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        qDebug() << QString::fromAscii( (const char*)glewGetErrorString(err) );
    }

    GLint majorVersion;
    GLint minorVersion;
    glGetIntegerv( GL_MAJOR_VERSION, &majorVersion );
    glGetIntegerv( GL_MINOR_VERSION, &minorVersion );

//    if( majorVersion < 4 ) {
//        printf( "Yout OpenGL version is %d.%d. Please upgrade to OpenGL 4.0+.\n",
//                majorVersion, minorVersion );
//        return;
//    }

    glEnable( GL_DEPTH_TEST );
    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );

//    glEnable( GL_LIGHTING );
//    glEnable( GL_LIGHT0 );

//    mProjectionMatrix = glm::perspective( 60.0, 1.0, 0.1, 10000.0 );

//    mModelViewMatrix = glm::translate( mModelViewMatrix, glm::vec3( 7.f, 5.f, -20.f ) );
//    mModelViewMatrix = glm::rotate( mModelViewMatrix, 77.f, glm::vec3( 0.f, 1.f, 0.f ) );
//    mModelViewMatrix = glm::rotate( mModelViewMatrix, -90.f, glm::vec3( 1.f, 0.f, 0.f ) );
//    mModelViewMatrix = glm::rotate( mModelViewMatrix, 180.f, glm::vec3( 0.f, 0.f, 1.f ) );
//    mModelViewMatrix = glm::translate( mModelViewMatrix, glm::vec3( -7.f, -5.f, -50.f ) );


//    glutDisplayFunc( run );
//    glutIdleFunc( calculateAnimation );
//    glutSpecialFunc( processKeyboard );

//    mTimeDelta = glutGet( GLUT_ELAPSED_TIME );

    initShaderPrograms();

    ilInit();

    checkGLError( "init()" );
}

void GLWrapper::checkGLError(const string &message)
{
    int errorCode;

    if( ( errorCode = glGetError() ) != GL_NO_ERROR ) {
        string errorString;
        switch( errorCode ) {
            case GL_INVALID_ENUM:
                errorString = "GL_INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                errorString = "GL_INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                errorString = "GL_INVALID_OPERATION";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                errorString = "GL_INVALID_FRAMEBUFFER_OPERATION";
                break;
            case GL_OUT_OF_MEMORY:
                errorString = "GL_OUT_OF_MEMORY";
                break;
            default:
                errorString = "UNKNOWN";
                break;
        }

        throw runtime_error( "OpenGL error(" + errorString + "): " + message + "\n" );
    }
}

void GLWrapper::generateTexture(Texture *texture)
{
    if( !texture )
        return;

    glGenTextures( 1, &texture->openGLId );
    glBindTexture( GL_TEXTURE_2D, texture->openGLId );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, texture->width, texture->height, 0,
                  GL_RGB, GL_UNSIGNED_BYTE, texture->data );
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, 0 );

    checkGLError( "generateTexture()" );
}

void GLWrapper::updateBuffer(const int &dataPosition, Mesh *mesh, bool createBuffer)
{
    GLuint elementCount = 3;
    GLfloat *source = mesh->data( (Mesh::DataPosition)dataPosition );
    GLboolean normalized = GL_TRUE;

    switch( dataPosition ) {
        case Mesh::Vertex:
            normalized = GL_FALSE;
            break;
        case Mesh::Normal:
            break;
        case Mesh::Color:
            elementCount = 4;
            break;
        case Mesh::TexCoord:
            elementCount = 2;
            break;
        default:
            cout << "Wrong data position passed to updateBuffer() for mesh " << mesh->name() << endl;
            return;
    }

    if( createBuffer )
        glGenBuffers( 1, &mesh->vboIds[ dataPosition ] );

    glBindBuffer( GL_ARRAY_BUFFER, mesh->vboIds[ dataPosition ] );
    glBufferData( GL_ARRAY_BUFFER,
                  elementCount * mesh->dataCount() * sizeof( GLfloat ),
                  source,
                  GL_STATIC_DRAW );

    if( createBuffer ) {
        glVertexAttribPointer( dataPosition, elementCount, GL_FLOAT, normalized, 0, 0 );
        glEnableVertexAttribArray( dataPosition );
    }

    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    checkGLError( "setupBuffer()" );
}

void GLWrapper::loadMeshData(Mesh *mesh)
{
    glGenVertexArrays( 1, &mesh->vaoId );
    glBindVertexArray( mesh->vaoId );

    updateBuffer( Mesh::Vertex, mesh, true );
    updateBuffer( Mesh::Normal, mesh, true );

//    if( mesh->shaderProgramType == ColorShader || mesh->shaderProgramType == ColorAndTextureShader )
//        updateBuffer( Mesh::Color, mesh, true );

    if( mesh->shaderProgramType == TextureShader ) {
        updateBuffer( Mesh::TexCoord, mesh, true );

        for( unsigned int i = 0; i < mesh->triangleCount(); ++i )
            for( unsigned int j = 0; j < Texture::TypeCount; ++j ) {
                generateTexture( mesh->texture( (Texture::Type)j, i ) );
            }
    }

    GLuint totalIndices = 0;
    for( unsigned int i = 0; i < mesh->triangleCount(); ++i )
        totalIndices += mesh->triangle( i )->indicesCount();

    glGenBuffers( 1, &mesh->elementArrayBufferId );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mesh->elementArrayBufferId );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER,
                  totalIndices * sizeof( GL_UNSIGNED_INT ),
                  0,
                  GL_STATIC_DRAW );

    GLuint lastOffset = 0;
    for( unsigned int i = 0; i < mesh->triangleCount(); ++i ) {
        glBufferSubData( GL_ELEMENT_ARRAY_BUFFER,
                         lastOffset * sizeof( GL_UNSIGNED_INT ),
                         mesh->triangle( i )->indicesCount() * sizeof( GL_UNSIGNED_INT ),
                         mesh->triangle( i )->indices() );
        lastOffset += mesh->triangle( i )->indicesCount();
    }

    checkGLError( "loadMeshes() - creating element array buffer" );

    glBindVertexArray( 0 );
}

void GLWrapper::createShader(GLuint program, GLenum type, ShaderType shaderType,
                          const std::string &fileName)
{
    string shaderSource;

    if( !( shaderSource = readTextFile( fileName ) ).empty() ) {
        GLuint &shaderId = mShaderIds[ program + shaderType ];
        shaderId = glCreateShader( type );
        const char *sourcePtr = shaderSource.c_str();
        glShaderSource( shaderId, 1, &sourcePtr, 0 );
        glCompileShader( shaderId );

        cout << shaderSource << endl;

        char *infoLog = new char[ 1000 ];
        glGetShaderInfoLog( shaderId, 1000, 0, infoLog );
        cout << infoLog << endl;
        delete []infoLog;
    } else {
        cout << "File " << fileName << " does not exist. Ommitting." << endl;
    }

    checkGLError( "createShader()" );
}

void GLWrapper::assignShader(GLuint programId, ShaderType shaderType, const std::string &fileName)
{
    GLenum oGLshaderEnum;
    string fileExtension;

    switch( shaderType ) {
        case VertexShader:
            fileExtension = ".vert";
            oGLshaderEnum = GL_VERTEX_SHADER;
            break;
        case FragmentShader:
            fileExtension = ".frag";
            oGLshaderEnum = GL_FRAGMENT_SHADER;
            break;
        default:
            cout << "Wrong shader type passed to assingShader().";
            return;
    }

    createShader( programId, oGLshaderEnum, shaderType, fileName + fileExtension );
    GLuint shaderId = mShaderIds[ programId + shaderType ];

    if( shaderId ) {
        glAttachShader( programId, shaderId );
        glDeleteShader( shaderId );
    }

    checkGLError( "assignShader()" );
}

void GLWrapper::initShaderPrograms()
{
    string shaderFileNames[ ShaderProgramsCount ] = { "texture" };

    for( int shaderProgramId = 0; shaderProgramId < ShaderProgramsCount; ++shaderProgramId ) {
        GLuint &programId = mShaderProgramIds[ shaderProgramId ];
        programId = glCreateProgram();

        string &fileName = shaderFileNames[ shaderProgramId ];

        assignShader( programId, VertexShader, fileName );
        assignShader( programId, FragmentShader, fileName );

        glBindAttribLocation( programId, Mesh::Vertex, "in_Position" );
        glBindAttribLocation( programId, Mesh::Normal, "in_Normal" );
        glBindAttribLocation( programId, Mesh::Color, "in_Color" );
        glBindAttribLocation( programId, Mesh::TexCoord, "in_TexCoord" );
        glLinkProgram( programId );

        checkGLError( "initShaderPrograms()" );
    }
}

void GLWrapper::draw(Mesh *mesh)
{
    if( !mesh )
        return;

    checkGLError( "draw begin" );

    if( mesh->vaoId == 0 )
        loadMeshData( mesh );

    glBindVertexArray( mesh->vaoId );

    GLWrapper::ShaderProgramType shaderProgramType = mesh->shaderProgramType;
    GLuint programId = mShaderProgramIds[ shaderProgramType ];

    glUseProgram( programId );

    glUniformMatrix4fv( glGetUniformLocation( programId, "modelViewMatrix" ), 16, GL_FALSE,
                        &mModelViewMatrix[ 0 ][ 0 ] );
    glUniformMatrix4fv( glGetUniformLocation( programId, "projectionMatrix" ), 16, GL_FALSE,
                        &mProjectionMatrix[ 0 ][ 0 ] );

    // load light information into uniform buffer

    static LightSource *light = 0;
    delete light;
    light = new LightSource( 0, -100, -20,
                             1.f, 1.f, 1.f,
                             0.5, 0.5, 0.5 );

    GLuint lightUniformBufferId = 0;
    glGenBuffers( 1, &lightUniformBufferId );

    GLuint lightUniformBlockIndex = glGetUniformBlockIndex( programId, "Light" );
    checkGLError( "light" );

    GLint lightUniformBlockSize = 0;
    glGetActiveUniformBlockiv( programId, lightUniformBlockIndex, GL_UNIFORM_BLOCK_DATA_SIZE,
                               &lightUniformBlockSize );
    glBindBuffer( GL_UNIFORM_BUFFER, lightUniformBufferId );
    glBufferData( GL_UNIFORM_BUFFER, lightUniformBlockSize, 0, GL_STATIC_DRAW );
    glBufferSubData( GL_UNIFORM_BUFFER, 0 * sizeof( GLfloat ),
                     4 * sizeof( GLfloat ), light->position );
    glBufferSubData( GL_UNIFORM_BUFFER, 4 * sizeof( GLfloat ),
                     4 * sizeof( GLfloat ), light->ambient );
    glBufferSubData( GL_UNIFORM_BUFFER, 8 * sizeof( GLfloat ),
                     4 * sizeof( GLfloat ), light->diffuse );
    glBindBuffer( GL_UNIFORM_BUFFER, 0 );

    glUniformBlockBinding( programId, lightUniformBlockIndex, 1 );
    glBindBufferBase( GL_UNIFORM_BUFFER, 1, lightUniformBufferId );

    if( mesh->triangleCount() == 0 ) {
        glLineWidth( 3 );
        glDrawArrays( GL_LINE_STRIP, 0, mesh->mDataCount );

        glDeleteBuffers( 1, &lightUniformBufferId );
        glBindVertexArray( 0 );
        glUseProgram( 0 );

        return;
    }

    checkGLError( "material" );

    // draw mesh

    GLuint lastIndexOffset = 0;

    GLuint materialUniformBufferId = 0;
    glGenBuffers( 1, &materialUniformBufferId );

    string samplerNames[] = { "ambientSampler", "diffuseSampler" };

    for( unsigned int i = 0; i < mesh->triangleCount(); ++i ) {
        Material *material = mesh->material( i );

        if( shaderProgramType == GLWrapper::TextureShader )
        {
            for( unsigned int j = 0; j < Texture::TypeCount; ++j ) {
                Texture *texture = mesh->texture( (Texture::Type)j, i );
                if( texture ) {
                    glActiveTexture( GL_TEXTURE0 + j );
                    glBindTexture( GL_TEXTURE_2D, texture->openGLId );
                    GLuint textureUniformId = glGetUniformLocation( programId,
                                                                    samplerNames[ j ].c_str() );
                    glUniform1i( textureUniformId, j );
                }
            }

            glEnable( GL_TEXTURE_2D );
        }

        // load material properties
        GLint materialUniformBlockSize = 0;
        GLuint materialUniformBlockIndex = glGetUniformBlockIndex( programId, "Material" );
        glGetActiveUniformBlockiv( programId, materialUniformBlockIndex,
                                   GL_UNIFORM_BLOCK_DATA_SIZE, &materialUniformBlockSize );

        glBindBuffer( GL_UNIFORM_BUFFER, materialUniformBufferId );
        glBufferData( GL_UNIFORM_BUFFER, materialUniformBlockSize, 0, GL_STATIC_DRAW );
        glBufferSubData( GL_UNIFORM_BUFFER, 0 * sizeof( GLfloat ),
                         4 * sizeof( GLfloat ), material->ambient );
        glBufferSubData( GL_UNIFORM_BUFFER, 4 * sizeof( GLfloat ),
                         4 * sizeof( GLfloat ), material->diffuse );
        glBufferSubData( GL_UNIFORM_BUFFER, 8 * sizeof( GLfloat ),
                         4 * sizeof( GLfloat ), material->specular );
        glBindBuffer( GL_UNIFORM_BUFFER, 0 );

        glUniformBlockBinding( programId, materialUniformBlockIndex, 0 );
        glBindBufferBase( GL_UNIFORM_BUFFER, 0, materialUniformBufferId );

        // draw elements
        glDrawElements( GL_TRIANGLES,
                        mesh->triangle( i )->indicesCount(),
                        GL_UNSIGNED_INT,
                        (char*)NULL + lastIndexOffset * sizeof( GL_UNSIGNED_INT ) );

        lastIndexOffset += mesh->triangle( i )->indicesCount();

        if( shaderProgramType == GLWrapper::TextureShader )
        {
            glDisable( GL_TEXTURE_2D );
        }
    }

    glDeleteBuffers( 1, &materialUniformBufferId );
    glDeleteBuffers( 1, &lightUniformBufferId );
    glBindVertexArray( 0 );
    glUseProgram( 0 );
}

void GLWrapper::clear(float r, float g, float b)
{
    glClearColor( r, g, b, 0 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void GLWrapper::flush()
{
    glFlush();
}

void GLWrapper::pushMatrix()
{
    mModelViewMatrixStack.push( mModelViewMatrix );
}

void GLWrapper::popMatrix()
{
    mModelViewMatrix = mModelViewMatrixStack.top();
    mModelViewMatrixStack.pop();
}

void GLWrapper::multMatrix(const glm::mat4 &matrix)
{
    mModelViewMatrix = mModelViewMatrix * matrix;
}

void GLWrapper::loadIdentity()
{
    mModelViewMatrix = glm::mat4( 1.f );
}

void GLWrapper::loadMatrix(const glm::mat4 &matrix)
{
    mModelViewMatrix = matrix;
}

void GLWrapper::translate(const glm::vec3 &vec)
{
    mModelViewMatrix = glm::translate( mModelViewMatrix, vec );
}

void GLWrapper::rotate(const float &angle, const glm::vec3 &vec)
{
    mModelViewMatrix = glm::rotate( mModelViewMatrix, angle, vec );
}

void GLWrapper::setPerspective(float aangle, float aaspectRatio, float anear, float afar)
{
    mProjectionMatrix = glm::perspective( aangle, aaspectRatio, anear, afar );
}

void GLWrapper::scale(const float &ratio)
{
    mModelViewMatrix = glm::scale( mModelViewMatrix, glm::vec3( ratio ) );
}

void GLWrapper::scale( const float &x, const float &y, const float &z )
{
    mModelViewMatrix = glm::scale( mModelViewMatrix, glm::vec3( x, y, z ) );
}

void GLWrapper::deleteBuffers(Mesh *mesh)
{

}
