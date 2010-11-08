#include "colladameshfactory.h"
#include "material.h"
#include "texture.h"
#include "transformation.h"
#include "triangles.h"

using namespace std;

ColladaMeshFactory::ColladaMeshFactory(QObject *parent, const QString &fileName) :
    QObject(parent),
    file( fileName ),
    mCurrentMesh( 0 ),
    originalVertices( 0 )
{
    if( !file.open( QIODevice::ReadOnly ) ) {
        qDebug() << "Nie mozna czytac z pliku " << fileName;
        qDebug() << file.errorString();
        exit( 1 );
    }

    QString errorMsg;
    int errorLine, errorColumn;
    if( !domDocument.setContent( &file, &errorMsg, &errorLine, &errorColumn ) ) {
        qDebug() << errorMsg;
        qDebug() << "Line: " << errorLine;
        qDebug() << "Column: " << errorColumn;
        exit( 2 );
    }
}

QDomElement ColladaMeshFactory::findNodeById(const QString &id, QDomElement parent, bool findBySid )
{
    QString attribute = findBySid ? "sid" : "id";

    return findNode( QString(), attribute, id, parent );
}

QDomElement ColladaMeshFactory::findNodeByTagName(const QString &tagName, QDomElement parent )
{
    return findNode( tagName, QString(), QString(), parent );

}

Mesh* ColladaMeshFactory::getMesh(const QString &name)
{
    QDomElement geometryNode = findNodeById( name ).toElement();
    geometryNode = geometryNode.firstChildElement( "mesh" );

    if( geometryNode.isNull() )
        return 0;

    if( Mesh::isMesh( name.toStdString() ) )
        return Mesh::mesh( name.toStdString() );

    Mesh *mesh = new Mesh( name.toStdString() );
    mCurrentMesh = mesh;
    Mesh::addMesh( name.toStdString(), mesh );

    QDomNodeList triangles = geometryNode.elementsByTagName( "triangles" );
    for( int i = 0; i < triangles.count(); ++i )
        mesh->addTriangles( processTrianglesTag( triangles.at( i ).toElement() ) );

    convert();
//    if( mesh->data( Mesh::Color ) ) {
//        if( mesh->data( Mesh::TexCoord ) ) {
//            mesh->shaderProgramType = GLWrapper::ColorAndTextureShader;
//        } else {
//            mesh->shaderProgramType = GLWrapper::ColorShader;
//        }
//    } else {
        mesh->shaderProgramType = GLWrapper::TextureShader;
//    }

    mCurrentMesh = 0;

    return mesh;
}

Triangles* ColladaMeshFactory::processTrianglesTag(const QDomElement &node)
{
    Triangles *triangles = new Triangles;

    QDomNodeList inputs = node.elementsByTagName( "input" );

    unsigned int indicesCount = node.attribute( "count" ).toUInt() * 3;
    unsigned int *indices = new unsigned int[ indicesCount * inputs.count() ];
    QStringList indicesList = node.text().split( " " );
    for( int i = 0; i < indicesList.count(); ++i )
        indices[ i ] = indicesList.at( i ).toUInt();
    triangles->setIndices( indicesCount, indices );

    // triangles' material
    QString materialName = node.attribute( "material" );
    
    triangles->setMaterialName( materialName.toStdString() );
    processMaterial( materialName, materialName, node );

    for( int i = 0; i < inputs.count(); ++i ) {
        QDomElement node = inputs.at( i ).toElement();
        putDataFromSourceTag( node.attribute( "source" ),
                              node.attribute( "semantic" ) );
    }

    return triangles;
}

float* ColladaMeshFactory::putDataFromSourceTag(const QString &sourceId,
                                                const QString &semantic)
{
    QDomElement node = findNodeById( sourceId.right( sourceId.size() - 1 ) );

    if( !node.firstChildElement( "input" ).attribute( "source").isEmpty() )
        return putDataFromSourceTag( node.firstChildElement( "input" ).attribute( "source" ),
                                     node.firstChildElement( "input" ).attribute( "semantic" ) );

    Mesh::DataPosition dataPosition = Mesh::Vertex;
    if( semantic == "NORMAL" )
        dataPosition = Mesh::Normal;
    else if( semantic == "COLOR" )
        dataPosition = Mesh::Color;
    else if( semantic == "TEXCOORD" )
        dataPosition = Mesh::TexCoord;

    if( mCurrentMesh->data( dataPosition ) )
        return 0;

    // data
    QStringList dataList = node.text().split( " " );

    float *array = new float[ dataList.count() ];
    for( int i = 0; i < dataList.count(); ++i )
        array[ i ] = dataList.at( i ).toFloat();

    mCurrentMesh->setData( dataPosition, array );

    return array;
}

