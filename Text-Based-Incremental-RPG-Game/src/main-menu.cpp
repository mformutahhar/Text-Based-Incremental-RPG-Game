#include "main-menu.h"

MainMenu::MainMenu() :
    totalOptions(static_cast<int>(magic_enum::enum_count<MainMenuState>())),
    currentOption(-1), state(MainMenuState::PLAY) {
    normalMenuButton = LoadTexture("assets/images/mainButton.png");
    hoverMenuButton  = LoadTexture("assets/images/mainButtonHovered.png");
}

void MainMenu::Update() {
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
        currentOption = (currentOption + 1) % totalOptions;
    }

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
        currentOption = (currentOption - 1 + totalOptions) % totalOptions;
    }

    if (IsKeyPressed(KEY_F11)) {
        ToggleFullscreen();
    }

    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) {
        state = static_cast<MainMenuState>(currentOption);
        switch (state) {
            case MainMenuState::PLAY:
                // StartGame(); // A function to transition to gameplay state
                break;
            case MainMenuState::HELP:
                // ShowHelpScreen(); // A function to transition to help screen state
                break;
            case MainMenuState::SETTINGS:
                // OpenSettingsMenu(); // A function to transition to settings state
                break;
            case MainMenuState::EXIT:
                SetExitKey(KEY_NULL); // Temporarily disable ESC as exit key if it's set
                CloseWindow();
                break;
            default:
                TraceLog(LOG_WARNING, "MENU: Unknown option selected!");
                break;
        }
    }
}

void StretchTextureToRectangle(Texture2D texture, Rectangle dest, Color tint = WHITE) {
    Rectangle src = { 0, 0, (float)texture.width, (float)texture.height };
    Vector2 origin = { 0, 0 };
    DrawTexturePro(texture, src, dest, origin, 0.0f, tint);
}


void MainMenu::Draw(const int fontSize, const int spacing, const Font& font1, const Font& font2,  const Color& textColor1, const Color&textColor2, const Color& backgroundColor) const {
    const float screenWidth = static_cast<float>(GetScreenWidth());
    const float screenHeight = static_cast<float>(GetScreenHeight());
    const float centerX = screenWidth / 2.0f;
    const float centerY = screenHeight / 2.0f;

    // Header
    const char* headerText = "WELCOME TO INCREMENTAL RPG GAME";
    Vector2 headerSize = MeasureTextEx(font1, headerText, static_cast<float>(fontSize), static_cast<float>(spacing));
    Vector2 headerPos = { centerX - headerSize.x / 2.0f, centerY / 5.0f - headerSize.y / 2.0f };
    DrawTextEx(font1, headerText, headerPos, static_cast<float>(fontSize), static_cast<float>(spacing), textColor1);

    // Start position for buttons
    float startY = headerPos.y + headerSize.y + 80.0f;

    float time = static_cast<float>(GetTime());

    Vector2 mouse = GetMousePosition();
    for (int i = 0; i < totalOptions - 1; ++i) {
        MainMenuState state = static_cast<MainMenuState>(i);
        std::string optionText = std::string(magic_enum::enum_name(state));
        Vector2 textSize = MeasureTextEx(font2, optionText.c_str(), (float)fontSize, (float)spacing);

        float paddingX = 120.0f;  // bigger for better texture visibility
        float paddingY = 60.0f;
        float buttonWidth = textSize.x + paddingX;
        float buttonHeight = textSize.y + paddingY;

        Vector2 buttonPos = { centerX - buttonWidth / 2.0f, startY };
        Rectangle buttonRect = { buttonPos.x, buttonPos.y, buttonWidth, buttonHeight };

        bool isHovered = CheckCollisionPointRec(mouse, buttonRect);

        float chaos = sinf(time * 1.3f + i * 2.5f) * cosf(time * 1.7f + i * 1.1f);
        chaos *= 0.2f;
        float pulse = 0.7f + chaos + (isHovered ? 0.15f : 0.0f);

        DrawRectangleRounded(buttonRect, 0.35f, 16, (Color {0, 0, 0, 0}));
        StretchTextureToRectangle((isHovered ? hoverMenuButton : normalMenuButton), buttonRect, Fade(WHITE, pulse));

        Vector2 textPos = {
            buttonRect.x + (buttonRect.width - textSize.x) / 2.0f,
            buttonRect.y + (buttonRect.height - textSize.y) / 2.0f - 5
        };
        DrawTextEx(font2, optionText.c_str(), textPos, (float)fontSize, (float)spacing, textColor2);

        startY += buttonHeight + 40.0f;
    }
}

MainMenu::~MainMenu() {
    UnloadTexture(normalMenuButton);
    UnloadTexture(hoverMenuButton);
}