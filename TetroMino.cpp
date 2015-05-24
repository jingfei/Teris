#include "TetroMino.h"
#include "IO.h"
#include <cstdlib>
#include <ctime>
using namespace std;

TetroMino::TetroMino(IO &iioo):io(iioo){

}

TetroMino::TetroMino(int a,int b,int c,int d,IO &iioo,int r):io(iioo),dir(0){
	X=io.Room[r].startx+io.Width/2-4;
	Y=io.Room[r].starty;
	ROOM=r;
	setStyle(a,b,c,d);
}

TetroMino& TetroMino::operator>>=(int i){
	this->dir+=i;
	this->dir%=4;
	return *this;
}

void TetroMino::ShowMino(int Loc,bool gray,bool Random){
	int tmp; int xx,yy;
	if(gray){tmp=color; color=7;}
	if(Loc==0){
		srand(time(NULL));
		color=rand()%(io.colorNum-1)+2;  //外牆顏色不能用
	}
	if(Loc==0 && ROOM==0){
		color+=rand();
		color%=(io.colorNum-1);
		color+=2;
	}
	if(Random){
		color+=rand()/2;
		color%=(io.colorNum-1);
		color+=2;
	}
	int cmp=0x8000;
	for(int y=0; y<4; y++)
		for(int x=0; x<4; x++, cmp>>=1){
			if(Style[dir] & cmp){
				if(ROOM==0 && Loc==0){
					yy=1+y; xx=5+x*2;
					io.Display(yy,xx,color);
					io.Display(yy,xx+1,color);
				}
				else if(ROOM==1 && Loc==0){
					yy=1+y; xx=67+x*2;
					io.Display(yy,xx,color);
					io.Display(yy,xx+1,color);
				}
				else if(Loc==1){
					io.Display(Y+y,X+x*2,color);
					io.Display(Y+y,X+x*2+1,color);
				}
			}
		}
	if(gray)color=tmp;
}

void TetroMino::setStyle(int a,int b,int c,int d){
	Style[0]=a; Style[1]=b; Style[2]=c; Style[3]=d;
}

void TetroMino::RemoveMino(int Loc){
	int cmp=0x8000;	 int xx,yy;
	for(int y=0; y<4; y++)
		for(int x=0; x<4; x++, cmp>>=1){
			if(Style[dir] & cmp){
				if(ROOM==0 && Loc==0){
					yy=1+y; xx=5+x*2;
					io.Display(yy,xx,0);
					io.Display(yy,xx+1,0);
				}
				else if(ROOM==1 && Loc==0){
					yy=1+y; xx=67+x*2;
					io.Display(yy,xx,0);
					io.Display(yy,xx+1,0);
				}
				else if(Loc==1){
					io.Display(Y+y,X+x*2,0);
					io.Display(Y+y,X+x*2+1,0);
				}
			}
		}
}

