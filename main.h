#pragma once
#include <SFML/Graphics.hpp>
#include "bullet.h"
#include "player.h"
#include "zombie.h"

using namespace sf;

int createBackground(VertexArray &rVA, IntRect arena);
Zombie *createHorde(int numZombies, IntRect arena);