#include "time.h"
#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
using namespace std;

time_inf::time_inf(){}

time_inf::time_inf(int y,int mo,int d,int h,int mi)
{
    year=y;
    month=mo>12?12:mo;
    day=d>31?31:d;
    hour=h>24?0:h;
    minute=mi>60?0:mi;
}

/**
分别获得时间的年、月、日、时、分
**/
int time_inf::getTi(int n)
{
    if(n==1) return year;
    else if(n==2) return month;
    else if(n==3) return day;
    else if(n==4) return hour;
    else if(n==5) return minute;
}

/**
调用系统库函数，输出当前的时间。
运用内置的time_t结构体
**/
char* time_inf::GetCurTime()
{
    char s[50];
	struct tm* local;
	time_t t=time(NULL);
	local=localtime(&t);
	strftime(s,50,"%Y-%m-%d %H:%M ",local);
    cout<<s;
}

/**
调用系统函数获得当前时间的各个成员值，与当前对象的各个成员
进行比较，判断时间是否已经超过，即判断此次列车是否已经出发。
**/
bool time_inf::isOverCur()
{
    char s[128];
	struct tm* local;
	time_t t=time(NULL);
	local=localtime(&t);

	if(local->tm_hour<hour||(local->tm_hour==hour && local->tm_min<=minute))
		return true;						 //比较当前时间与发车时间,获得班次的当前状况,返回表示班次未出发
	else
		return false;
}

/**
判断两个时间对象的先后，若原对象晚于比较的对象，返回1；
若原对象早于比较的对象，返回-1；
若两时间相同，返回0.
**/
int time_inf::compare(time_inf t)
{
    int a=minute+hour*66+day*66*24+month*66*24*32+year*66*24*32*13;
    int b=t.getTi(1)*66*24*32*13+t.getTi(2)*66*24*32+t.getTi(3)*66*24+t.getTi(4)*66+t.getTi(5);
    if(a>b) return 1;
    else if(a<b) return -1;
    else return 0;
}

/**
调用系统函数获得当前的年份
**/
int time_inf::getCurYear()
{
    char s[50];
    int r;
	struct tm* local;
	time_t t=time(NULL);
	local=localtime(&t);
	strftime(s,50,"%Y-%m-%d %H:%M ",local);
	stringstream sf(s);
	sf>>r;
	return r;
}
