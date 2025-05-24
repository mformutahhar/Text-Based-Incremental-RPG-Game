#include "main-menu.h"

MainMenu::MainMenu() :
    totalOptions(static_cast<int>(magic_enum::enum_count<MainMenuState>())),
    currentOption(-1), state(MainMenuState::PLAY) {
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
        MainMenuState selectedState = static_cast<MainMenuState>(currentOption);
        // Handle the selected option
        // Example: std::cout << "Selected: " << magic_enum::enum_name(selectedState) << '\n';
    }
}

void MainMenu::Draw(const int fontSize, const int spacing, const Font& font, const Color& textColor, const Color& boxColor) const {
    const float screenWidth = static_cast<float>(GetScreenWidth());
    const float screenHeight = static_cast<float>(GetScreenHeight());
    const float centerX = screenWidth / 2.0f;
    const float centerY = screenHeight / 2.0f;

    // Header
    const char* headerText = "WELCOME TO INCREMENTAL RPG GAME";
    Vector2 headerSize = MeasureTextEx(font, headerText, static_cast<float>(fontSize), static_cast<float>(spacing));
    Vector2 headerPos = { centerX - headerSize.x / 2.0f, centerY / 5.0f - headerSize.y / 2.0f };
    DrawTextEx(font, headerText, headerPos, static_cast<float>(fontSize), static_cast<float>(spacing), textColor);

    // Start position for buttons
    float startY = headerPos.y + headerSize.y + 80.0f;

    float time = static_cast<float>(GetTime());

    for (int i = 0; i < totalOptions - 1; ++i) {
        MainMenuState state = static_cast<MainMenuState>(i);
        std::string optionText = std::string(magic_enum::enum_name(state));
        Vector2 textSize = MeasureTextEx(font, optionText.c_str(), static_cast<float>(fontSize), static_cast<float>(spacing));

        // Button dimensions
        float paddingX = 80.0f;
        float paddingY = 30.0f;
        float buttonWidth = textSize.x + paddingX;
        float buttonHeight = textSize.y + paddingY;

        Vector2 buttonPos = { centerX - buttonWidth / 2.0f, startY };
        Rectangle buttonRect = { buttonPos.x, buttonPos.y, buttonWidth, buttonHeight };

        //  Chaotic shimmer
        float chaos = sinf(time * 1.3f + i * 2.5f) * cosf(time * 1.7f + i * 1.1f);
        float pulse = 0.6f + 0.4f * chaos;

        //  Glass colors
        unsigned char glassAlpha = static_cast<unsigned char>(180 + 60 * pulse);
        Color glassFill = { boxColor.r, boxColor.g, boxColor.b, glassAlpha };

        Color glowBorder = { 255, 255, 255, static_cast<unsigned char>(50 + 90 * pulse) };
        Color glowHighlight = { 255, 255, 255, static_cast<unsigned char>(30 + 50 * pulse) };

        //  Draw Glassmorphism Layers

        // Shadow/blur layer
        DrawRectangleRounded(buttonRect, 0.35f, 16, Fade(BLACK, 0.10f));

        // Translucent button pane
        DrawRectangleRounded(buttonRect, 0.35f, 16, glassFill);

        // White glass border
        DrawRectangleRoundedLines(buttonRect, 0.35f, 16, glowBorder);

        // Inner highlight bar
        Rectangle innerHighlight = {
            buttonRect.x + 12.0f,
            buttonRect.y + 8.0f,
            buttonRect.width - 24.0f,
            6.0f
        };
        DrawRectangleRounded(innerHighlight, 0.1f, 6, glowHighlight);

        //  Center text vertically and horizontally inside the button
        Vector2 textPos = {
            buttonRect.x + (buttonRect.width - textSize.x) / 2.0f,
            buttonRect.y + (buttonRect.height - textSize.y) / 2.0f + 10
        };
        DrawTextEx(font, optionText.c_str(), textPos, static_cast<float>(fontSize), static_cast<float>(spacing), textColor);

        startY += buttonHeight + 40.0f; // button spacing
    }
}