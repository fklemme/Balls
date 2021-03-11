#pragma once

#include <vector>

#include "Ball.h"
#include "Position.h"
#include "olcPixelGameEngine.h"

class Spielfeld : public olc::PixelGameEngine {
  public:
    Spielfeld(int breite, int hoehe);

    // Liefert die Breite des Spielfeldes innerhalb des Rahmens zur�ck.
    int get_breite() const;

    // Liefert die H�he des Spielfeldes innerhalb des Rahmens zur�ck.
    int get_hoehe() const;

    // Liefert eine Liste aller Hindernisse zur�ck.
    const std::vector<Position>& get_hindernisse() const;

    // Liefert "true" zur�ck, wenn an Position "p" ein Hindernis steht.
    bool check_kollision(const Position& p) const;

    // �berschreibt die Draw Funktion der PixelGameEngine. Alle Pixel werden effektiv +(1,1) gezeichnet, sodass sie
    // innerhalb des Spielfeldrahmens sind. Die R�nder sind somit bei x=-1/breite, bzw. y=-1/hoehe.
    bool Draw(int32_t x, int32_t y, olc::Pixel p = olc::WHITE) override;

    // Wird einmal am Anfang des Programms ausgef�hrt. (PixelGameEngine)
    bool OnUserCreate() override;

    // Wird f�r jedes Frame des Programms ausgef�hrt. (PixelGameEngine)
    bool OnUserUpdate(float elapsed_seconds) override;

  private:
    int m_breite;
    int m_hoehe;
    std::vector<Ball> m_balls;
    int m_startballs = 10;
    float m_elapsed_seconds = 0.0f;
    std::vector<Position> m_hindernisse;
};