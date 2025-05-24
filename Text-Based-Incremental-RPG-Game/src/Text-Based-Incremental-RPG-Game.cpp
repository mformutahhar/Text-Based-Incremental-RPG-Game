#include <raylib.h>
#include <stdio.h>
#include "font-manager.h"
#include "theme.h"
#include "game.h"
//#include <iostream>
//#include <filesystem>

void InitGame(const char*);

int main() {

    constexpr const char* windowTitle = "TEXT BASED INCREMENTAL RPG GAME";

    InitGame(windowTitle);

    FontManager fonts;
    Theme theme;
    Game game;

    //std::cout << "Working Dir: " << std::filesystem::current_path() << std::endl;


    while (!WindowShouldClose()) {
        game.Update();
        BeginDrawing();
        ClearBackground(theme.getBackgroundColor());

        game.Draw(fonts.GetHeadFontSize(), fonts.GetHeadSpacing(), fonts.GetHeadFont(), theme.getHeadColor(), theme.getBoxColor());

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void InitGame(const char* name) {
    //SetTraceLogLevel(LOG_ERROR); // not needed if console is disabled

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(0, 0, name);
    SetTargetFPS(30);

    Image icon = LoadImage("assets/images/icon.png");
    SetWindowIcon(icon);
    UnloadImage(icon);

    int monitorW = GetMonitorWidth(0);
    int monitorH = GetMonitorHeight(0);

    int winW = monitorW / 1.2f;
    int winH = monitorH / 1.2f;

    SetWindowSize(winW, winH);
    SetWindowPosition((monitorW - winW) / 2, (monitorH - winH) / 2);
}
