#ifndef TETRIS_H
#define TETRIS_H

#include "IO.h"
#include "TetroMino.h"
#include "myTime.h"
#include <cstring>

class Tetris{
	friend class IO;
	public:
		Tetris(IO &,myTime &);
		void Start();
	private:
		IO &io;
		myTime &Time;
		bool End;
		static int SPEED;
		static int Limit;
		static int Block[30][100];
		TetroMino* NextMino(int,bool Random=false);
		struct Player{
			TetroMino* Last;
			TetroMino* Down;
			int Score,Line,Level;
			//15 50 150 600
			bool Win;
		}P[2];
		void Init();
		int MovingMino();
		void seeDown(TetroMino);
		bool Move(TetroMino);
		void MoveDown(TetroMino);
		bool Check(TetroMino);
		void setBlock(TetroMino);
		void RemoveLine(int,int);
		bool TimeEnd();
};

#endif

