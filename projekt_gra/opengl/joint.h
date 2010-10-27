#ifndef JOINT_H
#define JOINT_H

#include "glmadapter.h"
#include "node.h"

class Joint : public Node {
public:
    Joint();

    virtual void calculateTransformMatrix( const glm::mat4 *parentMatrix = 0 );
    const glm::mat4& invBindMatrix() const;
    void setInvBindMatrix( const float *array );

private:
    glm::mat4 mInvBindMatrix;
};

#endif // JOINT_H
