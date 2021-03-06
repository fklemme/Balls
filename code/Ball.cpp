#include "Ball.h"
#include "Spielfeld.h"

Ball::Ball(Spielfeld* spielfeld, int position_x, int position_y)
	: m_spielfeld(spielfeld), m_position_x(position_x), m_position_y(position_y)
{}

void Ball::update() {
	// Dumm! (TODO)
	++m_position_x;
	++m_position_y;
}

void Ball::draw() const {
	// Zeichne nur, wenn auch tatsächlich im Spielfeld, nicht auf dem Rand!
	if (m_position_x >= 0 && m_position_x < m_spielfeld->get_breite()) {
		if (m_position_y >= 0 && m_position_y < m_spielfeld->get_hoehe()) {
			m_spielfeld->Draw(m_position_x, m_position_y);
		}
	}
}