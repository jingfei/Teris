#ifndef MINO_I_H
#define MINO_I_H

#include "TetroMino.h"
#include "IO.h"

class Mino_I : public TetroMino {
	public:
		Mino_I(IO &,int);
//		int Style[4];
	private:
//		virtual void setStyle();
};

#endif
