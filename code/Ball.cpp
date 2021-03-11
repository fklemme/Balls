#include "Ball.h"

#include <algorithm>
#include <vector>

#include "Spielfeld.h"

Ball::Ball(Spielfeld* spielfeld, int position_x, int position_y, int richtung_x, int richtung_y, olc::Pixel farbe)
    : m_spielfeld(spielfeld),
      m_position(position_x, position_y),
      m_richtung_x(richtung_x),
      m_richtung_y(richtung_y),
      m_farbe(farbe) {}

void Ball::update() {
    // Aktuelle Position in "Spur" speichern
    m_spur.push_front(m_position);
    if (m_spur.size() > m_spurlaenge) {
        m_spur.pop_back();
    }

    // Richtung checken und ggf. korregieren
    if (m_richtung_x != 0 && m_richtung_y != 0) {
        // Diagonale Bewegung
        Position d(m_position.x + m_richtung_x, m_position.y + m_richtung_y);
        if (m_spielfeld->check_kollision(d)) {
            // Nur in diesem Fall Richtungskorrektur nötig
            Position x(m_position.x + m_richtung_x, m_position.y);
            const bool x_kollision = m_spielfeld->check_kollision(x);
            Position y(m_position.x, m_position.y + m_richtung_y);
            const bool y_kollision = m_spielfeld->check_kollision(y);

            if (x_kollision && !y_kollision) {
                m_richtung_x = -m_richtung_x;  // x-Richtung umkehren
            } else if (!x_kollision && y_kollision) {
                m_richtung_y = -m_richtung_y;  // y-Richtung umkehren
            } else {
                m_richtung_x = -m_richtung_x;  // x-Richtung umkehren
                m_richtung_y = -m_richtung_y;  // y-Richtung umkehren
            }
        }
    } else {
        // Horizontale/Vertikale Bewegung
        if (m_richtung_x != 0) {
            // Rechts/Links Bewegung
            Position x(m_position.x + m_richtung_x, m_position.y);
            if (m_spielfeld->check_kollision(x)) {
                m_richtung_x = -m_richtung_x;  // x-Richtung umkehren
            }
        } else {
            // Oben/Unten Bewegung
            Position y(m_position.x, m_position.y + m_richtung_y);
            if (m_spielfeld->check_kollision(y)) {
                m_richtung_y = -m_richtung_y;  // y-Richtung umkehren
            }
        }
    }

    // Position updaten
    m_position.x += m_richtung_x;
    m_position.y += m_richtung_y;
}

void Ball::draw() const {
    std::vector<std::pair<Position, olc::Pixel>> schlange;

    // Aktuelle Position in Schlange einfügen
    schlange.emplace_back(m_position, m_farbe);

    // "Spur" in Schlange einfügen
    auto farbe = m_farbe;
    for (const Position& p : m_spur) {
        farbe *= 0.9f;  // reduziere auf 90%
        schlange.emplace_back(p, farbe);
    }

    // "Schlange" rückwärts(!) zeichnen
    // Damit übermalt der "Schwanz" nicht vordere Teile der "Schlange"
    std::reverse(schlange.begin(), schlange.end());
    for (auto& [position, farbe] : schlange) {
        m_spielfeld->Draw(position.x, position.y, farbe);
    }
}