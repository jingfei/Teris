#include "Mino_S.h"
using namespace std;

/* 
0:0000 1:0001 2:0010 3:0011 4:0100 5:0101 6:0110 7:0111
8:1000 9:1001 a:1010 b:1011 c:1100 d:1101 e:1110 f:1111
*/

Mino_S::Mino_S(IO &iioo,int r):TetroMino(0x06c0,0x0462,0x06c0,0x0462,iioo,r){
//	setStyle();	
}
/*
void Mino_S::setStyle(){
	Style[0]=0x06c0;
	Style[1]=0x08c2;
	Style[2]=0x06c0;
	Style[3]=0x08c2;
}
*/
