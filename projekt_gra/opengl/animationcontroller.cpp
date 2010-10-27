#include <QDebug>

#include "animationcontroller.h"
#include "node.h"
#include "opengl.h"

AnimationController::AnimationController()
{
}

Node* AnimationController::node(const std::string &string)
{
    return mNodes.find( string );
}

Node* AnimationController::node(const unsigned int &index)
{
    return mNodes.at( index );
}

void AnimationController::addNode(const std::string &string, Node *node)
{
    mNodes.push_back( string, node );
}

void AnimationController::setRootNode(Node *node)
{
    mRootNode = node;
}

void AnimationController::calculateTransformMatrix()
{
    Node::calculateTransformMatrix();

    mRootNode->calculateTransformMatrix();

//    std::cout << mTransformationMatrix << "\n\n";

//    for( unsigned int i = 0; i < mNodes.size(); ++i )
//        std::cout << i << "\n" << mNodes.at( i )->transformationMatrix() << "\n\n";
}

void AnimationController::draw()
{
    GLWrapper &gl = GLWrapper::instance();
    
    gl.pushMatrix();
    gl.multMatrix( mTransformationMatrix );

    // draw the animation
    mRootNode->draw();

    gl.popMatrix();

    // draw child nodes
    Node::draw();
}
