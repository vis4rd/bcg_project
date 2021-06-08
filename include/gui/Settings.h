#pragma once
#include "../animation/Animation.h"

class Settings
{
public:	

	static Settings * getInstance();

	Settings(Settings& oth) = delete;
	Settings(Settings&& oth) = delete;
	void operator=(const Settings &) = delete;
	void operator=(Settings &&) = delete;
	
	std::string getPath1() const;
	std::string getPath2() const;
	unsigned short getCurrentAnim() const;

	void setPath1(const std::string &path1);
	void setPath2(const std::string &path2);
	void setCurrentAnim(unsigned short anim);

private:
	Settings() = default;
	std::string m_path1;
	std::string m_path2;
	unsigned short m_anim;
	static Settings* setting;

};