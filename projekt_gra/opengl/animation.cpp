#include "animation.h"
#include "animationcontroller.h"
#include "animationsampler.h"
#include "common.h"

//#include <boost/foreach.hpp>

using namespace std;

Animation::Animation(AnimationController *controller)
    : mController( controller )
{

}

void Animation::updateController(unsigned int time)
{
    for( unsigned int i = 0; i < mAnimations.size(); ++i )
        mAnimations.at( i )->applyData( time / 1000.f );

//    BOOST_FOREACH( AnimationSampler *sampler, mAnimations )
//        sampler->applyData( time / 1000.f );

    mController->calculateTransformMatrix();
}

AnimationController* Animation::controller()
{
    return mController;
}

void Animation::addSampler(AnimationSampler *sampler)
{
    mAnimations.push_back( sampler );
}
