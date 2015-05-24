#ifndef IO_H
#define IO_H

#include <ncurses.h>

class IO{
//	friend Tetris;
	public:
		IO();
//		~IO();
		const int colorNum;
		void SetRoom(int n);
		void ShowInit(int t);
		void Display(int y,int x,int color);
		int Key();
		struct Room{
//			WINDOW *Win;
			int startx, starty;
		}Room[2];
	//	WINDOW *Room1, *Room2;
		const int Height,Width;
		void mmove(int r,int y,int x);
		void Over(bool,bool,int,int,int,int,int t);
		void ShowScore(int r,int Score,int Line,int Level);
		void showTime(int);
		void TimeEnd();
		void TimeCount(int);
		bool Wait(int,int,int,int,int);
	private:
		void GameInit();
		void ShowRoom(int n);
		void SetColor();
		void WantScore(int,int,int,int,int);
		void NoScore();
};

#endif
