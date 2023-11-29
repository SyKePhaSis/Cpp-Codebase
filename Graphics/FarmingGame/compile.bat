gcc main.c -o build/game.exe -O1 -Wno-missing-braces -std=c99 -I ../../Libraries/RayLib/include/ -L ../../Libraries/RayLib/lib/ -Wall -lraylib -lopengl32 -lstdc++ -lgdi32 -lwinmm
build\game.exe