void ColladaMeshFactory::processMaterial(const QString &matName, const QString &originalName,
                                         QDomElement parent)
{
    QDomElement node = findNodeById( matName, parent );

    if( node.isNull() ) {
        node = findNode( "instance_material", "symbol", matName );
        QString target = node.attribute( "target" );
        node = findNodeById( target );
    }

    QDomElement instanceEffectNode = findNodeByTagName( "instance_effect", node ).toElement();
    if( !instanceEffectNode.isNull() ) {
        QString instanceName = instanceEffectNode.attribute( "url" );
        return processMaterial( instanceName, originalName );
    }

    if( Mesh::material( matName.toStdString() ) )
        return;

    Material *material = new Material;

    // RGBA arrays
    // emission
    material->emission = getVector< float >( "emission", node );

    // ambient
    QDomElement ambientElement = findNodeByTagName( "ambient", node );
    QDomElement ambientTextureElement = ambientElement.firstChildElement( "texture" );
    if( ambientTextureElement.isNull() ) {
        material->ambient = getVector( "ambient", node );
    } else {
        getTexture( ambientTextureElement, node, material, Texture::Ambient );

        material->ambient = new float[ 4 ];
        for( int i = 0; i < 4; ++i )
            material->ambient[ i ] = 1;
    }

    // diffuse
    QDomElement diffuseElement = findNodeByTagName( "diffuse", node );
    QDomElement diffuseTextureElement = diffuseElement.firstChildElement( "texture" );
    if( diffuseTextureElement.isNull() ) {
        material->diffuse = getVector( "diffuse", node );
    } else {
        getTexture( diffuseTextureElement, node, material, Texture::Diffuse );
        material->diffuse = new float[ 4 ];

        for( int i = 0; i < 4; ++i )
            material->diffuse[ i ] = 1;
    }

    // specular
    material->specular = getVector( "specular", node );

    // reflective
    material->reflective = getVector( "reflective", node );

    // transparent
    material->transparent = getVector( "transparent", node );

    // single floats
    // shininess
    material->shininess = findNodeByTagName( "shininess", node ).text().toFloat();

    // reflectivity
    material->reflectivity = findNodeByTagName( "reflectivity", node ).text().toFloat();

    // transparency
    material->transparency = findNodeByTagName( "transparency", node ).text().toFloat();

    Mesh::addMaterial( originalName.toStdString(), material );
}

