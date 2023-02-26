CC= g++
CCFLAGS = -g -lsfml-graphics -lsfml-window -lsfml-system

all:
	$(CC) -o zombie main.cpp bullet.cpp createBackground.cpp createHorde.cpp player.cpp textureHolder.cpp zombie.cpp $(CCFLAGS) 

clean:
	rm zombie
