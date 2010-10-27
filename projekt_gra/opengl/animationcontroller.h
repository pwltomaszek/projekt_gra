#ifndef ANIMATIONCONTROLLERPROTO_H
#define ANIMATIONCONTROLLERPROTO_H

#include <string>

#include "node.h"
#include "pairvector.h"

class Node;

class AnimationController : public Node
{
public:
    AnimationController();

    void addNode( const std::string &string, Node *node );
    virtual void calculateTransformMatrix();
    virtual void draw();
    Node* node( const std::string &string );
    Node* node( const unsigned int &index );
    void setRootNode( Node *node );

protected:
    Node *mRootNode;
    PairVector< std::string, Node* > mNodes;
};

#endif // ANIMATIONCONTROLLERPROTO_H