void ColladaMeshFactory::convert()
{
    unsigned int indicesStride = 2;
    if( mCurrentMesh->data( Mesh::Color ) )
        ++indicesStride;
    if( mCurrentMesh->data( Mesh::TexCoord ) )
        ++indicesStride;

    QList< Vertex > vertices[ mCurrentMesh->triangleCount() ];

    for( unsigned int i = 0; i < mCurrentMesh->triangleCount(); ++i ) {
        Triangles *triangles = mCurrentMesh->triangle( i );

        for( unsigned int j = 0; j < triangles->indicesCount(); ++j ) {
            Vertex v;

            unsigned int position = j * indicesStride;

            v.x = mCurrentMesh->data( Mesh::Vertex )[ triangles->indices()[ position ] * 3 ];
            v.y = mCurrentMesh->data( Mesh::Vertex )[ triangles->indices()[ position ] * 3 + 1 ];
            v.z = mCurrentMesh->data( Mesh::Vertex )[ triangles->indices()[ position ] * 3 + 2 ];

            v.xNorm = mCurrentMesh->data( Mesh::Normal )[ triangles->indices()[ position + 1 ] * 3 ];
            v.yNorm = mCurrentMesh->data( Mesh::Normal )[ triangles->indices()[ position + 1 ] * 3 + 1 ];
            v.zNorm = mCurrentMesh->data( Mesh::Normal )[ triangles->indices()[ position + 1 ] * 3 + 2 ];

            if( mCurrentMesh->data( Mesh::Color ) ) {
                v.r = mCurrentMesh->data( Mesh::Color )[ triangles->indices()[ position + 2 ] * 4 ];
                v.g = mCurrentMesh->data( Mesh::Color )[ triangles->indices()[ position + 2 ] * 4 + 1 ];
                v.b = mCurrentMesh->data( Mesh::Color )[ triangles->indices()[ position + 2 ] * 4 + 2 ];
                v.a = mCurrentMesh->data( Mesh::Color )[ triangles->indices()[ position + 2 ] * 4 + 3 ];
            }

            if( mCurrentMesh->data( Mesh::TexCoord ) ) {
                v.s = mCurrentMesh->data( Mesh::TexCoord )[ triangles->indices()[ position + 2 ] * 2 ];
                v.t = mCurrentMesh->data( Mesh::TexCoord )[ triangles->indices()[ position + 2 ] * 2 + 1 ];
            }

//            qDebug() << v.x << v.y << v.z;

            vertices[ i ].append( v );
        }
    }

//    qDebug() << "\n==============================================\n";
//    qDebug() << vertices[ 0 ].size() << vertices[ 1 ].size();

    QList< Vertex > newVertices;
    unsigned int nextIndex = 0;

    for( unsigned int i = 0; i < mCurrentMesh->triangleCount(); ++i ) {
        Triangles *triangles = mCurrentMesh->triangle( i );

        QList< unsigned int > newIndices;

        foreach( const Vertex &v, vertices[ i ] ) {
            if( !newVertices.contains( v ) ) {
                newVertices.append( v );
                newIndices.append( nextIndex++ );

            } else {
                newIndices.append( newVertices.indexOf( v ) );
            }
        }

        // set up new indices array
        delete []triangles->indices();

        unsigned int indicesCount = newIndices.size();
        unsigned int *indices = new unsigned int[ indicesCount ];
        for( unsigned int j = 0; j < indicesCount; ++j )
            indices[ j ] = newIndices.at( j );

        triangles->setIndices( indicesCount, indices );

//        qDebug() << newIndices.size();
    }

    // set up new vertex data arrays
    // vertex positions and normals are always given

    // don't delete positions array, it will be needed later for skeleton skinning
//    delete []mCurrentMesh->positions;
    originalVertices = mCurrentMesh->data( Mesh::Vertex );

    delete []mCurrentMesh->data( Mesh::Normal );

    mCurrentMesh->setDataCount( newVertices.size() );
    float *positions = new float[ mCurrentMesh->dataCount() * 3 ];
    float *normals = new float[ mCurrentMesh->dataCount() * 3 ];
    for( unsigned int j = 0; j < mCurrentMesh->dataCount(); ++j ) {
        positions[ j * 3 ] = newVertices.at( j ).x;
        positions[ j * 3 + 1 ] = newVertices.at( j ).y;
        positions[ j * 3 + 2 ] = newVertices.at( j ).z;

        normals[ j * 3 ] = newVertices.at( j ).xNorm;
        normals[ j * 3 + 1 ] = newVertices.at( j ).yNorm;
        normals[ j * 3 + 2 ] = newVertices.at( j ).zNorm;
    }
    mCurrentMesh->setData( Mesh::Vertex, positions );
    mCurrentMesh->setData( Mesh::Normal, normals );

    if( mCurrentMesh->data( Mesh::Color ) ) {
        delete []mCurrentMesh->data( Mesh::Color );

        float *colors = new float[ mCurrentMesh->dataCount() * 4 ];
        for( unsigned int j = 0; j < mCurrentMesh->dataCount(); ++j ) {
            colors[ j * 4 ] = newVertices.at( j ).r;
            colors[ j * 4 + 1 ] = newVertices.at( j ).g;
            colors[ j * 4 + 2 ] = newVertices.at( j ).b;
            colors[ j * 4 + 3 ] = newVertices.at( j ).a;
        }

        mCurrentMesh->setData( Mesh::Color, colors );
    }

    if( mCurrentMesh->data( Mesh::TexCoord ) ) {
        delete []mCurrentMesh->data( Mesh::TexCoord );

        float *texcoords = new float[ mCurrentMesh->dataCount() * 2 ];
        for( unsigned int j = 0; j < mCurrentMesh->dataCount(); ++j ) {
            texcoords[ j * 2 ] = newVertices.at( j ).s;
            texcoords[ j * 2 + 1 ] = newVertices.at( j ).t;
        }

        mCurrentMesh->setData( Mesh::TexCoord, texcoords );
    }
}

