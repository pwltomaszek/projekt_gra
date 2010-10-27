#ifndef NODEPROTO_H
#define NODEPROTO_H

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
    Transformation* transformation( const std::string &name );
    Transformation* transformation( const unsigned int &index );
    unsigned int transformationCount() const;
    const glm::mat4& transformationMatrix() const;

protected:
    std::vector< Node* > mChildren;
    PairVector< std::string, Transformation* > mTransformations;
    glm::mat4 mTransformationMatrix;
};

#endif // NODEPROTO_H
