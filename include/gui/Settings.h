#pragma once
#include "../animation/Animation.h"
/**
 * @brief      Singleton class, responsible for storing the settings of the entire program
 * 			   All constructors are deleted to prevent the creation of new objects of this type
 * 			   Move and copy constructors are also deleted
 */
class Settings
{
public:	
	/**
	 * @brief      Getter for the instance.
	 *
	 * @return     The instance.
	 */
	static Settings *getInstance();
	
	Settings(Settings& oth) = delete;
	Settings(Settings&& oth) = delete;
	void operator=(const Settings &) = delete;
	void operator=(Settings &&) = delete;
	/**
	 * @brief      The path to the first image loaded to program.
	 *
	 * @return     m_path1.
	 */
	std::string getPath1() const;
	/**
	 * @brief      The path to the second image loaded to program
	 *
	 * @return     m_path2.
	 */
	std::string getPath2() const;
	/**
	 * @brief      Gets the current animation.
	 *
	 * @return     m_anim.
	 */
	unsigned short getCurrentAnim() const;
	/**
	 * @brief      Gets the current number of frames.
	 *
	 * @return     m_frames.
	 */
	unsigned short getCurrentFrames() const;
	/**
	 * @brief      Sets m_path1.
	 *
	 * @param[in]  path1  The path 1
	 */
	void setPath1(const std::string &path1);
	/**
	 * @brief      Sets m_path2.
	 *
	 * @param[in]  path2  The path 2
	 */
	void setPath2(const std::string &path2);
	/**
	 * @brief      Sets the current animation.
	 *
	 * @param[in]  anim  The animation
	 */
	void setCurrentAnim(unsigned short anim);
	/**
	 * @brief      Sets the current number of frames.
	 *
	 * @param[in]  frames  The frames
	 */
	void setCurrentFrames(unsigned short frames);

private:
	Settings() = default;
	std::string m_path1;
	std::string m_path2;
	unsigned short m_anim;
	unsigned short m_frames;
	static Settings* setting;

};