QDomElement ColladaMeshFactory::findNode(const QString &tagName, const QString &attributeName,
                                         const QString &attributeValue, QDomElement parent)
{
    if( parent.isNull() )
        parent = domDocument.documentElement();

    QDomElement child = parent.firstChildElement();
    if( child.isNull() )
        return QDomElement();

    QString realAttrValue = attributeValue;
    if( attributeValue.startsWith( '#' ) )
        realAttrValue.remove( 0, 1 );

    do {
        bool attributeMatches = child.attribute( attributeName ) == realAttrValue;
        bool tagNameMatches = child.tagName() == tagName;

        bool emptyTagNameCheck = tagName.isEmpty() && attributeMatches;
        bool emptyAttributeNameCheck = attributeName.isEmpty() && tagNameMatches;
        bool normalCheck = attributeMatches && tagNameMatches;

        if( emptyTagNameCheck || emptyAttributeNameCheck || normalCheck )
            return child;

        QDomElement result = findNode( tagName, attributeName, realAttrValue, child );
        if( !result.isNull() )
            return result;

        child = child.nextSiblingElement();
    } while( !child.isNull() );

    return QDomElement();
}

SkeletonController* ColladaMeshFactory::getSkeletonController(const QString &name,
                                                              Mesh *mesh)
{
    QDomElement controllerElement = findNodeById( name );

    if( controllerElement.isNull() )
        return 0;

    mCurrentMesh = mesh;

    SkeletonController *controller = new SkeletonController( mesh );

    // get bind shape matrix
    float *bsm = getVector( "bind_shape_matrix", controllerElement );
    controller->setBindShapeMatrix( bsm );
    delete []bsm;

    // get joints
    QDomElement jointsElement = findNodeByTagName( "joints", controllerElement );
    QString jointSourceName = findNode( "input", "semantic", "JOINT", jointsElement )
                                    .attribute( "source" );
    QDomElement jointSource = findNodeById( jointSourceName, controllerElement );
    QStringList jointNames = jointSource.text().split( " " );
    controller->setRootNode( getNodes( jointNames, controller ) );

    // get joints' inverse bind matrices
    QString ibmSourceName = findNode( "input", "semantic", "INV_BIND_MATRIX", jointsElement )
                                    .attribute( "source" );
    float *ibsm = getVector( "source", controllerElement, 0, "id", ibmSourceName );
    for( int i = 0; i < jointNames.size(); ++i ) {
        Joint *joint = static_cast< Joint* >( controller->node( i ) );
        joint->setInvBindMatrix( &ibsm[ i * 16 ] );
    }
    delete []ibsm;

    // vertex weights
    QDomElement vertexWeightsTag = findNodeByTagName( "vertex_weights", controllerElement );
    QDomElement inputElement = findNode( "input", "semantic", "WEIGHT", vertexWeightsTag );
    QString weightsId = inputElement.attribute( "source" );
    controller->setWeights( getVector( "source", controllerElement, 0, "id", weightsId ) );

    unsigned int originalVertexCount;
    unsigned int *originalJointPerVertex = getVector< unsigned int >( "vcount", vertexWeightsTag,
                                                                      &originalVertexCount );
    unsigned int *originalJointAndWeightIndices = getVector< unsigned int >( "v", vertexWeightsTag );

    // assign weight and joint data to our vertices order
    QList< unsigned int > *jointAndWeightIndices = new QList< unsigned int >[ mesh->dataCount() ];
    unsigned int *jointsPerVertex = new unsigned int[ mesh->dataCount() ];

    unsigned int indicesIterator = 0;
    unsigned int newArraySize = 0;
    float *positions = mesh->data( Mesh::Vertex );
    for( unsigned int originalVertexIterator = 0;
         originalVertexIterator < originalVertexCount;
         ++originalVertexIterator )
    {
        QList< unsigned int > verticesToChange;
        for( unsigned int i = 0; i < mesh->dataCount(); ++i ) {
            if
            (
                    fabs( positions[ i * 3 ] - originalVertices[ originalVertexIterator * 3 ] ) < EPSILON
                 && fabs( positions[ i * 3 + 1 ] - originalVertices[ originalVertexIterator * 3 + 1 ] ) < EPSILON
                 && fabs( positions[ i * 3 + 2 ] - originalVertices[ originalVertexIterator * 3 + 2 ] ) < EPSILON
            )
            {
                verticesToChange.append( i );
            }
        }

        unsigned int originalJointPerVertexCount = originalJointPerVertex[ originalVertexIterator ];
        foreach( unsigned int index, verticesToChange ) {
            jointsPerVertex[ index ] = originalJointPerVertexCount;

            for( unsigned int i = 0; i < originalJointPerVertexCount; ++i ) {
                // insert joint index
                jointAndWeightIndices[ index ].append( originalJointAndWeightIndices[ 2 * ( indicesIterator + i ) ] );
                // insert weight index
                jointAndWeightIndices[ index ].append( originalJointAndWeightIndices[ 2 * ( indicesIterator + i ) + 1 ] );

                ++newArraySize;
            }
        }
        indicesIterator += originalJointPerVertexCount;
    }
    controller->setJointsPerVertex( jointsPerVertex );

    unsigned int *newJointAndWeightIndices = new unsigned int[ newArraySize * 2 ];

    unsigned int arrayIterator = 0;
    for( unsigned int i = 0; i < mesh->dataCount(); ++i ) {
        unsigned int jointsPerCurrentVertex = jointAndWeightIndices[ i ].size();

        for( unsigned int j = 0; j < jointsPerCurrentVertex; ++j )
            newJointAndWeightIndices[ arrayIterator++ ] = jointAndWeightIndices[ i ].at( j );
    }    
    controller->setJointAndWeightIndices( newJointAndWeightIndices );

    delete []originalJointPerVertex;
    delete []originalJointAndWeightIndices;

    mCurrentMesh = 0;

    return controller;
}

