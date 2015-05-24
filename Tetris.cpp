#include <iostream>
#include <cstdlib>
#include <cstring>
#include "Tetris.h"
#include "IO.h"
#include "TetroMino.h"
#include "myTime.h"
#include "Mino_I.h"
#include "Mino_J.h"
#include "Mino_L.h"
#include "Mino_O.h"
#include "Mino_S.h"
#include "Mino_T.h"
#include "Mino_Z.h"
using namespace std;

Tetris::Tetris(IO &iioo,myTime &T) : io(iioo),Time(T) {
	io.SetRoom(1);
	io.SetRoom(0);
}

void Tetris::Init(){
	End=false;
	P[0].Score=0; P[0].Level=1; P[0].Line=0;
	P[1].Score=0; P[1].Level=1; P[1].Line=0;
	io.ShowScore(0,P[0].Score,P[0].Line,P[0].Level);
	io.ShowScore(1,P[1].Score,P[1].Line,P[1].Level);
	P[0].Win=P[1].Win=false;
	Time.Init(Limit);
}

TetroMino* Tetris::NextMino(int r,bool Random){
	const int minoNum=7;
	srand(time(NULL));
	TetroMino *mino;
	int Kind=rand()%minoNum;
	if(r==1){
		Kind+=rand();
		Kind%=minoNum;
	}
	if(Random){
		Kind+=rand()/2;
		Kind%=minoNum;
	}
	switch(Kind){
		case 0: mino=new Mino_I(io,r); break;
		case 1: mino=new Mino_J(io,r); break;
		case 2: mino=new Mino_L(io,r); break;
		case 3: mino=new Mino_O(io,r); break;
		case 4: mino=new Mino_S(io,r); break;
		case 5: mino=new Mino_T(io,r); break;
		case 6: mino=new Mino_Z(io,r); break;
	}	
	mino->ShowMino(0,false,true);
	return mino;
}

void Tetris::Start(){
	Init();
	int r=0;
	P[1].Last=NextMino(1,true);
	P[1].Down=P[1].Last;
	P[1].Last->RemoveMino(0);
	P[1].Last=NextMino(1);
	P[1].Down->ShowMino(1,false,true);
	seeDown(*(P[1].Down));
	P[0].Last=NextMino(0,true);
	do{
		 P[r].Down=P[r].Last;
		 P[r].Last->RemoveMino(0);
		 P[r].Last=NextMino(r);
		 P[r].Down->ShowMino(1);
		 seeDown(*(P[r].Down));
		 r=MovingMino();
		 if(!End) delete P[r].Down;
	}while(!End);
	if(P[0].Last!=0) delete P[0].Last;
	if(P[1].Last!=0) delete P[1].Last;
	if(P[0].Down!=0) delete P[0].Down;
	if(P[1].Down!=0) delete P[1].Down;
	io.Over(P[1].Win,P[0].Win,P[1].Score,P[0].Score,P[1].Line,P[0].Line,Time.getTime());
}

//Key: 1234 up down left right

int Tetris::MovingMino(){
	int ttime=0;
	while(true){
		ttime++;
		if(ttime%SPEED==0){
			Time.showTime();
			if(TimeEnd()) break;
			ttime=0; 
			TetroMino Temp1=*(P[0].Down),Temp2=*(P[1].Down);
			Temp1.Y++;
			Move(Temp1);
			Temp2.Y++;
			Move(Temp2);
		}
		//p1
		TetroMino Temp1=*(P[1].Down),Temp2=*(P[0].Down);
		Temp1.Y++;
		if(!Check(Temp1)){
			if(P[1].Down->Y <= io.Room[1].starty){ 
				P[0].Win=true;
				P[1].Win=false;
				End=true;
			}
			setBlock(*(P[1].Down));
			RemoveLine(P[1].Down->Y,1);
			return 1;
		}
		//p2
		Temp2.Y++;
		if(!Check(Temp2)){
			if(P[0].Down->Y <= io.Room[0].starty){
				P[0].Win=false;
				P[1].Win=true;
				End=true;
			}
			setBlock(*(P[0].Down));
			RemoveLine(P[0].Down->Y,0);
			return 0;
		}
		bool tmp;
		TetroMino T1=*(P[1].Down),T2=*(P[0].Down);
		int k;
		k=io.Key();
		switch(k){
			case 1:		//up
				T1>>=1;
				tmp=Move(T1);
				if(tmp)seeDown(*(P[1].Down));
				break;
			case 2:		//p1 down
				MoveDown(T1);
				break;
			case 3:		//p1 left
				T1.X-=2;
				tmp=Move(T1);
				if(tmp)seeDown(*(P[1].Down));
				break;
			case 4:		//p1 right
				T1.X+=2;
				tmp=Move(T1);
				if(tmp)seeDown(*(P[1].Down));
				break;
			case 5:		//p2 up
				T2>>=1;
				tmp=Move(T2);
				if(tmp)seeDown(*(P[0].Down));
				break;
			case 6:		//p2 down
				MoveDown(T2);
				break;
			case 7:		//p2 left
				T2.X-=2;
				tmp=Move(T2);
				if(tmp)seeDown(*(P[0].Down));
				break;
			case 8:		//p2 right
				T2.X+=2;
				tmp=Move(T2);
				if(tmp)seeDown(*(P[0].Down));
				break;
			case -2:
				Time.stopTime();
				if(!io.Wait(P[0].Score,P[1].Score,P[0].Line,P[1].Line,Time.getTime())) End=true;
				Time.contTime();
				if(End){
					P[0].Win=P[1].Win=false;
					P[0].Score>P[1].Score?P[0].Win=true:P[1].Win=true;
					return 0;
				}
				break;
			case -1:
				End=true;
				P[0].Win=P[1].Win=false;
				P[0].Score>P[1].Score?P[0].Win=true:P[1].Win=true;
				return 0;
		}
	}
}

