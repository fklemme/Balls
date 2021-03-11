#define OLC_PGE_APPLICATION
#include "Spielfeld.h"

#include <stdlib.h>  // für rand()

Spielfeld::Spielfeld(int breite, int hoehe) : m_breite(breite), m_hoehe(hoehe) {
    sAppName = "Balls";
    Construct(breite + 2, hoehe + 2, 10, 10);
}

int Spielfeld::get_breite() const { return m_breite; }

int Spielfeld::get_hoehe() const { return m_hoehe; }

const std::vector<Position>& Spielfeld::get_hindernisse() const { return m_hindernisse; }

bool Spielfeld::check_kollision(const Position& p) const {
    for (const Position& h : m_hindernisse) {
        if (h.x == p.x && h.y == p.y) {
            return true;  // Kollision gefunden
        }
    }
    return false;  // keine Kollision gefunden
}

bool Spielfeld::Draw(int32_t x, int32_t y, olc::Pixel p) { return olc::PixelGameEngine::Draw(x + 1, y + 1, p); }

bool Spielfeld::OnUserCreate() {
    // Rahmen als Hindernis anlegen
    for (int x = -1; x <= m_breite; ++x) {
        m_hindernisse.emplace_back(x, -1);       // oben
        m_hindernisse.emplace_back(x, m_hoehe);  // unten
    }
    for (int y = -1; y <= m_hoehe; ++y) {
        m_hindernisse.emplace_back(-1, y);        // links
        m_hindernisse.emplace_back(m_breite, y);  // rechts
    }

    // Hindernisse anlegen
    for (int i = 10; i <= 20; ++i) {
        m_hindernisse.emplace_back(i, 10);  // von (10, 10) nach (20, 10)
        m_hindernisse.emplace_back(10, i);  // von (10, 10) nach (10, 20)
    }

    // Balls anlegen
    for (int i = 0; i < m_startballs; ++i) {
        int position_x = rand() % m_breite;
        int position_y = rand() % m_hoehe;

        int richtung_x = (rand() % 3) - 1;  // Zahl zwischen -1 und 1.
        int richtung_y = (rand() % 3) - 1;  // Zahl zwischen -1 und 1.
        while (richtung_x == 0 && richtung_y == 0) {
            richtung_x = (rand() % 3) - 1;  // Zahl zwischen -1 und 1.
            richtung_y = (rand() % 3) - 1;  // Zahl zwischen -1 und 1.
        }

        olc::Pixel farbe = olc::Pixel(rand() % 256, rand() % 256, rand() % 256);

        Ball b(this, position_x, position_y, richtung_x, richtung_y, farbe);
        m_balls.push_back(b);
    }

    // Debug Ball
    // m_balls.emplace_back(this, 26, 15, -1, -1, olc::RED);

    return true;
}

bool Spielfeld::OnUserUpdate(float elapsed_seconds) {
    m_elapsed_seconds += elapsed_seconds;

    // Bildschirm leeren
    Clear(olc::BLACK);

    // Hindernisse zeichnen
    for (const Position& p : m_hindernisse) {
        Draw(p.x, p.y, olc::YELLOW);
    }

    const float update_delay = 0.1f;
    if (m_elapsed_seconds >= update_delay) {
        // Balls updaten
        for (Ball& b : m_balls) {
            b.update();
        }
        m_elapsed_seconds -= update_delay;
    }

    // Balls zeichnen
    for (Ball& b : m_balls) {
        b.draw();
    }

    return true;
}