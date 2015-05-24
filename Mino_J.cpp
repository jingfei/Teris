#include "Mino_J.h"
using namespace std;

/* 
0:0000 1:0001 2:0010 3:0011 4:0100 5:0101 6:0110 7:0111
8:1000 9:1001 a:1010 b:1011 c:1100 d:1101 e:1110 f:1111
*/

Mino_J::Mino_J(IO &iioo,int r):TetroMino(0x0e20,0x0226,0x08e0,0x0644,iioo,r){
//	setStyle();	
}
/*
void Mino_J::setStyle(){
	Style[0]=0x0e20;
	Style[1]=0x0226;
	Style[2]=0x08e0;
	Style[3]=0x0644;
}
*/
