CC= g++
CCFLAGS = -g -lsfml-graphics -lsfml-window -lsfml-system

all:
	$(CC) -o zombie main.cpp bullet.cpp createBackground.cpp createHorde.cpp pickup.cpp player.cpp reload.cpp textureHolder.cpp zombie.cpp $(CCFLAGS) 

clean:
	rm zombie