template< typename T >
T* ColladaMeshFactory::getVector(const QString &tagName, QDomElement &parent,
                                     unsigned int *count, const QString &attributeName,
                                     const QString &attributeValue)
{
    if( parent.isNull() )
        parent = domDocument.documentElement();

    QDomElement sourceElement = findNode( tagName, attributeName, attributeValue, parent );

    QStringList values = sourceElement.text().split( " " );

    T *returnValue = new T[ values.size() ];
    for( int i = 0; i < values.size(); ++i ) {
        returnValue[ i ] = values.at( i ).toFloat();
    }

    if( count )
        *count = values.size();

    return returnValue;
}

void ColladaMeshFactory::getTexture(QDomElement textureElement, QDomElement parent,
                                    Material *material, const Texture::Type &textureType)
{
    QString samplerId = textureElement.attribute( "texture" );
    QDomElement samplerElement = findNode( "newparam", "sid", samplerId, parent );

    QString textureSourceId = findNodeByTagName( "source", samplerElement ).text();
    QDomElement textureSourceElement = findNode( "newparam", "sid", textureSourceId, parent );

    QString textureFileId = findNodeByTagName( "init_from", textureSourceElement ).text();
    QDomElement textureFileElement = findNodeById( textureFileId );

    QString fileName = textureFileElement.text();

    Texture *texture = new Texture;
    texture->devilId = ilGenImage();
    ilBindImage( texture->devilId );
    ilLoadImage( fileName.toAscii() );
    ilConvertImage( IL_RGB, IL_UNSIGNED_BYTE );
    texture->width = ilGetInteger( IL_IMAGE_WIDTH );
    texture->height = ilGetInteger( IL_IMAGE_HEIGHT );
    texture->data = ilGetData();

    std::string textureNameValue = samplerId.remove( "-sampler" ).toStdString();
    material->setTextureName( textureType, textureNameValue );
    Mesh::addTexture( textureNameValue, texture );
}

Node* ColladaMeshFactory::getNodes(const QStringList &jointNames, SkeletonController *controller)
{
    // assume first node on the list is the root node
    QDomElement rootNode = findNode( "node", "id", jointNames.at( 0 ) );

    if( rootNode.isNull() )
        return 0;

    Node *joint = getNodeData( rootNode, controller );

    return joint;
}

