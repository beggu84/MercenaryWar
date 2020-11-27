#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "cocos2d.h"

#include "GetterSetter.h"

#define MY_FONT "fonts/IropkeBatangM.ttf"
#define ROUND_BUTTON "buttons/Round"

#define TO_REAL(pixel) Settings::Instance().ToReal(pixel)

#define GREAT_FONT_SIZE		TO_REAL(16.f)
#define BIG_FONT_SIZE		TO_REAL(14.f)
#define NORMAL_FONT_SIZE	TO_REAL(12.f)
#define SMALL_FONT_SIZE		TO_REAL(10.f)

#define HORI_LONG_MARGIN	TO_REAL(9.f)
#define HORI_NORMAL_MARGIN	TO_REAL(7.f)
#define HORI_SHORT_MARGIN	TO_REAL(5.f)
#define VERT_LONG_MARGIN	TO_REAL(3.f)
#define VERT_NORMAL_MARGIN	TO_REAL(2.f)
#define VERT_SHORT_MARGIN	TO_REAL(1.f)

class Settings
{
private:
	float _screenWidth{ 0.f };
	float _warBriefHeight{ 0.f };

public:
	static Settings& Instance()
	{
		static Settings instance;
		return instance;
	}

	GETTER(float, ScreenWidth, _screenWidth);
	GETTER(float, WarBriefHeight, _warBriefHeight);

	void SetScreenWidth(float screenWidth)
	{
		_screenWidth = screenWidth;
		_warBriefHeight = screenWidth * 0.27f;
	}

	float ToReal(float pixel)
	{
		return _warBriefHeight / 100.f * pixel;
	}
};

#endif // __SETTINGS_H__
