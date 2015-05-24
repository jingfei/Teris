#ifndef TETROMINO_H
#define TETROMINO_H

#include "IO.h"

class TetroMino{
	public:
		TetroMino &operator>>=(int i);
		TetroMino(IO &);
		virtual ~TetroMino(){}
		void ShowMino(int Loc,bool gray=false,bool Random=false); 
		void RemoveMino(int Loc);
		int Style[4];
		int color;
		int dir;
		int Y,X,ROOM;
	protected:
		TetroMino(int,int,int,int,IO &,int);
		bool Check(int n,int Shape,int my,int mx);
		bool End;
	private:
		void setStyle(int,int,int,int);
		IO &io;
};

#endif
