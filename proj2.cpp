#include <iostream>
#include "Tetris.h"
#include "myTime.h"
#include "IO.h"
using namespace std;

int Tetris::SPEED=300000;
int Tetris::Limit=100;
int main(){
	IO io;
	myTime Time(io);
	Tetris Game(io,Time);
	Game.Start();
/*	freopen("test.txt","w",stdout);
	for(int i=0; i<30; i++){
		for(int j=0; j<75; j++){
			cout << Tetris::Block[i][j];
		}
		cout << endl;
	}
	cout << endl;
*/	return 0;
}
