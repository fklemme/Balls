#include "Ball.h"

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

    auto& hindernisse = m_spielfeld->get_hindernisse();

    // Hinderniss "x" check und update
    Position x_check = m_position;
    x_check.x += m_richtung_x;

    bool collision = false;
    for (const Position& p : hindernisse) {
        if (p.x == x_check.x && p.y == x_check.y) {
            collision = true;
            break;
        }
    }

    if (collision) {
        m_richtung_x = -m_richtung_x;  // Richtung umkehren
    }
    m_position.x += m_richtung_x;  // Position updaten

    // Hinderniss "y" check und update
    Position y_check = m_position;
    y_check.y += m_richtung_y;

    collision = false;
    for (const Position& p : hindernisse) {
        if (p.x == y_check.x && p.y == y_check.y) {
            collision = true;
            break;
        }
    }

    if (collision) {
        m_richtung_y = -m_richtung_y;  // Richtung umkehren
    }
    m_position.y += m_richtung_y;  // Position updaten
}

void Ball::draw() const {
    // Aktuelle Position zeichnen
    m_spielfeld->Draw(m_position.x, m_position.y, m_farbe);

    // "Spur" zeichnen
    auto farbe = m_farbe;
    for (const Position& p : m_spur) {
        farbe *= 0.9f;  // reduziere auf 90%
        m_spielfeld->Draw(p.x, p.y, farbe);
    }
}