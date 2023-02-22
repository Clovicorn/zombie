#include "zombie.h"

int main(void)
{
    enum class State
    {
        PAUSED,
        LEVEL_UP,
        GAME_OVER,
        PLAYING
    };
    Vector2f resolution(1920, 1080);
    State state = State::GAME_OVER;

    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Zombie Killer!", Style::Fullscreen);

    View mainView(FloatRect(0, 0, 1920, 1080));

    Player player;

    Clock clock;
    Time gameTimeTotal;

    Vector2f mouseWorldPosition;
    Vector2i mouseScreenPosition;

    IntRect arena;
    VertexArray background;
    Texture texBackground;
    texBackground.loadFromFile("assets/graphics/background_sheet.png");

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
                        arena.width = 500;
                        arena.height = 500;
                        arena.left = 0;
                        arena.top = 0;

                        int tileSize = createBackground(background, arena);

                        player.spawn(arena, resolution, tileSize);
                        clock.restart();
                    }
                } // End leveling up section
            }

            if (event.type == Event::KeyReleased)
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

        } // End polling events
          /**
           * all code that goes before
           * drawing sprites to scren
           * place here.
           */
        window.clear();
        if (state == State::PLAYING)
        {
            Time dt = clock.restart();
            gameTimeTotal += dt;

            float dtAsSeconds = dt.asSeconds();

            mouseScreenPosition = Mouse::getPosition();
            mouseWorldPosition = window.mapPixelToCoords(mouseScreenPosition, mainView);

            player.update(dtAsSeconds, Mouse::getPosition());

            Vector2f playerPosition(player.getCenter());
            mainView.setCenter(player.getCenter());

            window.setView(mainView);
            window.draw(background, &texBackground);
            window.draw(player.getSprite());
        }
        if (state == State::LEVEL_UP)
        {
        }
        if (state == State::PAUSED)
        {
        }
        if (state == State::GAME_OVER)
        {
        }
        // Place window.draw code here
        window.display();
    } // End game loop

    return 0;
}
