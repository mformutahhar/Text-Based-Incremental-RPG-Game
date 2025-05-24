#include "game.h"

Game::Game() {

}

Game::~Game() {

}

void Game::Update() {
	mainMenu.Update();
}

void Game::Draw(const int fontSize, const int spacing, const Font& font, const Color& color, const Color& boxColor) const {
	mainMenu.Draw(fontSize, spacing, font, color, boxColor);
}
