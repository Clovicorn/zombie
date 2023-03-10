#include "zombie.h"

using namespace std;

const int BLOATER = 0;
const int CHASER = 1;
const int CRAWLER = 2;

bool Zombie::hit()
{
    m_Health--;

    if (m_Health < 0)
    {
        m_Alive = false;
        m_Sprite.setTexture(TextureHolder::getTexture("assets/graphics/blood.png"));

        return true;
    }

    return false;
}

bool Zombie::isAlive()
{
    return m_Alive;
}

void Zombie::spawn(float startX, float startY, int type, int seed)
{
    switch (type)
    {
    case BLOATER:
        m_Sprite = Sprite(TextureHolder::getTexture("assets/graphics/bloater.png"));
        m_Speed = BLOATER_SPEED;
        m_Health = BLOATER_HEALTH;
        break;

    case CHASER:
        m_Sprite = Sprite(TextureHolder::getTexture("assets/graphics/chaser.png"));
        m_Speed = CHASER_SPEED;
        m_Health = CHASER_HEALTH;
        break;

    case CRAWLER:
        m_Sprite = Sprite(TextureHolder::getTexture("assets/graphics/crawler.png"));
        m_Speed = CRAWLER_SPEED;
        m_Health = CRAWLER_HEALTH;
        break;
    }

    srand(int(time(0)) * seed);
    float modifier = (rand() % MAX_VARRIANCE) + OFFSET;
    modifier /= 100;
    m_Speed *= modifier;

    m_Position.x = startX;
    m_Position.y = startY;

    m_Sprite.setOrigin(25, 25);
    m_Sprite.setPosition(m_Position);
    m_Alive = true;
}

FloatRect Zombie::getPosition()
{
    return m_Sprite.getGlobalBounds();
}

Sprite Zombie::getSprite()
{
    return m_Sprite;
}

void Zombie::update(float elapsedTime, Vector2f playerLocation)
{
    float playerX = playerLocation.x;
    float playerY = playerLocation.y;

    if (playerX > m_Position.x)
    {
        m_Position.x += (m_Speed * elapsedTime);
    }
    else
    {
        m_Position.x -= (m_Speed * elapsedTime);
    }

    if (playerY > m_Position.y)
    {
        m_Position.y += (m_Speed * elapsedTime);
    }
    else
    {
        m_Position.y -= (m_Speed * elapsedTime);
    }

    m_Sprite.setPosition(m_Position);

    float angle = (atan2(playerY - m_Position.y, playerX - m_Position.x) * 180) / 3.141;
    m_Sprite.setRotation(angle);
}