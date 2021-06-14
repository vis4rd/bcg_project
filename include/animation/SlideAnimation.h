#pragma once
#include "ObjectAnimation.h"

/**
 * @brief      class responsible for animating the transition between two pictures,
 *             the first picture moves to the right
 *             and at the same time it is replaced by the second picture moving from the left side of the screen to the ride
 */
class SlideAnimation : public ObjectAnimation
{
    public:
    /**
     * default constructor
     */
    SlideAnimation();
    /**
     * @brief      Constructor setting animation startup parameters
     *
     * @param[in]  animation_length  The animation length
     * @param[in]  animation_speed   The animation speed
     * @param[in]  image1start       The image 1 start position
     * @param[in]  image2start       The image 2 start position
     * @param[in]  image1end         The image 1 end position 
     * @param[in]  image2end         The image 2 end position
     */
    explicit SlideAnimation(
        const float &animation_length,
        const float &animation_speed,
        const em::Matrix4f &image1start,
        const em::Matrix4f &image2start,
        const em::Matrix4f &image1end,
        const em::Matrix4f &image2end);
    /**
     * @brief      default destructor
     */
    ~SlideAnimation() = default;
    /**
     * @brief      Performs transformations on the first image
     *
     * @param[in]  current_time  The current time animation
     *
     * @return     The image 1 frame.
     */
    inline const em::Matrix4f getImage1Frame(const float &current_time) const override
    {
        em::Matrix4f temp = m_image1Start;
        temp.translate( sf::Vector3f( 960.f*(current_time/m_totalTime) , 0.f, 0.f) );
        return temp;
    }
    /**
     * @brief      Performs transformations on the second image
     *
     * @param[in]  current_time  The current time of animation
     *
     * @return     The image 2 frame.
     */
    inline const em::Matrix4f getImage2Frame(const float &current_time) const override
    {
        em::Matrix4f temp = m_image1Start;
        temp.translate( sf::Vector3f( - 960.f*(1 - current_time/m_totalTime), 0, 0) );
        return temp;
    }

};
