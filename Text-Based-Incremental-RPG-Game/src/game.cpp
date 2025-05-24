#include "game.h"

Game::Game() {

}

Game::~Game() {

}

void Game::Update() {
	mainMenu.Update();
}

void Game::Draw(const int fontSize, const int spacing, const Font& font1, const Font& font2, const Color& color1, const Color& color2, const Color& backgroundColor) const {
	mainMenu.Draw(fontSize, spacing, font1, font2, color1, color2, backgroundColor);
}
