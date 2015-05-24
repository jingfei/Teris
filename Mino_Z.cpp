#include "Mino_Z.h"
using namespace std;

/* 
0:0000 1:0001 2:0010 3:0011 4:0100 5:0101 6:0110 7:0111
8:1000 9:1001 a:1010 b:1011 c:1100 d:1101 e:1110 f:1111
*/

Mino_Z::Mino_Z(IO &iioo,int r):TetroMino(0x0c60,0x0264,0x0c60,0x0264,iioo,r){
//	setStyle();	
}
/*
void Mino_Z::setStyle(){
	Style[0]=0x0c60;
	Style[1]=0x0264;
	Style[2]=0x0c60;
	Style[3]=0x0264;
}
*/
