#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "textureHolder.h"

using namespace sf;

class Player
{
private:
    const float START_SPEED = 200;
    const float START_HEALTH = 100;

    Vector2f m_Position;
    float m_Speed;

    Sprite m_Sprite;
    Texture m_Texture;

    Vector2f m_Resolution;
    IntRect m_Arena;
    int m_TileSize;

    bool m_UpPressed;
    bool m_RightPressed;
    bool m_DownPressed;
    bool m_LeftPressed;

    int m_Health;
    int m_MaxHealth;

    Time m_LastHit;

    void setMovement(float elapsedTime);

public:
    Player();

    void spawn(IntRect arena, Vector2f resolution, int tileSize);

    bool hit(Time timeHit);

    Time getLastHitTime();
    FloatRect getPosition();
    Vector2f getCenter();
    float getRotation();
    Sprite getSprite();

    void moveUp();
    void moveRight();
    void moveDown();
    void moveLeft();

    void stopUp();
    void stopRight();
    void stopDown();
    void stopLeft();

    void update(float elapsedTime, Vector2f mousePosition);
    void upgradeSpeed();
    void upgradeHealth();
    void increaseHealthLevel(int amount);

    int getHealth();
    void resetPlayerStats();
};