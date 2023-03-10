#include "main.h"
#include "zombie.h"

Zombie *createHorde(int numZombies, IntRect arena)
{
    Zombie *zombies = new Zombie[numZombies];

    int maxY = arena.height - 50;
    int minY = arena.top + 50;
    int minX = arena.left + 50;
    int maxX = arena.width - 50;
    for (int i = 0; i < numZombies; i++)
    {
        srand(((int)time(0)) * i);
        int side = (rand() % 4);
        float x = 0;
        float y = 0;

        switch (side)
        {
        case 0:
            // left
            x = minX;
            y = (rand() % maxY) + minY;
            break;

        case 1:
            // right
            x = maxX;
            y = (rand() % maxY) + minY;
            break;

        case 2:
            // top
            x = (rand() % maxX) + minX;
            y = minY;
            break;

        case 4:
            // bottom
            x = (rand() % maxX) + minX;
            y = maxY;
            break;
        }
        // create zombie type
        srand(int(time(0)) * i * 2);
        int type = (rand() % 3);

        zombies[i].spawn(x, y, type, i);
    }
    return zombies;
}