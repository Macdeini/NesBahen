all: 
	g++ -Isrc/Include -Lsrc/lib -o prog testing\*.cpp NES\*.cpp -I "D:\Personal Projects\Projects\nesbahen\NesBahen" -lmingw32 -lSDL2main -lSDL2

