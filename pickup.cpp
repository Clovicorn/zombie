#include "pickup.h"

Pickup::Pickup(int type)
{
    m_Type = type;
    if (m_Type == 1)
    {
        m_Sprite = Sprite(TextureHolder::getTexture("assets/graphics/health_pickup.png"));
        m_Value = HEALTH_START_VALUE;
    }
    else
    {
        m_Sprite = Sprite(TextureHolder::getTexture("assets/graphics/ammo_pickup.png"));
        m_Value = AMMO_START_VALUE;
    }
    m_Sprite.setOrigin(25, 25);
    m_SecondsToLive = START_SECONDS_TO_LIVE;
    m_SecondsToWait = START_WAIT_TIME;
}

void Pickup::setArena(IntRect arena)
{
    m_Arena.left = arena.left + 50;
    m_Arena.top = arena.top + 50;
    m_Arena.width = arena.width - 50;
    m_Arena.height = arena.height - 50;

    spawn();
}

void Pickup::spawn()
{
    srand((int)time(0) / m_Type);
    int x = (rand() % m_Arena.width);
    srand((int)time(0) * m_Type);
    int y = (rand() % m_Arena.height);

    m_SecondsSinceSpawn = 0;
    m_Spawned = true;
    m_Sprite.setPosition(x, y);
}

FloatRect Pickup::getPosition()
{
    return m_Sprite.getGlobalBounds();
}

Sprite Pickup::getSprite()
{
    return m_Sprite;
}

void Pickup::update(float elapsedTime)
{
    if (m_Spawned)
    {
        m_SecondsSinceSpawn += elapsedTime;
    }
    else
    {
        m_SecondsToDespawn += elapsedTime;
    }
    if (m_SecondsSinceSpawn > m_SecondsToLive && m_Spawned)
    {
    }
    if (m_SecondsSinceSpawn > m_SecondsToWait && !m_Spawned)
    {
        spawn();
    }
}

bool Pickup::isSpawned()
{
    return m_Spawned;
}

int Pickup::gotIt()
{
    m_Spawned = false;
    m_SecondsToDespawn = 0;
    return m_Value;
}

void Pickup::upgrade()
{
    if (m_Type == 1)
    {
        m_Value += (HEALTH_START_VALUE * 0.5);
    }
    else
    {
        m_Value += (AMMO_START_VALUE * 0.5);
    }

    m_SecondsToLive += (START_SECONDS_TO_LIVE / 10);
    m_SecondsToWait -= (START_WAIT_TIME / 10);
}