Node* ColladaMeshFactory::getNodeData(QDomElement &jointElement, AnimationController *controller)
{    
    Node *currentNode;

    QString nodeName = jointElement.attribute( "id" );

    if( jointElement.attribute( "type" ) == "JOINT" ) {
        currentNode = new Joint;

    } else if( jointElement.tagName() == "instance_geometry" ) {
        QString meshName = jointElement.attribute( "url" ).remove( 0, 1 );
        nodeName = meshName;
        currentNode = getMesh( meshName );

    } else {
        currentNode = new Node;
    }

    if( controller )
        controller->addNode( nodeName.toStdString(), currentNode );

    QDomNodeList childNodes = jointElement.childNodes();

    for( int i = 0; i < childNodes.size(); ++i ) {
        QDomElement element = childNodes.at( i ).toElement();
        QString tagName = element.tagName();

        if( tagName == "node" || tagName == "instance_geometry" ) {
            currentNode->addChild( getNodeData( element, controller ) );

        } else if( tagName == "rotate" || tagName == "translate" || tagName == "scale" ) {
            Transformation *transformation = new Transformation;
            transformation->name = element.attribute( "sid" ).toStdString();
            if( tagName == "translate" )
                transformation->type = Transformation::Translation;
            else if( tagName == "rotate" )
                transformation->type = Transformation::Rotation;
            else
                transformation->type = Transformation::Scale;

            transformation->data = getVector( "", jointElement, 0, "sid",
                                             QString::fromStdString( transformation->name ) );

            currentNode->addTransformation( transformation->name, transformation );
        }
    }

    return currentNode;
}

Animation* ColladaMeshFactory::getAnimation(AnimationController *controller)
{
    QDomElement animationsLibrary = findNodeByTagName( "library_animations" );

    if( animationsLibrary.isNull() )
        return 0;

    Animation *animation = new Animation( controller );

    QDomNodeList animationsList = animationsLibrary.childNodes();

    for( int i = 0;i < animationsList.size(); ++i ) {
        QDomElement animationElement = animationsList.at( i ).toElement();
        QDomElement channelElement = findNodeByTagName( "channel", animationElement );
        QStringList target = channelElement.attribute( "target" ).split( QRegExp( "[/.]" ) );

        if( !controller->node( target.at( 0 ).toStdString() ) ) {
            qDebug() << "Cannot find joint " << target.at( 0 );
            continue;
        }

        Node* joint = controller->node( target.at( 0 ).toStdString() );
        string targetTransformName = target.at( 1 ).toStdString();

        Transformation *transformation = joint->transformation( targetTransformName );
        if( !transformation ) {
            qDebug() << "Joint " << target.at( 0 ) << " has no transformation named "
                     << target.at( 1 );
            continue;
        }

        string targetName = target.at( 0 ).toStdString();
        QDomElement samplerElement = findNodeByTagName( "sampler", animationElement );
        unsigned int dataCount;
        QDomElement inputSource = findNode( "source", "id",
                                            findNode( "input", "semantic", "INPUT",
                                                      samplerElement )
                                                        .attribute( "source" ) );
        float *input = getVector( "float_array", inputSource, &dataCount );

        unsigned int dimension;
        float *output = getVector( "source", animationElement, &dimension, "id",
                                   findNode( "input", "semantic", "OUTPUT", samplerElement )
                                        .attribute( "source" ) );
        dimension /= dataCount;

        unsigned int tangentCount;
        float *intangents = getVector( "source", animationElement, &tangentCount, "id",
                                       findNode( "input", "semantic", "IN_TANGENT", samplerElement )
                                          .attribute( "source" ) );
        bool completeTangents = tangentCount == dimension * dataCount * 2 ? true : false;

        float *outtangents = getVector( "source", animationElement, 0, "id",
                                        findNode( "input", "semantic", "OUT_TANGENT", samplerElement )
                                          .attribute( "source" ) );

        AnimationSampler::TargetType destination;
        if( target.size() == 3 && dimension == 1 ) {
            QString singleTarget = target.at( 2 );

            if( singleTarget == "ANGLE" )
                destination = AnimationSampler::Angle;
            else if( singleTarget == "X" )
                destination = AnimationSampler::X;
            else if( singleTarget == "Y" )
                destination = AnimationSampler::Y;
            else if( singleTarget == "Z" )
                destination = AnimationSampler::Z;
        } else {
            // means we write `dimension` elements to `targetValueName`
            destination = AnimationSampler::Continous;
        }

        // load interpolation data here
        QString interpolationTagId = findNode( "input", "semantic", "INTERPOLATION",
                                               samplerElement ).attribute( "source" );
        QStringList interpolationNames = findNode( "source", "id", interpolationTagId,
                                                   animationElement ).text().split( " " );

        AnimationSampler::InterpolationType *interpolations =
                new AnimationSampler::InterpolationType[ dataCount ];
        for( int i = 0; i < interpolationNames.size(); ++i )
            if( interpolationNames.at( i ) == "BEZIER" )
                interpolations[ i ] = AnimationSampler::Bezier;

        animation->addSampler( new AnimationSampler( controller, targetName, targetTransformName,
                                                     destination, input, output, intangents,
                                                     outtangents, completeTangents,
                                                     dataCount, dimension ) );
    }

    return animation;
}

