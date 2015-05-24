#ifndef MINO_O_H
#define MINO_O_H

#include "TetroMino.h"
#include "IO.h"

class Mino_O : public TetroMino {
	public:
		Mino_O(IO &,int);
	private:
//		virtual void setStyle();
};

#endif
