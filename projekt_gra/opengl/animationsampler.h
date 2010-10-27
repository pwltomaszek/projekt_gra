#ifndef ANIMATIONSAMPLER_H
#define ANIMATIONSAMPLER_H

#include <string>

#include "animation.h"

class AnimationSampler {
public:
    enum TargetType {
        Continous = -1,
        X,
        Y,
        Z,
        Angle
    };

    enum InterpolationType {
        Bezier
    } *mInterpolations;

    AnimationSampler( AnimationController *controller, const std::string &targetName,
                      const std::string &targetValueName, const TargetType &destination,
                      float *input, float *output, float *intangents, float *outtangents,
                      bool completeTangents, const unsigned int &dataCount,
                      const unsigned int &dimension );

    void applyData( float deltaTime );

private:
    unsigned int mDataCount, mDimensionCount;
    bool mCompleteTangents;
    float *mInput, *mOutput, *mIntangents, *mOuttangents;
    std::string mTargetName, mTargetValueName;
    TargetType mOutputTarget;
    AnimationController *mController;
};

#endif // ANIMATIONSAMPLER_H
