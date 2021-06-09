#include "../../include/gui/Settings.h"

Settings* Settings::setting = nullptr;

std::string Settings::getPath1() const 
{
	return m_path1;
}
std::string Settings::getPath2() const
{
	return m_path2;
}
unsigned short Settings::getCurrentAnim() const
{
	return m_anim;
}
unsigned short Settings::getCurrentFrames() const
{
	return m_frames;
}

void Settings::setPath1(const std::string &path1)
{
	m_path1 = path1;
}
void Settings::setPath2(const std::string &path2)
{
	m_path2 = path2;
}
void Settings::setCurrentAnim(unsigned short anim)
{
	m_anim = anim;
}
void Settings::setCurrentFrames(unsigned short frames)
{
	m_frames = frames;
}

Settings* Settings::getInstance()
{
	if(setting == nullptr)
	{
		setting = new Settings();
	}
	return setting;
}
