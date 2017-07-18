#include "myClock.h"
#include <ctime>
#include <string>
#include <iostream>
#include <unistd.h>
#include "music.h"
#include <map>
#include <fstream>
myClock::myClock()
{
		t = time(0);
		now = localtime(&t);
		usleep(1000);
		std::ifstream infile("txtFiles/converter.txt");
		int key;
		std::string value;
		while(infile >> key >> value)
			converter[key]=value;
}
std::string myClock::getTime()
{
	t = time(0);
	now = localtime(&t);
	std::string ap = "A. M";
	int hour = now->tm_hour;
	if(hour > 12)
	{
		hour=hour-12;
		ap = "P. M";
	}//std::cout<< "time is " << (converter[now->tm_hour] + converter[now->tm_min]) <<std::endl;
	return (converter[hour] + ". " + converter[now->tm_min] + ". "+  ap);
	//return (std::to_string(now->tm_hour) + ":" + std::to_string(now->tm_min) + ":" +  std::to_string(now->tm_sec)); 
}

std::string numToWord(int x)
{
 
}

std::string myClock::getDate()
{
	
}

bool myClock::checkAlarm()
{
	if(now->tm_hour == alarmHour)
	{
		if(now->tm_min == alarmMinute && !alarmStart)
		{
			return alarmStart =true; 
		}
	}
	//std::cout <<"does it return false?" << std::endl;
	return false; 
}
void myClock::setAlarm(int _alarmHour, int _alarmMinute)
{
	alarmHour=_alarmHour;
	alarmMinute = _alarmMinute;
}

void myClock::startAlarm()
{
	if(alarmStart)
	{
			music c;
			c.playMusic("Alarm");	
			//alarmStart = false;
	}
}
void myClock::endAlarm()
{
	music c;
	c.stopMusic();
	alarmStart = false;
}
