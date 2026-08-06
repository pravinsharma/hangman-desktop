#pragma once

#include "Renderer.h"
#include <vector>
#include <random>
#include <cmath>

struct Particle {
    float x, y;
    float vx, vy;
    float life;
    float maxLife;
    float size;
    SDL_Color color;
};

class ConfettiRenderer {
public:
    ConfettiRenderer() = default;

    void spawn(float x, float y, int count = 80) {
        m_particles.clear();
        m_particles.reserve(static_cast<size_t>(count));
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_real_distribution<float> angleDist(0.0f, 2.0f * 3.14159265f);
        std::uniform_real_distribution<float> speedDist(100.0f, 300.0f);
        std::uniform_real_distribution<float> lifeDist(1.0f, 2.5f);
        std::uniform_int_distribution<int> colorDist(0, 4);

        SDL_Color colors[] = {
            {255, 100, 100, 255},
            {100, 255, 100, 255},
            {100, 100, 255, 255},
            {255, 255, 100, 255},
            {255, 100, 255, 255}
        };

        for (int i = 0; i < count; ++i) {
            float angle = angleDist(rng);
            float speed = speedDist(rng);
            Particle p;
            p.x = x;
            p.y = y;
            p.vx = std::cos(angle) * speed;
            p.vy = std::sin(angle) * speed - 200.0f;
            p.life = lifeDist(rng);
            p.maxLife = p.life;
            p.size = 4.0f + (rng() % 4);
            p.color = colors[colorDist(rng)];
            m_particles.push_back(p);
        }
    }

    void update(float dt) {
        for (auto& p : m_particles) {
            p.vy += 400.0f * dt;
            p.x += p.vx * dt;
            p.y += p.vy * dt;
            p.life -= dt;
        }
        std::erase_if(m_particles, [](const Particle& p) { return p.life <= 0.0f; });
    }

    void draw(const Renderer& renderer) const {
        for (const auto& p : m_particles) {
            float alpha = p.life / p.maxLife;
            SDL_Color color = p.color;
            color.a = static_cast<Uint8>(255 * alpha);
            renderer.drawRect(p.x - p.size / 2.0f, p.y - p.size / 2.0f, p.size, p.size, color);
        }
    }

    bool isEmpty() const { return m_particles.empty(); }

private:
    std::vector<Particle> m_particles;
};
