#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include "TetroMino.h"
#include "Tetris.h"
#include "IO.h"
using namespace std;

int Tetris::Block[][100]={0};

IO::IO() : Height(19),Width(20),colorNum(6) {
	GameInit();
}

void IO::GameInit(){
	initscr();
	SetColor();
	cbreak();
	noecho();
	keypad(stdscr,TRUE);
	nodelay(stdscr,TRUE);
}

void IO::SetColor(){
	start_color();
	init_color(COLOR_BLACK,128,128,128);
	init_pair(1,COLOR_RED,COLOR_RED); //wall
	init_pair(2,COLOR_BLUE,COLOR_BLUE);
	init_pair(3,COLOR_GREEN,COLOR_GREEN);
	init_pair(4,COLOR_YELLOW,COLOR_YELLOW);
	init_pair(5,COLOR_MAGENTA,COLOR_MAGENTA);
	init_pair(6,COLOR_CYAN,COLOR_CYAN);
	init_pair(7,COLOR_WHITE,COLOR_WHITE);
	init_pair(8,COLOR_BLACK,COLOR_WHITE);
}

void IO::ShowInit(int t){
	mvprintw(0,30,"Welcome to Tetris!!!");
	mvprintw(6,63,"Press Q to quit");
	mvprintw(7,63,"Press P to stop");
	mvprintw(8,63,"Total time:%3d",t);
	mvprintw(15,63,"how to move:");
	mvprintw(16,65,"turn: up");
	mvprintw(17,65,"  <=: down");
	mvprintw(18,65,"  =>: left");
	mvprintw(19,65," put: down");
	mvprintw(6,0,"Press Q to quit");
	mvprintw(7,0,"Press P to stop");
	mvprintw(8,0,"Total time:%3d",t);
	mvprintw(15,2,"how to move:");
	mvprintw(16,4,"turn: W");
	mvprintw(17,4,"  <=: A");
	mvprintw(18,4,"  =>: D");
	mvprintw(19,4," put: S");
}

void IO::SetRoom(int n){
	int h=LINES,w=COLS;
	//getmaxyx(stdscr,h,w);
	if(n==1){ Room[1].startx=w/2+1; Room[1].starty=1; }
	else if(n==0){ Room[0].startx=w/2-1-Width; Room[0].starty=1; }
	ShowRoom(n);
}

void IO::ShowRoom(int n){
	if(n==0){
		for(int i=0; i<=Height; i++){
			Display(i+Room[0].starty,Room[0].startx-1,1);
			Display(i+Room[0].starty,Room[0].startx-2,1);
			Display(i+Room[0].starty,Room[0].startx+Width,1);
			Tetris::Block[i+Room[0].starty][Room[0].startx-1]=1;
			Tetris::Block[i+Room[0].starty][Room[0].startx-2]=1;
			Tetris::Block[i+Room[0].starty][Room[0].startx+Width]=1;
		}
		for(int i=0; i<Width; i++) {
			Display(Room[0].starty+Height,i+Room[0].startx,1);
			Tetris::Block[Room[0].starty+Height][i+Room[0].startx]=1;
		}
	}
	else if(n==1){
		for(int i=0; i<=Height; i++){
			Display(i+Room[1].starty,Room[1].startx-1,1);
			Display(i+Room[1].starty,Room[1].startx+Width,1);
			Display(i+Room[1].starty,Room[1].startx+Width+1,1);
			Tetris::Block[i+Room[1].starty][Room[1].startx-1]=1;
			Tetris::Block[i+Room[1].starty][Room[1].startx+Width]=1;
			Tetris::Block[i+Room[1].starty][Room[1].startx+Width+1]=1;
		}
		for(int i=0; i<Width; i++){
			Display(Room[1].starty+Height,i+Room[1].startx,1);
			Tetris::Block[Room[1].starty+Height][i+Room[1].startx]=1;
		}
	}
}

void IO::Display(int y,int x,int color){
	if(color==0)
		mvaddch(y,x,' ');
	else{
		attron(COLOR_PAIR(color));
		mvaddch(y,x,'1');
		attroff(COLOR_PAIR(color));
	}
	move(0,0);
}

