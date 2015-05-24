all: main.o Tetris.o TetroMino.o IO.o myTime.o Mino_I.o Mino_J.o Mino_L.o Mino_O.o Mino_S.o Mino_T.o Mino_Z.o
	g++ -o proj2 main.o Tetris.o TetroMino.o IO.o myTime.o Mino_I.o Mino_J.o Mino_L.o Mino_O.o Mino_S.o Mino_T.o Mino_Z.o -lncurses

main.o: proj2.cpp
	g++ -o main.o -c proj2.cpp

Tetris.o: Tetris.cpp Tetris.h
	g++ -c Tetris.cpp

TetroMino.o: TetroMino.cpp TetroMino.h
	g++ -c TetroMino.cpp

IO.o: IO.h IO.cpp
	g++ -c IO.cpp -lncurses

myTime.o: myTime.h myTime.cpp
	g++ -c myTime.cpp

Mino_I.o: Mino_I.h Mino_I.cpp TetroMino.h
	g++ -c Mino_I.cpp

Mino_J.o: Mino_J.h Mino_J.cpp TetroMino.h
	g++ -c Mino_J.cpp

Mino_L.o: Mino_L.h Mino_L.cpp TetroMino.h
	g++ -c Mino_L.cpp

Mino_O.o: Mino_O.h Mino_O.cpp TetroMino.h
	g++ -c Mino_O.cpp

Mino_S.o: Mino_S.h Mino_S.cpp TetroMino.h
	g++ -c Mino_S.cpp

Mino_T.o: Mino_T.h Mino_T.cpp TetroMino.h
	g++ -c Mino_T.cpp

Mino_Z.o: Mino_Z.h Mino_Z.cpp TetroMino.h
	g++ -c Mino_Z.cpp

clean:
	rm *.o

