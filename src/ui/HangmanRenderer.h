#pragma once

#include "Renderer.h"
#include "game/HangmanGame.h"
#include <cmath>

class HangmanRenderer {
public:
    explicit HangmanRenderer(float centerX, float baseY)
        : m_centerX(centerX), m_baseY(baseY), m_shakeTimer(0.0f), m_shakeIntensity(0.0f) {}

    void startShake(float intensity = 5.0f) {
        m_shakeTimer = 0.3f;
        m_shakeIntensity = intensity;
    }

    void update(float dt) {
        if (m_shakeTimer > 0.0f) {
            m_shakeTimer -= dt;
            if (m_shakeTimer < 0.0f) m_shakeTimer = 0.0f;
        }
    }

    void draw(const Renderer& renderer, int wrongGuesses) const {
        SDL_Color color{200, 200, 200, 255};

        float shakeX = 0.0f;
        float shakeY = 0.0f;
        if (m_shakeTimer > 0.0f) {
            shakeX = std::sin(m_shakeTimer * 50.0f) * m_shakeIntensity;
            shakeY = std::cos(m_shakeTimer * 40.0f) * m_shakeIntensity * 0.5f;
        }

        drawGallows(renderer, color, shakeX, shakeY);
        drawPerson(renderer, color, wrongGuesses, shakeX, shakeY);
    }

private:
    void drawGallows(const Renderer& renderer, SDL_Color color, float shakeX, float shakeY) const {
        float baseY = m_baseY + shakeY;
        float x = m_centerX + shakeX;
        float topY = baseY - 300.0f;
        float ropeX = x + 80.0f;

        renderer.drawLine(x - 60.0f, baseY, x + 60.0f, baseY, color);
        renderer.drawLine(x, baseY, x, topY, color);
        renderer.drawLine(x, topY, ropeX, topY, color);
        renderer.drawLine(ropeX, topY, ropeX, topY + 30.0f, color);
    }

    void drawPerson(const Renderer& renderer, SDL_Color color, int wrongGuesses, float shakeX, float shakeY) const {
        float ropeX = m_centerX + 80.0f + shakeX;
        float headY = m_baseY - 300.0f + 30.0f + shakeY;
        float headRadius = 25.0f;
        float bodyTop = headY + headRadius * 2;
        float bodyBottom = bodyTop + 80.0f;

        if (wrongGuesses >= 4) {
            renderer.drawCircle(ropeX, headY + headRadius, headRadius, color);
        }
        if (wrongGuesses >= 5) {
            renderer.drawLine(ropeX, bodyTop, ropeX, bodyBottom, color);
        }
        if (wrongGuesses >= 6) {
            float armY = bodyTop + 40.0f;
            renderer.drawLine(ropeX, armY, ropeX - 35.0f, armY + 30.0f, color);
            renderer.drawLine(ropeX, armY, ropeX + 35.0f, armY + 30.0f, color);
            renderer.drawLine(ropeX, bodyBottom, ropeX - 30.0f, bodyBottom + 50.0f, color);
            renderer.drawLine(ropeX, bodyBottom, ropeX + 30.0f, bodyBottom + 50.0f, color);
        }
    }

    float m_centerX{0.0f};
    float m_baseY{0.0f};
    float m_shakeTimer{0.0f};
    float m_shakeIntensity{0.0f};
};
