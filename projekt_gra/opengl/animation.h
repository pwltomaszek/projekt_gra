#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>

#include "node.h"

class AnimationController;
class AnimationSampler;

class Animation {
public:
    Animation( AnimationController *controller );

    void addSampler( AnimationSampler *sampler );
    AnimationController* controller();
    void updateController( unsigned int time );

private:
    std::vector< AnimationSampler* > mAnimations;
    AnimationController *mController;
};

#endif // ANIMATION_H
