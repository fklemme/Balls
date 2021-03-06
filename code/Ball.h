#pragma once

// Forward declaration
class Spielfeld;

class Ball {
public:
	Ball(Spielfeld* spielfeld, int position_x, int position_y);

	void update();

	void draw() const;

private:
	Spielfeld* m_spielfeld;
	int m_position_x;
	int m_position_y;
};