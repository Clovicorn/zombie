#pragma once
#include <SFML/Graphics.hpp>
#include <tuple>
#include "bullet.h"
#include "player.h"
#include "zombie.h"

using namespace sf;

int createBackground(VertexArray &rVA, IntRect arena);
Zombie *createHorde(int numZombies, IntRect arena);
std::tuple<int, int> reload(int spareBullets, int bulletsInClip, int clipSize);