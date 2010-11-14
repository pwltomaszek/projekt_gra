#ifndef NODEPROTO_H
#define NODEPROTO_H

#include <map>
#include <string>
#include <vector>

#include "glm/glm/glm.hpp"

#include "glmadapter.h"
#include "pairvector.h"

#include <iostream>

class Transformation;

class Node
{
public:
    Node();

    void addChild( Node *child );
    void addTransformation( const std::string &name, Transformation *transformation );
    virtual void calculateTransformMatrix( const glm::mat4 *parentMatrix = 0 );
    virtual void draw();
    void processTransformations();
    Node* scene( const std::string &name );
    Transformation* transformation( const std::string &name );
    Transformation* transformation( const unsigned int &index );
    unsigned int transformationCount() const;
    const glm::mat4& transformationMatrix() const;

    static void addNode( const std::string &name, Node *node );
    static Node* node( const std::string &name );

protected:
    std::vector< Node* > mChildren;
    PairVector< std::string, Transformation* > mTransformations;
    glm::mat4 mTransformationMatrix;

    static PairVector< std::string, Node* > mNodes;
};

#endif // NODEPROTO_H
