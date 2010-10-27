#include <QDebug>

#include <iostream>

#include "joint.h"
#include "mesh.h"
#include "skeletoncontroller.h"

SkeletonController::SkeletonController(Mesh *mesh)
    : mMesh( mesh )
{

}

void SkeletonController::setBindShapeMatrix(const float *array)
{
    mBindShapeMatrix = GLMAdapter::mat4( array );
}

unsigned int SkeletonController::jointIndex(const unsigned int &index) const
{
    return mJointAndWeightIndices[ index * 2 ];
}

float SkeletonController::weight(const unsigned int &index) const
{
    return mWeights[ mJointAndWeightIndices[ index * 2 + 1 ] ];
}

void SkeletonController::setWeights(float *array)
{
    mWeights = array;
}

void SkeletonController::setJointAndWeightIndices(unsigned int *array)
{
    mJointAndWeightIndices = array;
}

unsigned int SkeletonController::jointsPerVertex(unsigned int &vertexIndex) const
{
    return mJointsPerVertex[ vertexIndex ];
}

const glm::mat4& SkeletonController::bindShapeMatrix() const {
    return mBindShapeMatrix;
}

void SkeletonController::setJointsPerVertex(unsigned int *array)
{
    mJointsPerVertex = array;
}

void SkeletonController::draw()
{
//    for( unsigned int i = 0; i < mNodes.size(); ++i ) {
//        Joint *joint = static_cast< Joint* >( node( i ) );
//        std::cout << i << " " << mNodes.key( joint ) << "\n\n" << joint->invBindMatrix() << "\n\n";
//        std::cout << glm::inverse( joint->transformationMatrix() ) << "\n================\n\n";
//    }

    unsigned int indicesIterator = 0;
    for( unsigned int i = 0; i < mMesh->dataCount(); ++i ) {
        unsigned int jointsPerCurrentVertex = jointsPerVertex( i );
        glm::vec4 newPosition;
        glm::vec4 oldPosition = glm::vec4( GLMAdapter::vec3( &mMesh->data( Mesh::Vertex )[ i * 3 ] ),
                                           1.f ) * mBindShapeMatrix;

        for( unsigned int j = 0; j < jointsPerCurrentVertex; ++j ) {
            glm::vec4 currentResult = oldPosition;

            unsigned int index = jointIndex( indicesIterator + j );
            Joint *joint = static_cast< Joint* >( node( index ) );

            currentResult = currentResult * joint->invBindMatrix();
//            std::cout << index << "\n" << joint->invBindMatrix() << "\n------------------\n";
            currentResult = currentResult * joint->transformationMatrix();
            currentResult = currentResult * weight( indicesIterator + j );

            newPosition = newPosition + currentResult;
        }
        indicesIterator += jointsPerCurrentVertex;

//        std::cout << oldPosition << "\n" << newPosition << "\n\n";

        for( int j = 0; j < 3; ++j )
            mMesh->data( Mesh::Vertex )[ i * 3 + j ] = newPosition[ j ];
    }

    // draw the skin
    mMesh->draw();

    // draw controller's children
    Node::draw();
}
