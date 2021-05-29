#pragma once

#include "Animation.h"
#include "../util/ExtendedMath.h"

class ObjectAnimation : public Animation
{
public:
	ObjectAnimation();
	explicit ObjectAnimation(
		const float &animation_length,
		const float &animation_speed,
		const em::Matrix4f &image1start,
		const em::Matrix4f &image2start,
		const em::Matrix4f &image1end,
		const em::Matrix4f &image2end);

	virtual ~ObjectAnimation() = default;

	inline virtual const em::Matrix4f &getImage1Frame(const float &current_time) const = 0;
	inline virtual const em::Matrix4f &getImage2Frame(const float &current_time) const = 0;

	const em::Matrix4f &getStartingTransform1() const;
	const em::Matrix4f &getStartingTransform2() const;
	const em::Matrix4f &getEndingTransform1() const;
	const em::Matrix4f &getEndingTransform2() const;

	void setStartingTransform1(const em::Matrix4f &im1_start);
	void setStartingTransform2(const em::Matrix4f &im2_start);
	void setEndingTransform1(const em::Matrix4f &im1_end);
	void setEndingTransform2(const em::Matrix4f &im2_end);

protected:
	em::Matrix4f m_image1Start;	///> starting position of image1
	em::Matrix4f m_image2Start;	///> starting position of image2
	em::Matrix4f m_image1End;	///> finishing position of image1
	em::Matrix4f m_image2End;	///> finishing position of image2

private:
	
};
