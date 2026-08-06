#pragma once

#include "Renderer.h"
#include "game/HangmanGame.h"
#include <cmath>

class HangmanRenderer {
public:
    explicit HangmanRenderer(float centerX, float baseY)
        : m_centerX(centerX), m_baseY(baseY), m_shakeTimer(0.0f), m_shakeIntensity(0.0f) {}

    void startShake(float intensity = 6.0f) {
        m_shakeTimer = 0.35f;
        m_shakeIntensity = intensity;
    }

    void update(float dt) {
        if (m_shakeTimer > 0.0f) {
            m_shakeTimer -= dt;
            if (m_shakeTimer < 0.0f) m_shakeTimer = 0.0f;
        }
    }

    void draw(const Renderer& renderer, int wrongGuesses) const {
        SDL_Color gallowsColor{140, 160, 200, 255};
        SDL_Color personColor{210, 225, 255, 255};
        SDL_Color glowColor{100, 140, 220, 120};

        float shakeX = 0.0f;
        float shakeY = 0.0f;
        if (m_shakeTimer > 0.0f) {
            shakeX = std::sin(m_shakeTimer * 55.0f) * m_shakeIntensity;
            shakeY = std::cos(m_shakeTimer * 45.0f) * m_shakeIntensity * 0.6f;
        }

        drawGallows(renderer, gallowsColor, glowColor, shakeX, shakeY);
        drawPerson(renderer, personColor, glowColor, wrongGuesses, shakeX, shakeY);
    }

private:
    void drawGallows(const Renderer& renderer, SDL_Color color, SDL_Color glowColor, float shakeX, float shakeY) const {
        float baseY = m_baseY + shakeY;
        float x = m_centerX + shakeX;
        float topY = baseY - 320.0f;
        float ropeX = x + 90.0f;

        renderer.drawLine(x - 70.0f, baseY, x + 70.0f, baseY, glowColor);
        renderer.drawLine(x, baseY, x, topY, color);
        renderer.drawLine(x, topY, ropeX, topY, color);
        renderer.drawLine(ropeX, topY, ropeX, topY + 35.0f, color);
    }

    void drawPerson(const Renderer& renderer, SDL_Color color, SDL_Color glowColor, int wrongGuesses, float shakeX, float shakeY) const {
        float ropeX = m_centerX + 90.0f + shakeX;
        float headY = m_baseY - 320.0f + 35.0f + shakeY;
        float headRadius = 28.0f;
        float bodyTop = headY + headRadius * 2;
        float bodyBottom = bodyTop + 90.0f;

        if (wrongGuesses >= 4) {
            renderer.drawCircle(ropeX, headY + headRadius, headRadius + 4.0f, glowColor);
            renderer.drawCircle(ropeX, headY + headRadius, headRadius, color);
        }
        if (wrongGuesses >= 5) {
            renderer.drawLine(ropeX, bodyTop, ropeX, bodyBottom, color);
        }
        if (wrongGuesses >= 6) {
            float armY = bodyTop + 45.0f;
            renderer.drawLine(ropeX, armY, ropeX - 40.0f, armY + 35.0f, color);
            renderer.drawLine(ropeX, armY, ropeX + 40.0f, armY + 35.0f, color);
            renderer.drawLine(ropeX, bodyBottom, ropeX - 35.0f, bodyBottom + 55.0f, color);
            renderer.drawLine(ropeX, bodyBottom, ropeX + 35.0f, bodyBottom + 55.0f, color);
        }
    }

    float m_centerX{0.0f};
    float m_baseY{0.0f};
    float m_shakeTimer{0.0f};
    float m_shakeIntensity{0.0f};
};
