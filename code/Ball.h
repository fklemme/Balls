#pragma once

#include "olcPixelGameEngine.h"

// Forward declaration
class Spielfeld;

class Ball {
  public:
    Ball(Spielfeld* spielfeld, int position_x, int position_y, int richtung_x, int richtung_y, olc::Pixel farbe);

    // Bewegt den Ball eine Position weiter.
    void update();

    // Zeichnet den Ball auf dem Spielfeld.
    void draw() const;

  private:
    Spielfeld* m_spielfeld;
    int m_position_x;
    int m_position_y;
    int m_richtung_x;
    int m_richtung_y;
    olc::Pixel m_farbe;
};