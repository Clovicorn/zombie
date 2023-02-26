#include "bullet.h"

Bullet::Bullet()
{
    m_Shape.setSize(Vector2f(11, 7));
    m_Shape.setTexture(&TextureHolder::getTexture("assets/graphics/bullet.png"), true);
    m_Shape.setOrigin(Vector2f(5.5, 3.5));
}

void Bullet::stop()
{
    m_InFlight = false;
}

bool Bullet::isInFlight()
{
    return m_InFlight;
}

void Bullet::shoot(float startX, float startY, float targetX, float targetY)
{
    m_InFlight = true;
    m_Position.x = startX;
    m_Position.y = startY;

    float gradient = (startX - targetX) / (startY - targetY);
    if (gradient < 0)
    {
        gradient *= -1;
    }

    float ratioXY = m_Speed / (1 + gradient);
    m_DistanceY = ratioXY;
    m_DistanceX = ratioXY * gradient;

    if (targetX < startX)
    {
        m_DistanceX *= -1;
    }

    if (targetY < startY)
    {
        m_DistanceY *= -1;
    }

    float range = 1000;
    m_MinX = startX - range;
    m_MaxX = startX + range;
    m_MinY = startY - range;
    m_MaxY = startY + range;

    m_Shape.setPosition(m_Position);

    float angle = (atan2(startY - targetY, startX - targetX) * 180) / 3.141;
    m_Shape.setRotation(angle);
}

FloatRect Bullet::getPosition()
{
    return m_Shape.getGlobalBounds();
}

RectangleShape Bullet::getShape()
{
    return m_Shape;
}

void Bullet::update(float elapsedTime)
{
    m_Position.x += m_DistanceX * elapsedTime;
    m_Position.y += m_DistanceY * elapsedTime;

    m_Shape.setPosition(m_Position);

    if (m_Position.x < m_MinX || m_Position.x > m_MaxX || m_Position.y < m_MinY || m_Position.y > m_MaxY)
    {
        m_InFlight = false;
    }
}