void Tetris::seeDown(TetroMino m){
	while(Check(m)){m.Y++;}
	m.Y--;
	m.ShowMino(1,true);
}

bool Tetris::Move(TetroMino T){
	int r=T.ROOM;
	if(!Check(T)) return false;
	P[r].Down->RemoveMino(1);
	TetroMino tmp=*(P[r].Down); tmp.Y=T.Y+1;
	while(Check(tmp)){tmp.Y++;}
	tmp.Y--;
	tmp.RemoveMino(1);
	(P[r].Down)->Y=T.Y;
	(P[r].Down)->X=T.X;
	(P[r].Down)->dir=T.dir;
	P[r].Down->ShowMino(1);
	return true;
}

void Tetris::MoveDown(TetroMino tmp){
	tmp.RemoveMino(1);
	while(Check(tmp)){
		(tmp.Y)++;
	}
	tmp.Y--;
	tmp.ShowMino(1);
	(P[tmp.ROOM].Down)->Y=tmp.Y;
}

bool Tetris::Check(TetroMino tmp){
	int cmp=0x8000;
	for(int yy=0; yy<4; yy++)
		for(int xx=0; xx<4; xx++, cmp>>=1)
			if(tmp.Style[tmp.dir] & cmp){
				if(Block[tmp.Y+yy][tmp.X+xx*2]==8 || Block[tmp.Y+yy][tmp.X+xx*2+1]==8) 
					continue;
				if(Block[tmp.Y+yy][tmp.X+xx*2] || Block[tmp.Y+yy][tmp.X+xx*2+1]) 
					return false;
			}
	return true;
}

void Tetris::setBlock(TetroMino tmp){
	int cmp=0x8000;
	for(int yy=0; yy<4; yy++)
		for(int xx=0; xx<4; xx++, cmp>>=1)
			if(tmp.Style[tmp.dir] & cmp)
				Block[tmp.Y+yy][tmp.X+xx*2]=Block[tmp.Y+yy][tmp.X+xx*2+1]=tmp.color;
}

void Tetris::RemoveLine(int y,int r){
	int Total=0;
	int sx=io.Room[r].startx,sy=io.Room[r].starty;
	bool Remove;
	for(int yy=y; yy<y+4; yy++){
		if(yy>=sy+io.Height) break;
		if(Block[yy][sx]==1) break;
		Remove=true;
		for(int xx=sx; xx<sx+io.Width; xx++)
			if(Block[yy][xx]==0){ Remove=false; continue;}
		if(Remove){
			Total++;
			for(int Y=yy; Y>sy+1; Y--)
				for(int xx=sx; xx<sx+io.Width; xx++){
					Block[Y][xx]=Block[Y-1][xx];
					io.Display(Y,xx,Block[Y-1][xx]);
				}
			for(int xx=sx; xx<sx+io.Width; xx++){
				io.Display(sy+1,xx,0);
				Block[sy+1][xx]=0;
			}
		}
	}
	//add others line
	int tmpr=(r+1)%2;
	int ry=io.Room[tmpr].starty+io.Height-1,rx=io.Room[tmpr].startx;
	while(Block[ry][rx]==1) ry--;
	if(ry<=io.Room[tmpr].starty){
		P[tmpr].Win=false;
		P[r].Win=true;
		End=true;
	}
	for(int i=0; i<Total; i++){
		for(int j=rx; j<rx+io.Width; j++){
			Block[ry][j]=1;
			io.Display(ry,j,1);
		}
		ry--;
		if(ry<=io.Room[tmpr].starty){
			P[tmpr].Win=false;
			P[r].Win=true;
			End=true;
		}
	}
	
	P[r].Line+=Total;
	if(Total==1) P[r].Score+=15;
	else if(Total==2) P[r].Score+=50;
	else if(Total==3) P[r].Score+=150;
	else if(Total==4) P[r].Score+=600;
	io.ShowScore(r,P[r].Score,P[r].Line,P[r].Level);
}

bool Tetris::TimeEnd(){
	int t=Time.getTime();
	if(t>=Limit){
		End=true;
		io.TimeEnd();
		if(P[0].Score==P[1].Score)
			P[0].Win=P[1].Win=true;
		else if(P[0].Score>P[1].Score){
			P[0].Win=true;
			P[1].Win=false;
		}
		else{
			P[0].Win=false;
			P[1].Win=true;
		}
		return true;
	}
	if(Limit-t<=5) io.TimeCount(Limit-t);
	return false;
}

