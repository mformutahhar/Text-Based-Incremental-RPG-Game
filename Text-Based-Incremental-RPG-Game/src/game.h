#pragma once  
#include "main-menu.h"  

class Game  
{  
private:  
	MainMenu mainMenu;

public:  
	Game();  
	~Game();  

	void Update();
	void Draw(const int fontSize, const int spacing, const Font& font1, const Font& font2, const Color& color1, const Color& color2, const Color& backgroundColor) const;
};
