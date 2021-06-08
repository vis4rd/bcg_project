#include "../../include/animation/SlideAnimation.h"

SlideAnimation::SlideAnimation()
:
ObjectAnimation()
{

}


SlideAnimation::SlideAnimation(
    const float &animation_length,
    const float &animation_speed,
    const em::Matrix4f &image1start,
    const em::Matrix4f &image2start,
    const em::Matrix4f &image1end,
    const em::Matrix4f &image2end)
:ObjectAnimation(animation_length,animation_speed,image1start,image2start,image1end,image2end)
{
}