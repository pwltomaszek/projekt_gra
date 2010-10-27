#include "animationcontroller.h"
#include "animationsampler.h"
#include "interpolation.h"
#include "node.h"
#include "transformation.h"

#include <QDebug>

using namespace std;

AnimationSampler::AnimationSampler(AnimationController *controller, const std::string &targetName,
                                   const std::string &targetValueName,
                                   const TargetType &destination, float *input, float *output,
                                   float *intangents, float *outtangents, bool completeTangents,
                                   const unsigned int &dataCount, const unsigned int &dimension)
    : mController( controller ),
      mTargetName( targetName ),
      mTargetValueName( targetValueName ),
      mOutputTarget( destination ),
      mInput( input ),
      mOutput( output ),
      mIntangents( intangents ),
      mOuttangents( outtangents ),
      mCompleteTangents( completeTangents ),
      mDataCount( dataCount ),
      mDimensionCount( dimension )
{
}

void AnimationSampler::applyData(float time)
{
    unsigned int animSegment = 0;
    while( animSegment < mDataCount - 2 ) {
        if( mInput[ animSegment + 1 ] > time )
            break;

        ++animSegment;
    }

    float p0x = mInput[ animSegment ];
    float *p0y = &mOutput[ animSegment * mDimensionCount ];

    float p1x = mInput[ animSegment + 1 ];
    float *p1y = &mOutput[ ( animSegment + 1 ) * mDimensionCount ];

    float c0x, c1x;
    float *c0y, *c1y;
    if( mCompleteTangents ) {
        c0x = mOuttangents[ animSegment * 2 * mDimensionCount ];
        c0y = &mOuttangents[ animSegment * 2 * mDimensionCount + 1 ];

        c1x = mIntangents[ ( animSegment + 1 ) * 2 * mDimensionCount  ];
        c1y = &mIntangents[ ( animSegment + 1 ) * 2 * mDimensionCount + 1 ];

    } else {
        c0x = mInput[ animSegment ] / 3 + mInput[ animSegment + 1 ] * 2 / 3;
        c0y = &mOuttangents[ animSegment * mDimensionCount + 1 ];

        c0x = mInput[ animSegment ] * 2 / 3 + mInput[ animSegment + 1 ] / 3;
        c1y = &mIntangents[ ( animSegment + 1 ) * mDimensionCount + 1 ];
    }

    float s = Interpolation::approximateCubicBezierParameter( time, p0x, c0x, c1x, p1x );
    float *interpolatedValues = Interpolation::bezierInterpolation( s, p0y, c0y, c1y, p1y,
                                                                    mDimensionCount );
//    qDebug() << interpolatedValues[ 0 ];

    Node *node = mController->node( mTargetName );

//    bool ok = false;
//    for( int i = 0; i < mController->mNodes.size(); ++i ) {
//        Node *node = mController->mNodes.at( i );
//        for( int j = 0; j < node->mChildren.size(); ++j ) {
//            if( joint == node->mChildren.at( j ) ) {
//                joint = node;
//                ok = true;
//                break;
//            }
//        }
//        if( ok )
//            break;
//    }

    Transformation *transformation = node->transformation( mTargetValueName );

    TargetType target = mOutputTarget;
    if( target == Continous )
        target = X;

    for( unsigned int i = 0; i < mDimensionCount; ++i )
        transformation->data[ target + i ] = interpolatedValues[ i ];

    delete []interpolatedValues;
}