AnimationController* ColladaMeshFactory::getAnimationController(const QString &rootNodeId)
{
    AnimationController *controller = new AnimationController;

    QDomElement rootElement = findNode( "node", "id", rootNodeId );

    Node *rootNode = getNodeData( rootElement, controller );
    controller->setRootNode( rootNode );

    return controller;
}

Node* ColladaMeshFactory::getScene(const QString &rootNodeId)
{
    QDomElement rootElement = findNode( "node", "id", rootNodeId );

    return  getNodeData( rootElement );
}

bool ColladaMeshFactory::writeToFile(const QString &fileName, Mesh *rootNode)
{
    QFile file( fileName );
    if( !file.open( QIODevice::WriteOnly ) )
        return false;

    QDataStream out( &file );

    return writeMesh( rootNode, out );
}

bool ColladaMeshFactory::writeMesh(const Mesh *mesh, QDataStream &out)
{
    out << (quint32)MeshSource;
    out.writeBytes( mesh->mName.c_str(), mesh->mName.size() );
    out << (quint32)mesh->mTriangles.size();

    foreach( Triangles *triangles, mesh->mTriangles )
        writeTriangles( triangles, out );

    uint dataSize = mesh->mDataCount * sizeof( float );

    for( uint i = 0; i < Mesh::DataPositionCount; ++i ) {
        if( mesh->mData[ i ] ) {
            int dataCountPerVertex = 3;
            if( i == Mesh::Color )
                dataCountPerVertex = 4;
            else if( i == Mesh::TexCoord )
                dataCountPerVertex = 2;

            out.writeBytes( (char*)mesh->mData[ i ], dataSize * dataCountPerVertex );
        } else
            out << (quint32)0;
    }

    return true;
}

bool ColladaMeshFactory::writeTriangles(const Triangles *triangles, QDataStream &out)
{
    out.writeBytes( triangles->mMaterialName.c_str(), triangles->mMaterialName.size() );
    out.writeBytes( (char*)triangles->mIndices, triangles->mIndicesCount * sizeof( uint ) );

    return true;
}

Mesh* ColladaMeshFactory::readFromFile(const QString &fileName)
{
    QFile file( fileName );
    if( !file.open( QIODevice::ReadOnly ) )
        return false;

    QDataStream in( &file );

    quint32 typ;
    in >> typ;
    if( typ != MeshSource )
        return 0;

    char *nazwa;
    quint32 dlugosc;
    in.readBytes( nazwa, dlugosc );
    Mesh *mesh = new Mesh( string( nazwa, dlugosc ) );
    delete []nazwa;

    quint32 iloscZestawowTrojkatow;
    in >> iloscZestawowTrojkatow;
    for( uint i = 0; i < iloscZestawowTrojkatow; ++i ) {
        readTriangles( mesh, in );

        QString matName = QString::fromStdString( mesh->mTriangles.back()->mMaterialName );
        processMaterial( matName, matName );
    }

    for( uint i = 0; i < Mesh::DataPositionCount; ++i ) {
        int dataCountPerVertex = 3;
        if( i == Mesh::Color )
            dataCountPerVertex = 4;
        else if( i == Mesh::TexCoord )
            dataCountPerVertex = 2;

        quint32 size;
        char *data;
        in.readBytes( data, size );

        if( size != 0 ) {
            mesh->mData[ i ] = (float*)data;
            mesh->mDataCount = size / dataCountPerVertex / sizeof( float );

        } else
            mesh->mData[ i ] = 0;
    }

    mesh->shaderProgramType = GLWrapper::TextureShader;

    Mesh::addMesh( mesh->name(), mesh );

    return mesh;
}

void ColladaMeshFactory::readTriangles(Mesh *mesh, QDataStream &in)
{
    Triangles *triangles = new Triangles;

    char *nazwa;
    quint32 dlugosc;
    in.readBytes( nazwa, dlugosc );
    triangles->mMaterialName = string( nazwa, dlugosc );
    delete []nazwa;

    char *indices;
    quint32 indicesCount;
    in.readBytes( indices, indicesCount );
    triangles->mIndicesCount = indicesCount / sizeof( uint );
    triangles->mIndices = ( uint* )indices;

    mesh->mTriangles.push_back( triangles );
}
