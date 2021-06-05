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
Animation* Settings::getCurrentAnim() const
{
	return m_anim;
}

void Settings::setPath1(const std::string &path1)
{
	m_path1 = path1;
}
void Settings::setPath2(const std::string &path2)
{
	m_path2 = path2;
}
void Settings::setCurrentAnim(Animation* anim)
{
	m_anim = anim;
}

Settings * Settings::getInstance()
{
	if(setting == nullptr)
	{
		setting = new Settings();
	}
	return setting;
}
