#include "player.h"

Player::Player()
{
    m_Speed = START_SPEED;
    m_Health = START_HEALTH;
    m_MaxHealth = START_HEALTH;

    m_Texture.loadFromFile("assets/graphics/player2.png");
    m_Sprite.setTexture(m_Texture);

    m_Sprite.setOrigin(25, 25);
}

void Player::spawn(IntRect arena, Vector2f resolution, int tileSize)
{
    // Put player in center of the arena to start
    m_Position.x = arena.width / 2;
    m_Position.y = arena.height / 2;

    // Save the arena sizes
    m_Arena.left = arena.left;
    m_Arena.top = arena.top;
    m_Arena.width = arena.width;
    m_Arena.height = arena.height;

    // how many pixels are the tiles
    m_TileSize = tileSize;

    // save screen resolution for internal use
    m_Resolution.x = resolution.x;
    m_Resolution.y = resolution.y;
}

bool Player::hit(Time timeHit)
{
    if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200)
    {
        m_LastHit = timeHit;
        m_Health -= 10;
        return true;
    }

    return false;
}

Time Player::getLastHitTime()
{
    return m_LastHit;
}

FloatRect Player::getPosition()
{
    return m_Sprite.getGlobalBounds();
}

Vector2f Player::getCenter()
{
    return m_Position;
}

float Player::getRotation()
{
    return m_Sprite.getRotation();
}

Sprite Player::getSprite()
{
    return m_Sprite;
}

void Player::moveUp()
{
    m_UpPressed = true;
}

void Player::moveRight()
{
    m_RightPressed = true;
}

void Player::moveDown()
{
    m_DownPressed = true;
}

void Player::moveLeft()
{
    m_LeftPressed = true;
}

void Player::stopUp()
{
    m_UpPressed = false;
}

void Player::stopRight()
{
    m_RightPressed = false;
}

void Player::stopDown()
{
    m_DownPressed = false;
}

void Player::stopLeft()
{
    m_LeftPressed = false;
}

void Player::upgradeSpeed()
{
    m_Speed += (START_SPEED * 0.2f);
}

void Player::upgradeHealth()
{
    m_MaxHealth += (START_HEALTH * 0.2f);
}

void Player::increaseHealthLevel(int amount)
{
    m_Health += amount;

    if (m_Health > m_MaxHealth)
    {
        m_Health = m_MaxHealth;
    }
}

int Player::getHealth()
{
    return m_Health;
}

void Player::resetPlayerStats()
{
    m_Health = START_HEALTH;
    m_MaxHealth = START_HEALTH;
    m_Speed = START_SPEED;
}

void Player::update(float elapsedTime, Vector2i mousePosition)
{
    setMovement(elapsedTime);
    // std::cout << m_Position.x << " " << m_Position.y << "\n";

    float angle = (atan2(mousePosition.y - m_Resolution.y / 2, mousePosition.x - m_Resolution.x / 2) * 180) / 3.141;
    m_Sprite.setRotation(angle);
}

void Player::setMovement(float elapsedTime)
{
    if (m_UpPressed)
    {
        m_Position.y -= m_Speed * elapsedTime;
    }
    else if (m_DownPressed)
    {
        m_Position.y += m_Speed * elapsedTime;
    }

    if (m_LeftPressed)
    {
        m_Position.x -= m_Speed * elapsedTime;
    }
    else if (m_RightPressed)
    {
        m_Position.x += m_Speed * elapsedTime;
    }

    m_Sprite.setPosition(m_Position);

    if (m_Position.x > m_Arena.width - m_TileSize)
    {
        m_Position.x = m_Arena.width - m_TileSize;
    }
    if (m_Position.x < m_Arena.top + m_TileSize)
    {
        m_Position.x = m_Arena.top + m_TileSize;
    }

    if (m_Position.y < m_Arena.left + m_TileSize)
    {
        m_Position.y = m_Arena.left + m_TileSize;
    }
    if (m_Position.y > m_Arena.height - m_TileSize)
    {
        m_Position.y = m_Arena.height - m_TileSize;
    }
}