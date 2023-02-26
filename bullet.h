#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "textureHolder.h"

using namespace sf;

class Bullet
{
private:
    Vector2f m_Position;
    RectangleShape m_Shape;
    bool m_InFlight = false;
    float m_Speed = 1000;
    float m_DistanceX;
    float m_DistanceY;

    float m_MaxX;
    float m_MinX;
    float m_MaxY;
    float m_MinY;

public:
    Bullet();
    void stop();
    bool isInFlight();
    void shoot(float startX, float startY, float targetX, float targetY);
    FloatRect getPosition();
    RectangleShape getShape();
    void update(float elapsedTime);
};