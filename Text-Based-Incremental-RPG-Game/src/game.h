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
	void Draw(const int fontSize, const int spacing, const Font& font, const Color& color, const Color& boxColor) const;
};
