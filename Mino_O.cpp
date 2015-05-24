#include "Mino_O.h"
using namespace std;

/* 
0:0000 1:0001 2:0010 3:0011 4:0100 5:0101 6:0110 7:0111
8:1000 9:1001 a:1010 b:1011 c:1100 d:1101 e:1110 f:1111
*/

Mino_O::Mino_O(IO &iioo,int r):TetroMino(0x0660,0x0660,0x0660,0x0660,iioo,r){
//	setStyle();	
}
/*
void Mino_O::setStyle(){
	Style[0]=0x0660;
	Style[1]=0x0660;
	Style[2]=0x0660;
	Style[3]=0x0660;
}
*/
