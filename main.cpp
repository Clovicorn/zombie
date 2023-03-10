#include "main.h"

int main(void)
{
    enum class State
    {
        PAUSED,
        LEVEL_UP,
        GAME_OVER,
        PLAYING
    };

    int score = 0;
    int highScore = 0;

    TextureHolder holder;
    Vector2f resolution(1920, 1080);
    State state = State::GAME_OVER;

    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Zombie Killer!", Style::Fullscreen);

    window.setMouseCursorVisible(true);
    Sprite spriteCrosshair = Sprite(TextureHolder::getTexture("assets/graphics/crosshair1.png"));
    spriteCrosshair.setOrigin(25, 25);
    View mainView(FloatRect(0, 0, 1920, 1080));

    Player player;
    Pickup healthPickup(1);
    Pickup ammoPickup(2);

    Clock clock;
    Time gameTimeTotal;

    Vector2f mouseWorldPosition;
    Vector2i mouseScreenPosition;

    IntRect arena;
    VertexArray background;
    Texture texBackground = TextureHolder::getTexture("assets/graphics/background_sheet.png");

    int numZombies;
    int numZombiesAlive;
    Zombie *zombies = nullptr;

    Bullet bullets[100];
    int currentBullet = 0;
    int bulletSpares = 24;
    int bulletsInClip = 6;
    int clipSize = 6;
    float fireRate = 1;
    Time lastPressed;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {

            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape)
                {
                    window.close();
                }
                // Instead of testing both for return and state
                // test once for return and then test states
                if (event.key.code == Keyboard::Enter)
                {
                    // if paused
                    if (state == State::PAUSED)
                    {
                        state = State::PLAYING;
                        clock.restart();
                    }
                    // if game over
                    else if (state == State::GAME_OVER)
                    {
                        state = State::LEVEL_UP;
                    }
                    // if playing
                    else if (state == State::PLAYING)
                    {
                        state = State::PAUSED;
                    }
                } // end section for return key and state tests
                // Playing game and a key is pressed!
                if (state == State::PLAYING)
                {
                    if (event.key.code == Keyboard::W)
                    {
                        player.moveUp();
                    }
                    else if (event.key.code == Keyboard::S)
                    {
                        player.moveDown();
                    }
                    if (event.key.code == Keyboard::A)
                    {
                        player.moveLeft();
                    }
                    else if (event.key.code == Keyboard::D)
                    {
                        player.moveRight();
                    }

                    if (event.key.code == Keyboard::R)
                    {
                        // Reload clip if there are spares and room in clip
                        std::tie(bulletsInClip, bulletSpares) = reload(bulletSpares, bulletsInClip, clipSize);
                    }

                } // end Playing game and key pressed section
                // start Level Up section of key pressed
                if (state == State::LEVEL_UP)
                {

                    if (event.key.code == Keyboard::Num1)
                    {
                        state = State::PLAYING;
                    }
                    if (event.key.code == Keyboard::Num2)
                    {
                        state = State::PLAYING;
                    }
                    if (event.key.code == Keyboard::Num3)
                    {
                        state = State::PLAYING;
                    }
                    if (event.key.code == Keyboard::Num4)
                    {
                        state = State::PLAYING;
                    }
                    if (event.key.code == Keyboard::Num5)
                    {
                        state = State::PLAYING;
                    }
                    if (event.key.code == Keyboard::Num6)
                    {
                        state = State::PLAYING;
                    }

                    if (state == State::PLAYING)
                    {
                        arena.width = 1000;
                        arena.height = 1000;
                        arena.left = 0;
                        arena.top = 0;

                        int tileSize = createBackground(background, arena);
                        window.setMouseCursorVisible(false);
                        // When we spawn the player it will be in the center of
                        // the arena and we will center the mainView at the player
                        player.spawn(arena, resolution, tileSize);
                        healthPickup.setArena(arena);
                        ammoPickup.setArena(arena);

                        delete[] zombies;
                        numZombies = 10;
                        zombies = createHorde(numZombies, arena);
                        numZombiesAlive = numZombies;

                        clock.restart();
                    }
                } // End leveling up section
            }

            if (event.type == Event::KeyReleased)
            {
                if (state == State::PLAYING)
                {
                    if (event.key.code == Keyboard::W)
                    {
                        player.stopUp();
                    }
                    if (event.key.code == Keyboard::S)
                    {
                        player.stopDown();
                    }

                    if (event.key.code == Keyboard::A)
                    {
                        player.stopLeft();
                    }
                    if (event.key.code == Keyboard::D)
                    {
                        player.stopRight();
                    }
                }
            }

            if (event.type == Event::MouseButtonPressed)
            {
                if (state == State::PLAYING)
                {
                    if (event.mouseButton.button == Mouse::Left)
                    {
                        if (gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds() > 1000 / fireRate &&
                            bulletsInClip > 0)
                        {
                            mouseScreenPosition = Mouse::getPosition();
                            mouseWorldPosition = window.mapPixelToCoords(mouseScreenPosition, mainView);
                            bullets[currentBullet].shoot(player.getCenter().x, player.getCenter().y, mouseWorldPosition.x, mouseWorldPosition.y);
                            currentBullet++;
                            if (currentBullet > 99)
                            {
                                currentBullet = 0;
                            }
                            lastPressed = gameTimeTotal;
                            bulletsInClip--;
                        }
                    }
                    if (event.mouseButton.button == Mouse::Right)
                    {
                        std::tie(bulletsInClip, bulletSpares) = reload(bulletSpares, bulletsInClip, clipSize);
                    }
                }
            }

        } // End polling events
          /**
           * all code that goes before
           * drawing sprites to screen
           * place here.
           */
        window.clear();
        // The code when actually playing the game portion for DRAWing and setting
        // of POSITIONS
        if (state == State::PLAYING)
        {

            Time dt = clock.restart();
            gameTimeTotal += dt;

            float dtAsSeconds = dt.asSeconds();

            mouseScreenPosition = Mouse::getPosition();
            mouseWorldPosition = window.mapPixelToCoords(mouseScreenPosition, mainView);

            player.update(dtAsSeconds, mouseWorldPosition);

            Vector2f playerPosition(player.getCenter());
            Vector2f mainViewCenter;

            // This should be the start of the code to either move the world or the player
            // It is not complete yet be cause it is only dealing with if the arena is bigger than
            // the size of the view
            if (arena.width > mainView.getSize().x)
            {
                if (playerPosition.x - (mainView.getSize().x / 2) <= 0)
                {
                    mainViewCenter.x = arena.left + (mainView.getSize().x / 2);
                }
                else if (playerPosition.x + (mainView.getSize().x / 2) >= arena.width)
                {
                    mainViewCenter.x = arena.width - (mainView.getSize().x / 2);
                }
                else
                {
                    mainViewCenter.x = playerPosition.x;
                }
            }
            else if (arena.width <= mainView.getSize().x)
            {
                mainViewCenter.x = arena.width / 2;
            }
            // This is the Y section of centering the View around player or not.
            if (arena.height > mainView.getSize().y)
            {
                if (playerPosition.y - (mainView.getSize().y / 2) <= 0)
                {
                    mainViewCenter.y = arena.top + (mainView.getSize().y / 2);
                }
                else if (playerPosition.y + (mainView.getSize().y / 2) >= arena.height)
                {
                    mainViewCenter.y = arena.height - (mainView.getSize().y / 2);
                }
                else
                {
                    mainViewCenter.y = playerPosition.y;
                }
            }
            else if (arena.height <= mainView.getSize().y)
            {
                mainViewCenter.y = arena.height / 2;
            }

            mainView.setCenter(Vector2f(mainViewCenter.x, mainViewCenter.y));

            // Move the zombies
            for (int z = 0; z < numZombies; z++)
            {
                if (zombies[z].isAlive())
                {
                    zombies[z].update(dt.asSeconds(), playerPosition);
                }
            }

            for (int i = 0; i < 100; i++)
            {
                if (bullets[i].isInFlight())
                {
                    bullets[i].update(dt.asSeconds());
                }
            }
            healthPickup.update(dt.asSeconds());
            ammoPickup.update(dt.asSeconds());

            // Collision detection time
            // did we shoot a zombie?
            for (int b = 0; b < 100; b++)
            {
                for (int z = 0; z < numZombies; z++)
                {
                    if (bullets[b].isInFlight() && zombies[z].isAlive())
                    {
                        if (bullets[b].getPosition().intersects(zombies[z].getPosition()))
                        {
                            bullets[b].stop();
                            if (zombies[z].hit())
                            {
                                score += 10;
                                if (score > highScore)
                                {
                                    highScore = score;
                                }
                                numZombiesAlive -= 1;
                                if (numZombiesAlive <= 0)
                                {
                                    state = State::LEVEL_UP;
                                }
                            }
                        }
                    }
                }
            }
            // Did a zombie hit the player?
            for (int z = 0; z < numZombies; z++)
            {
                if (player.getPosition().intersects(zombies[z].getPosition()) && zombies[z].isAlive())
                {
                    if (player.hit(gameTimeTotal))
                    {
                    }
                    if (player.getHealth() <= 0)
                    {
                        state = State::GAME_OVER;
                    }
                }
            }
            // Did player get the Pickup?
            if (player.getPosition().intersects(healthPickup.getPosition()) && healthPickup.isSpawned())
            {
                player.increaseHealthLevel(healthPickup.gotIt());
            }
            if (player.getPosition().intersects(ammoPickup.getPosition()) && ammoPickup.isSpawned())
            {
                bulletSpares += ammoPickup.gotIt();
            }
            // End Collision detection
            spriteCrosshair.setPosition(mouseWorldPosition.x, mouseWorldPosition.y);
            window.setView(mainView);
            window.draw(background, &texBackground);
            // Draw zombies
            for (int z = 0; z < numZombies; z++)
            {
                window.draw(zombies[z].getSprite());
            }
            for (int b = 0; b < 100; b++)
            {
                if (bullets[b].isInFlight())
                {
                    window.draw(bullets[b].getShape());
                }
            }
            if (ammoPickup.isSpawned())
            {
                window.draw(ammoPickup.getSprite());
            }
            if (healthPickup.isSpawned())
            {
                window.draw(healthPickup.getSprite());
            }
            window.draw(player.getSprite());
            window.draw(spriteCrosshair);
        }
        if (state == State::LEVEL_UP)
        {
        }
        if (state == State::PAUSED)
        {
        }
        if (state == State::GAME_OVER)
        {
            player.resetPlayerStats();
        }
        // Place window.draw code here
        window.display();
    } // End game loop

    window.setMouseCursorVisible(true);
    delete[] zombies;
    return 0;
}
