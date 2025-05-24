#pragma once
#include <raylib.h>
#include <magic_enum/magic_enum.hpp>

enum class MainMenuState {
	PLAY,
	SETTINGS,
	HELP,
	EXIT,
	OPTION_COUNT
};

class MainMenu
{
private:
	int totalOptions;
	int currentOption;
	Texture normalMenuButton;
	Texture hoverMenuButton;
	MainMenuState state;

public:
	MainMenu();
	~MainMenu();

	void Update();
	void Draw(const int fontSize, const int spacing, const Font& font1, const Font& font2, const Color& color1, const Color& color2, const Color& backgroundColor) const;
};

