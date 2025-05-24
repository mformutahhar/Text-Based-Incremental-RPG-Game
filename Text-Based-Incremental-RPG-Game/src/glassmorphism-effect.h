#pragma once
#include <raylib.h>
#include <string>

class GlassmorphismEffect {
private:
    Shader blurShader{};
    Texture2D noiseTexture{};
    RenderTexture2D blurTarget{};

    int screenWidth{};
    int screenHeight{};

public:
    GlassmorphismEffect() = default;

    // Initialize resources, load shader & noise, setup framebuffer
    bool Init(int screenW, int screenH,
        const std::string& blurShaderPath,
        const std::string& noiseTexturePath)
    {
        screenWidth = screenW;
        screenHeight = screenH;

        blurShader = LoadShader(0, blurShaderPath.c_str());
        if (blurShader.id == 0) return false;

        noiseTexture = LoadTexture(noiseTexturePath.c_str());
        if (noiseTexture.id == 0) {
            UnloadShader(blurShader);
            return false;
        }

        blurTarget = LoadRenderTexture(screenWidth, screenHeight);
        if (blurTarget.id == 0) {
            UnloadShader(blurShader);
            UnloadTexture(noiseTexture);
            return false;
        }

        return true;
    }

    // Clean up GPU resources
    void Unload() {
        if (blurShader.id != 0) UnloadShader(blurShader);
        if (noiseTexture.id != 0) UnloadTexture(noiseTexture);
        if (blurTarget.id != 0) UnloadRenderTexture(blurTarget);
    }

    // Call this every frame BEFORE your UI drawing.
    // Pass a function to draw your game scene (without UI)
    template<typename DrawSceneFunc>
    void CaptureAndBlurBackground(DrawSceneFunc drawScene) {
        // Capture scene into framebuffer
        BeginTextureMode(blurTarget);
        ClearBackground(BLANK);
        drawScene();
        EndTextureMode();

        // Apply blur shader & draw full screen quad with blur
        BeginShaderMode(blurShader);
        float resolution[2] = { (float)screenWidth, (float)screenHeight };
        SetShaderValue(blurShader, GetShaderLocation(blurShader, "resolution"), resolution, SHADER_UNIFORM_VEC2);
        DrawTextureRec(blurTarget.texture, { 0, 0, (float)blurTarget.texture.width, -(float)blurTarget.texture.height }, { 0, 0 }, WHITE);
        EndShaderMode();
    }

    // Draw a glass button with shimmer, noise, and hover effect
    // Returns true if hovered (can be used for input)
    bool DrawGlassButton(Rectangle buttonRect, const char* text, const Font& font, int fontSize, int spacing, Color textColor, Color boxColor, Vector2 mousePos, float time) {
        bool hovered = CheckCollisionPointRec(mousePos, buttonRect);

        float chaos = sinf(time * 1.3f + buttonRect.y * 0.05f) * cosf(time * 1.7f + buttonRect.x * 0.03f);
        float pulse = 0.6f + 0.4f * chaos;
        float hoverPulse = hovered ? (0.8f + 0.6f * sinf(time * 8.0f)) : 0.0f;

        unsigned char glassAlpha = static_cast<unsigned char>(180 + 60 * pulse + 50 * hoverPulse);
        Color glassFill = { boxColor.r, boxColor.g, boxColor.b, glassAlpha };

        Color glowBorder = { 255, 255, 255, static_cast<unsigned char>(50 + 90 * pulse + 80 * hoverPulse) };
        Color glowHighlight = { 255, 255, 255, static_cast<unsigned char>(30 + 50 * pulse + 50 * hoverPulse) };

        // Shadow/blur layer
        DrawRectangleRounded(buttonRect, 0.35f, 16, Fade(BLACK, 0.10f));

        // Translucent pane
        DrawRectangleRounded(buttonRect, 0.35f, 16, glassFill);

        // Noise overlay, animated
        float noiseTileScale = 0.15f;
        Vector2 noisePos = { fmod(time * 30.0f + buttonRect.x * 0.7f, buttonRect.width * noiseTileScale) - buttonRect.width * noiseTileScale,
                             fmod(time * 20.0f + buttonRect.y * 0.5f, buttonRect.height * noiseTileScale) - buttonRect.height * noiseTileScale };

        Rectangle noiseSource = { noisePos.x / noiseTileScale, noisePos.y / noiseTileScale, (float)noiseTexture.width, (float)noiseTexture.height };
        DrawTexturePro(noiseTexture, noiseSource, buttonRect, { 0, 0 }, 0.0f, Fade(WHITE, 0.04f + 0.05f * hoverPulse));

        // Glass border glow
        DrawRectangleRoundedLines(buttonRect, 0.35f, 16, glowBorder);

        // Inner highlight bar
        Rectangle innerHighlight = { buttonRect.x + 12.0f, buttonRect.y + 8.0f, buttonRect.width - 24.0f, 6.0f };
        DrawRectangleRounded(innerHighlight, 0.1f, 6, Fade(WHITE, 0.15f + 0.1f * pulse + 0.15f * hoverPulse));

        // Inner shadow (depth)
        DrawRectangleRoundedLines(buttonRect, 0.35f, 16, Fade(BLACK, 0.06f));

        // Text centered
        Vector2 textSize = MeasureTextEx(font, text, (float)fontSize, (float)spacing);
        Vector2 textPos = {
            buttonRect.x + (buttonRect.width - textSize.x) / 2.0f,
            buttonRect.y + (buttonRect.height - textSize.y) / 2.0f
        };
        DrawTextEx(font, text, textPos, (float)fontSize, (float)spacing, textColor);

        return hovered;
    }
};


