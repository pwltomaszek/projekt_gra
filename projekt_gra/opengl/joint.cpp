#include "joint.h"

//#include <boost/foreach.hpp>

using namespace std;

Joint::Joint()
{

}

void Joint::setInvBindMatrix( const float *array )
{
    mInvBindMatrix = GLMAdapter::mat4( array );
}

const glm::mat4& Joint::invBindMatrix() const
{
    return mInvBindMatrix;
}

void Joint::calculateTransformMatrix(const glm::mat4 *parentMatrix)
{
    if( parentMatrix )
        mTransformationMatrix = *parentMatrix;
    else
        mTransformationMatrix = glm::mat4( 1.f );

    processTransformations();

    for( unsigned int i = 0; i < mChildren.size(); ++i )
        mChildren.at( i )->calculateTransformMatrix( &mTransformationMatrix );

//    BOOST_FOREACH( Node *child, mChildren )
//        child->calculateTransformMatrix( &mTransformationMatrix );
}
