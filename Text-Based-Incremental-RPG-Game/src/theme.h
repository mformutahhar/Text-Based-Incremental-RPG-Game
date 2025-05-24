#pragma once
#include <raylib.h>

class Theme
{
private:
	Color backgroundColor;
	Color textColor;
	Color headColor;
	Color boxColor;

public:
	Theme();
	~Theme() = default;
	
	const Color& getBackgroundColor() const { return backgroundColor; }
	const Color& getTextColor() const { return textColor; }
	const Color& getHeadColor() const { return headColor; }
	const Color& getBoxColor() const { return boxColor; }
};

