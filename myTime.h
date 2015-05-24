#ifndef MYTIME_H
#define MYTIME_H

#include "IO.h"

class myTime{
	public:
		myTime(IO &iioo);
		void Init(int Limit);
		void showTime();
		int getTime();
		void stopTime();
		void contTime();
	private:
		IO &io;
		int timeBeg;
		int timeNow;
		int Limit;
		int stopTimeBeg;
		int stopTimeTotal;
};

#endif
