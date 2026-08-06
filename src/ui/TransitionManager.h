#pragma once

#include <SDL3/SDL.h>
#include <algorithm>

class TransitionManager {
public:
    TransitionManager() = default;

    void startFadeOut(float duration = 0.3f) {
        m_duration = duration;
        m_timer = duration;
        m_state = FadeOut;
    }

    void startFadeIn(float duration = 0.3f) {
        m_duration = duration;
        m_timer = duration;
        m_state = FadeIn;
    }

    void update(float dt) {
        if (m_state == None) return;

        m_timer -= dt;
        if (m_timer <= 0.0f) {
            m_timer = 0.0f;
            if (m_state == FadeOut) {
                m_state = FadeIn;
                m_timer = m_duration;
            } else if (m_state == FadeIn) {
                m_state = None;
                m_alpha = 0.0f;
            }
        }

        if (m_state == FadeOut) {
            m_alpha = 1.0f - (m_timer / m_duration);
        } else if (m_state == FadeIn) {
            m_alpha = m_timer / m_duration;
        }
    }

    float getAlpha() const { return std::clamp(m_alpha, 0.0f, 1.0f); }
    bool isActive() const { return m_state != None; }

private:
    enum State { None, FadeOut, FadeIn } m_state{None};
    float m_duration{0.3f};
    float m_timer{0.0f};
    float m_alpha{0.0f};
};
