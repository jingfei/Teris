#ifndef MINO_S_H
#define MINO_S_H

#include "TetroMino.h"
#include "IO.h"

class Mino_S : public TetroMino {
	public:
		Mino_S(IO &,int);
	private:
//		virtual void setStyle();
};

#endif
