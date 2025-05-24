#pragma once
#include <raylib.h>

class FontManager
{
private:
	int textFontSize;
	int headFontSize;
	float headFontSpacing;

	Font headFont;
	Font textFont;

public:
	FontManager();
	~FontManager();

	int GetHeadFontSize() const { return headFontSize; }
	int GetTextFontSize() const { return textFontSize; }

	float GetHeadSpacing() const { return headFontSpacing; }

	const Font& GetHeadFont() const { return headFont; }
	const Font& GetTextFont() const { return textFont; }
};

