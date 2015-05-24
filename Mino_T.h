#ifndef MINO_T_H
#define MINO_T_H

#include "TetroMino.h"
#include "IO.h"

class Mino_T : public TetroMino {
	public:
		Mino_T(IO &,int);
	private:
//		virtual void setStyle();
};

#endif
