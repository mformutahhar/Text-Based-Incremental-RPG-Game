#include <raylib.h>
#include <stdio.h>
#include "font-manager.h"
#include "theme.h"
#include "game.h"
#include "imageData.h"
#include <stdio.h>
//#include <iostream>
//#include <filesystem>

void InitGame(const char*);

int main() {

    constexpr const char* windowTitle = "TEXT BASED INCREMENTAL RPG GAME";

    InitGame(windowTitle);

    FontManager fonts;
    Theme theme;
    Game game;

    Texture2D backgroundTexture = LoadTexture("assets/images/background2.jpeg");

    //std::cout << "Working Dir: " << std::filesystem::current_path() << std::endl;


    while (!WindowShouldClose()) {

        game.Update();

        BeginDrawing();
        ClearBackground(theme.getBackgroundColor());

        DrawTexturePro(
            backgroundTexture,
            { 0, 0, static_cast<float>(backgroundTexture.width), static_cast<float>(backgroundTexture.height) },
            { 0, 0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) },
            { 0, 0 },
            0.0f,
            WHITE
        );

        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color {0, 0, 0, 100}));

        game.Draw(fonts.GetHeadFontSize(), fonts.GetHeadSpacing(), fonts.GetHeadFont(), fonts.GetTextFont(), theme.getHeadColor(), theme.getTextColor(), theme.getBackgroundColor());

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void InitGame(const char* name) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(0, 0, name);

    SetTargetFPS(30);

    int monitorW = GetMonitorWidth(0);
    int monitorH = GetMonitorHeight(0);

    int winW = static_cast<int>(monitorW / 1.2f);
    int winH = static_cast<int>(monitorH / 1.2f);

    SetWindowSize(winW, winH);
    SetWindowPosition((monitorW - winW) / 2, (monitorH - winH) / 2);

    // Setup image from embedded data
    Image icon = { 0 };
    icon.data = IMAGEDATA_DATA;
    icon.width = IMAGEDATA_WIDTH;
    icon.height = IMAGEDATA_HEIGHT;
    icon.format = IMAGEDATA_FORMAT;
    icon.mipmaps = 1;

    ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    SetWindowIcon(icon);
}
