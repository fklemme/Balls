#define OLC_PGE_APPLICATION
#include "Spielfeld.h"

#include <stdlib.h>  // für rand()

Spielfeld::Spielfeld(int breite, int hoehe) : m_breite(breite), m_hoehe(hoehe) {
    sAppName = "Balls";
    Construct(breite + 2, hoehe + 2, 10, 10);
}

int Spielfeld::get_breite() const { return m_breite; }
int Spielfeld::get_hoehe() const { return m_hoehe; }

bool Spielfeld::Draw(int32_t x, int32_t y, olc::Pixel p) { return olc::PixelGameEngine::Draw(x + 1, y + 1, p); }

// Called once at the start, so create things here
bool Spielfeld::OnUserCreate() {
    // Balls anlegen
    for (int i = 0; i < 50; ++i) {
        Ball b(this, rand() % m_breite, rand() % m_hoehe);
        m_balls.push_back(b);
    }

    return true;
}

// Called once per frame, draws pixels
bool Spielfeld::OnUserUpdate(float elapsed_seconds) {
    m_elapsed_seconds += elapsed_seconds;

    // Bildschirm leeren
    Clear(olc::BLACK);

    // Rahmen zeichnen
    // Obere Linie
    for (int i = -1; i <= m_breite; ++i) {
        Draw(i, -1, olc::YELLOW);
    }
    // Untere Linie
    for (int i = -1; i <= m_breite; ++i) {
        Draw(i, m_hoehe, olc::YELLOW);
    }
    // Linke Linie
    for (int i = -1; i <= m_hoehe; ++i) {
        Draw(-1, i, olc::YELLOW);
    }
    // Rechte Linie
    for (int i = -1; i <= m_hoehe; ++i) {
        Draw(m_breite, i, olc::YELLOW);
    }

    if (m_elapsed_seconds >= 1.0f) {
        // Balls updaten
        for (Ball& b : m_balls) {
            b.update();
        }
        m_elapsed_seconds -= 1.0f;
    }

    // Balls zeichnen
    for (Ball& b : m_balls) {
        b.draw();
    }

    return true;
}