int IO::Key(){
	int ch;
	if((ch=getch())==ERR) return 0;
	do{
		switch(ch){
			case KEY_LEFT: 
				return 3;
			case KEY_RIGHT: 
				return 4;
			case KEY_UP: 
				return 1;
			case KEY_DOWN: 
				return 2;
			case 'w': case 'W':
				return 5;
			case 's': case 'S':
				return 6;
			case 'a': case 'A':
				return 7;
			case 'd': case 'D':
				return 8;
			case 'p': case 'P':
				return -2;
			case 'q': case 'Q':
				return -1;
		}
	}while((ch=getch())!=ERR);
}

bool IO::Wait(int s1,int s2,int l1,int l2,int t){
	nodelay(stdscr,FALSE);
	mvaddstr(21,Room[0].startx+Width-10,"Press C to continue...");
	WantScore(s1,s2,l1,l2,t);
	int ch=getch();
	while(ch!='c' && ch!='C' && ch!='q' && ch!='Q'){
		ch=getch();
	}
	NoScore();
	nodelay(stdscr,TRUE);
	if(ch=='q' || ch=='Q') return false;
	return true;
}

void IO::WantScore(int s1,int s2,int l1,int l2,int t){
	int Loc1=Room[1].startx+Width/2-7, Loc2=Room[0].startx+Width/2-7;
	mvprintw(12,Loc1-2,"   Your Score: %3d",s1);
	mvprintw(13,Loc1-2,"Rival's Score: %3d",s2);
	mvprintw(14,Loc1-2,"  Remove Line: %3d",l1);
	mvprintw(12,Loc2-2,"   Your Score: %3d",s2);
	mvprintw(13,Loc2-2,"Rival's Score: %3d",s1);
	mvprintw(14,Loc2-2,"  Remove Line: %3d",l2);
	mvprintw(8,Loc1-15,"used time: %2d seconds",t);
}

void IO::NoScore(){
	int Loc1=Room[1].startx+Width/2-7, Loc2=Room[0].startx+Width/2-7;
	for(int i=8; i<=14; i++)
		for(int j=Loc2-2; j<Loc1+20; j++)
			Display(i,j,Tetris::Block[i][j]);
	mvaddstr(21,Room[0].startx+Width-10,"                      ");
}

void IO::Over(bool p1,bool p2,int s1,int s2,int l1,int l2,int t){
	int ch;
	nodelay(stdscr,FALSE);
	int Loc1=Room[1].startx+Width/2-7, Loc2=Room[0].startx+Width/2-7;
	if(p1 && p2){
		mvaddstr(10,Loc2,"    Draw -.-  ");
		mvaddstr(10,Loc1,"    Draw -.-  ");
	}
	else if(!p1 && p2){		//p2 win
		mvaddstr(10,Loc2,"  YOU WIN!!!!!");
		mvaddstr(10,Loc1,"  you lose....");
	}
	else if(!p2 && p1){		//p1 win
		mvaddstr(10,Loc1,"  YOU WIN!!!!!");
		mvaddstr(10,Loc2,"  you lose....");
	}
	mvaddstr(9,Loc1,"              ");
	mvaddstr(9,Loc2,"              ");
	mvaddstr(6,Loc1-9,"Game  Over");
	WantScore(s1,s2,l1,l2,t);
	mvaddstr(21,Room[0].startx+Width-5,"Press Q to end");
	ch=getch();
	while(ch!='q' && ch!='Q'){
		ch=getch();
	}
	endwin();
}

void IO::ShowScore(int r,int Score,int Line,int Level){
	attron(COLOR_PAIR(8)|A_BOLD);
	if(r==1){
		mvprintw(11,66,"Score: %3d",Score);
		mvprintw(12,66,"Line:  %3d",Line);
		mvprintw(13,66,"Level: %3d",Level);
	}
	else if(r==0){
		mvprintw(11,3,"Score: %3d",Score);
		mvprintw(12,3,"Line:  %3d",Line);
		mvprintw(13,3,"Level: %3d",Level);
	}
	attroff(COLOR_PAIR(8)|A_BOLD);
}

void IO::showTime(int t){
	attron(COLOR_PAIR(8)|A_BOLD);
	mvprintw(10,66,"Time:  %3d",t>0?t:0);
	mvprintw(10, 3,"Time:  %3d",t>0?t:0);
	attroff(COLOR_PAIR(8)|A_BOLD);
}

void IO::TimeEnd(){
	mvprintw(4,33,"Time's Up~~~");
}

void IO::TimeCount(int t){
	mvprintw(9,Room[1].startx+Width/2-7,"Time Remain: %d",t);
	mvprintw(9,Room[0].startx+Width/2-7,"Time Remain: %d",t);
//	mvprintw(6,38,"%d",t);
}

