#include <QDebug>

#include "common.h"
#include "node.h"
#include "opengl.h"
#include "transformation.h"

//#include <boost/foreach.hpp>

using namespace std;

PairVector< string, Node* > Node::mNodes;

Node::Node()
    : mTransformationMatrix( 1.f )
{
}

Transformation* Node::transformation(const std::string &name)
{
    return mTransformations.find( name );
}

Transformation* Node::transformation(const unsigned int &index)
{
    return mTransformations.at( index );
}

void Node::calculateTransformMatrix(const glm::mat4 *parentMatrix)
{
    if( parentMatrix )
        mTransformationMatrix = *parentMatrix;
    else
        mTransformationMatrix = glm::mat4( 1.f );

    processTransformations();

    for( unsigned int i = 0; i < mChildren.size(); ++i )
        mChildren.at( i )->calculateTransformMatrix();
}

const glm::mat4& Node::transformationMatrix() const
{
    return mTransformationMatrix;
}

void Node::addChild(Node *child)
{
    mChildren.push_back( child );
}

void Node::addTransformation(const std::string &name, Transformation *transformation)
{
    mTransformations.push_back( name, transformation );
}

unsigned int Node::transformationCount() const
{
    return mTransformations.size();
}

void Node::draw()
{
    GLWrapper &gl = GLWrapper::instance();

    gl.pushMatrix();
    gl.multMatrix( mTransformationMatrix );

    for( unsigned int i = 0; i < mChildren.size(); ++i )
        mChildren.at( i )->draw();

//    BOOST_FOREACH( Node *child, mChildren )
//        child->draw();

    gl.popMatrix();
}

void Node::processTransformations()
{
    for( unsigned int i = 0; i < mTransformations.size(); ++i ) {
        Transformation *transformation = mTransformations.at( i );
        glm::vec3 vec = GLMAdapter::vec3( transformation->data );

        if( transformation->type == Transformation::Translation ) {
            mTransformationMatrix = glm::translate( mTransformationMatrix, vec );
        } else if( transformation->type == Transformation::Rotation ) {
            mTransformationMatrix = glm::rotate( mTransformationMatrix,
                                                 transformation->data[ 3 ], vec );
        } else if( transformation->type == Transformation::Scale ) {
            mTransformationMatrix = glm::scale( mTransformationMatrix, vec );
        } else {
            qDebug() << "Oops!";
        }
    }
}

Node* Node::node(const std::string &name)
{
    return mNodes.at( name );
}

void Node::addNode(const std::string &name, Node *node)
{
    mNodes.push_back( name, node );
}
