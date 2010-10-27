#ifndef SKELETONCONTROLLER_H
#define SKELETONCONTROLLER_H

#include "animationcontroller.h"
#include "glmadapter.h"

class Mesh;

class SkeletonController : public AnimationController {
public:
    SkeletonController( Mesh *mesh );

    const glm::mat4& bindShapeMatrix() const;
    virtual void draw();
    unsigned int jointIndex( const unsigned int &index ) const;
    unsigned int jointsPerVertex( unsigned int &vertexIndex ) const;
    void setBindShapeMatrix( const float *array );
    void setJointAndWeightIndices( unsigned int *array );
    void setJointsPerVertex( unsigned int *array );
    void setWeights( float *array );
    float weight( const unsigned int &index ) const;

private:
    glm::mat4 mBindShapeMatrix;
    float *mWeights;
    Mesh *mMesh;
    unsigned int *mJointsPerVertex;
    unsigned int *mJointAndWeightIndices;
};

#endif // SKELETONCONTROLLER_H
