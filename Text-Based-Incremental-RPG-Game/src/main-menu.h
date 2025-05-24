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
	MainMenuState state;

public:
	MainMenu();
	~MainMenu() = default;

	void Update();
	void Draw(const int fontSize, const int spacing, const Font& font, const Color& color, const Color& boxColor) const;
};

