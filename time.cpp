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
�ֱ���ʱ����ꡢ�¡��ա�ʱ����
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
����ϵͳ�⺯���������ǰ��ʱ�䡣
�������õ�time_t�ṹ��
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
����ϵͳ������õ�ǰʱ��ĸ�����Աֵ���뵱ǰ����ĸ�����Ա
���бȽϣ��ж�ʱ���Ƿ��Ѿ����������жϴ˴��г��Ƿ��Ѿ�������
**/
bool time_inf::isOverCur()
{
    char s[128];
	struct tm* local;
	time_t t=time(NULL);
	local=localtime(&t);

	if(local->tm_hour<hour||(local->tm_hour==hour && local->tm_min<=minute))
		return true;						 //�Ƚϵ�ǰʱ���뷢��ʱ��,��ð�εĵ�ǰ״��,���ر�ʾ���δ����
	else
		return false;
}

/**
�ж�����ʱ�������Ⱥ���ԭ�������ڱȽϵĶ��󣬷���1��
��ԭ�������ڱȽϵĶ��󣬷���-1��
����ʱ����ͬ������0.
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
����ϵͳ������õ�ǰ�����
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
