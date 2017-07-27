#ifndef MYCLOCK_H
#define MYCLOCK_H
#include <ctime>
#include <iostream>
#include <map>
#include "music.h"
class myClock
{
	private:
		time_t t;
		struct tm * now;
		int alarmHour;
		int alarmMinute;
		std::string alarmAP;
		bool alarmStart;
		std::map<int,std::string> converter;
		music alarmSound;
	public:
		myClock();
		std::string getTime();
		std::string getDate();
		std::string getAlarmTime();
		bool checkAlarm();
		void setAlarm(int _alarmHour, int _alarmMinute, std::string AP);
		void waitAlarm();
		void startAlarm(); //possibly use bass audio or something
		void endAlarm(); // stops alarm
};


#endif 
