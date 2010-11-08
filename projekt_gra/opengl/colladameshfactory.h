#ifndef COLLADAMESHFACTORY_H
#define COLLADAMESHFACTORY_H

#include <QtXml>

#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QImage>
#include <QObject>
#include <QSet>

#include <algorithm>
#include <iostream>
#include <string>

#include "IL/il.h"

#include "animation.h"
#include "animationsampler.h"
#include "common.h"
#include "joint.h"
#include "mesh.h"
#include "skeletoncontroller.h"

struct Vertex {
    Vertex() {
        x = y = z = xNorm = yNorm = zNorm = r = g = b = a = s = t = 0;
    }

    float x, y, z, xNorm, yNorm, zNorm, r, g, b, a, s, t;
};

inline bool operator==( const Vertex& first, const Vertex &other ) {
    if( fabs( first.x - other.x ) > EPSILON || fabs( first.y - other.y ) > EPSILON || fabs( first.z - other.z
        ) > EPSILON || fabs( first.xNorm - other.xNorm ) > EPSILON || fabs( first.yNorm - other.yNorm ) > EPSILON || fabs( first.zNorm - other.zNorm
        ) > EPSILON || fabs( first.r - other.r ) > EPSILON || fabs( first.g - other.g ) > EPSILON || fabs( first.b - other.b ) > EPSILON || fabs( first.a - other.a
        ) > EPSILON || fabs( first.s - other.s ) > EPSILON || fabs( first.t - other.t ) > EPSILON )
        return false;

    return true;
}

inline uint qHash(const Vertex &key) {
    return ::qHash( (uint)(key.x + 2 * key.y + 4 * key.z + 16 * key.yNorm + 32 * key.zNorm + 64 * key.r + 128 * key.g + 256 * key.b + 512 * key.a) );
}

class ColladaMeshFactory : public QObject
{
Q_OBJECT
public:
    explicit ColladaMeshFactory(QObject *parent, const QString &fileName);

    Animation* getAnimation( AnimationController* controller );
    AnimationController* getAnimationController( const QString &rootNodeId );
    Mesh* getMesh( const QString &name );
    Node* getScene( const QString &name );
    SkeletonController* getSkeletonController( const QString &name, Mesh *mesh );

    Mesh* readFromFile( const QString &fileName );
    bool writeToFile( const QString &fileName, Mesh *mesh );

signals:

public slots:

private:
    void convert();
    QDomElement findNode( const QString &tagName, const QString &attributeName,
                          const QString &attributeValue, QDomElement parent = QDomElement() );
    QDomElement findNodeById( const QString &id, QDomElement parent = QDomElement(),
                              bool findBySid = false );
    QDomElement findNodeByTagName( const QString &tagName, QDomElement parent = QDomElement() );
    Node* getNodeData( QDomElement &jointElement, AnimationController *controller = 0 );
    Node* getNodes( const QStringList &jointNames, SkeletonController *controller );

    template< typename T = float >
    T* getVector( const QString &tagName, QDomElement &parent, unsigned int *count = 0,
                      const QString &attributeName = QString(),
                      const QString &attributeValue = QString() );

    void getTexture( QDomElement textureElement, QDomElement parent,
                     Material *material, const Texture::Type &textureType );
    void processMaterial( const QString &matName, const QString &originalName,
                          QDomElement parent = QDomElement() );
    Triangles* processTrianglesTag( const QDomElement &node );
    float* putDataFromSourceTag( const QString &sourceId, const QString &semantic );

    // writing and reading from custom binary files
    enum SourceType {
        NodeSource,
        MeshSource
    };

    void readTriangles( Mesh *mesh, QDataStream &in );
    bool writeMesh( const Mesh *mesh, QDataStream &out );
    bool writeTriangles( const Triangles *triangles, QDataStream &out );

    QDomDocument domDocument;
    QFile file;

    Mesh *mCurrentMesh;
    float *originalVertices;
};

#endif // COLLADAMESHFACTORY_H
