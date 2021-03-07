#include "Ball.h"

#include "Spielfeld.h"

Ball::Ball(Spielfeld* spielfeld, int position_x, int position_y, int richtung_x, int richtung_y, olc::Pixel farbe)
    : m_spielfeld(spielfeld),
      m_position_x(position_x),
      m_position_y(position_y),
      m_richtung_x(richtung_x),
      m_richtung_y(richtung_y),
      m_farbe(farbe) {}

void Ball::update() {
    // Wenn m_richtung_x in die linke Wand führen würde, gehen stattdessen nach rechts.
    if (m_position_x + m_richtung_x < 0) {
        m_richtung_x = -m_richtung_x;  // Richtungswechsel (nach rechts)
    } else if (m_position_x + m_richtung_x >= m_spielfeld->get_breite()) {
        m_richtung_x = -m_richtung_x;  // Richtungswechsel (nach links)
    }
    m_position_x += m_richtung_x;

    // Wenn m_richtung_y in die obere Wand führen würde, gehen stattdessen nach unten.
    if (m_position_y + m_richtung_y < 0) {
        m_richtung_y = -m_richtung_y;  // Richtungswechsel (nach unten)
    } else if (m_position_y + m_richtung_y >= m_spielfeld->get_hoehe()) {
        m_richtung_y = -m_richtung_y;  // Richtungswechsel (nach oben)
    }
    m_position_y += m_richtung_y;
}

void Ball::draw() const { m_spielfeld->Draw(m_position_x, m_position_y, m_farbe); }