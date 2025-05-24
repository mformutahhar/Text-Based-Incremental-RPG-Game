#include "font-manager.h"

FontManager::FontManager() {
	textFontSize = 50;
	headFontSize = static_cast<int>(textFontSize * 1.2f);

	headFontSpacing = 2.0f;

	headFont = LoadFontEx("assets/fonts/LuckiestGuy-Regular.ttf", headFontSize, 0, 0);
	textFont = LoadFontEx("assets/fonts/FreckleFace-Regular.ttf", textFontSize, 0, 0);
}

FontManager::~FontManager() {
	UnloadFont(headFont);
	UnloadFont(textFont);
}