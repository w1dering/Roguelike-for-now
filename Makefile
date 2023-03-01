default:
	g++ main.cpp Obstacles/Platform.cpp Player/Player.cpp Weapons/Bow.cpp -o test.exe -O2 -Wall -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm