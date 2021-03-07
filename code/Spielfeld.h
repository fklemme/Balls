#pragma once

#include <vector>

#include "Ball.h"
#include "olcPixelGameEngine.h"

class Spielfeld : public olc::PixelGameEngine {
  public:
    Spielfeld(int breite, int hoehe);

    int get_breite() const;
    int get_hoehe() const;

    bool Draw(int32_t x, int32_t y, olc::Pixel p = olc::WHITE) override;

    // Called once at the start, so create things here
    bool OnUserCreate() override;

    // Called once per frame, draws pixels
    bool OnUserUpdate(float fElapsedTime) override;

  private:
    int m_breite;
    int m_hoehe;
    std::vector<Ball> m_balls;
    float m_elapsed_seconds = 0.0f;
};