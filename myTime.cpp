#include "myTime.h"
#include <iostream>
#include "IO.h"

myTime::myTime(IO &iioo):io(iioo){
	stopTimeTotal=0;
}

void myTime::Init(int L){
	timeBeg=time(NULL);
	Limit=L;
	io.ShowInit(Limit);
}

int myTime::getTime(){
	timeNow=time(NULL);
	return (int)(timeNow-timeBeg-stopTimeTotal);
}

void myTime::showTime(){
	io.showTime(Limit-getTime());
}

void myTime::stopTime(){
	stopTimeBeg=time(NULL);
}

void myTime::contTime(){
	int tmp=time(NULL);
	stopTimeTotal+=(tmp-stopTimeBeg);;
}

