#include "../../include/animation/FlyAnimation.h"

FlyAnimation::FlyAnimation()
:
ObjectAnimation()
{

}


FlyAnimation::FlyAnimation(
	const float &animation_length,
	const float &animation_speed,
	const em::Matrix4f &image1start,
	const em::Matrix4f &image2start,
	const em::Matrix4f &image1end,
	const em::Matrix4f &image2end)
:ObjectAnimation(animation_length,animation_speed,image1start,image2start,image1end,image2end)
{
}

