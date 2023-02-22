CC= g++


all:
	$(CC) -o zombie main.cpp player.cpp createBackground.cpp -g -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm zombie
