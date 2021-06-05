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
	Animation* getCurrentAnim() const;

	void setPath1(const std::string &path1);
	void setPath2(const std::string &path2);
	void setCurrentAnim(Animation* anim);

private:
	Settings() = default;
	std::string m_path1;
	std::string m_path2;
	Animation* m_anim;
	static Settings* setting;

};