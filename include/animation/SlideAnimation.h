#pragma once
#include "ObjectAnimation.h"


class SlideAnimation : public ObjectAnimation
{
    public:

    SlideAnimation();
    explicit SlideAnimation(
        const float &animation_length,
        const float &animation_speed,
        const em::Matrix4f &image1start,
        const em::Matrix4f &image2start,
        const em::Matrix4f &image1end,
        const em::Matrix4f &image2end);

    ~SlideAnimation() = default;

    inline const em::Matrix4f getImage1Frame(const float &current_time) const override
    {
        em::Matrix4f temp = m_image1Start;
        temp.translate( sf::Vector3f( 960.f*(current_time/m_totalTime) , 0.f, 0.f) );
        return temp;
    }

    inline const em::Matrix4f getImage2Frame(const float &current_time) const override
    {
        em::Matrix4f temp = m_image1Start;
        temp.translate( sf::Vector3f( - 960.f*(1 - current_time/m_totalTime), 0, 0) );
        return temp;
    }

};
