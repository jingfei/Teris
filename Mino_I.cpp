#include "Mino_I.h"
using namespace std;

/* 
0:0000 1:0001 2:0010 3:0011 4:0100 5:0101 6:0110 7:0111
8:1000 9:1001 a:1010 b:1011 c:1100 d:1101 e:1110 f:1111
*/

Mino_I::Mino_I(IO &iioo,int r):TetroMino(0x0f00,0x2222,0x0f00,0x2222,iioo,r){
}
/*
void Mino_I::setStyle(){
	Style[0]=0xf000;
	Style[1]=0x2222;
	Style[2]=0xf000;
	Style[3]=0x2222;
}*/
