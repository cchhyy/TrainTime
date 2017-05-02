#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

/**
时间类的定义，成员有年、月、日、时、分
提供基本的时间操作。
**/
#include <string>
#include <cstring>
using namespace std;

class time_inf
{
public:
    int year,month,day,hour,minute;
public:
    time_inf();
    time_inf(int y,int mo,int d,int h,int mi);
    int getTi(int n);   //1-5：分别返回y,m,d,h,m
    /**获得当前系统时间，通过库函数**/
    static char* GetCurTime();
    /** 判断此时间对象是否已经超过当前时间，若是返回1，否则返回0**/
    bool isOverCur();
    /**与另一个时间对象进行比较，大于，等于，小于**/
    int compare(time_inf t);
    /**年成员不常用，为简化用户输入直接用函数获取年份**/
    static int getCurYear();
};

#endif // TIME_H_INCLUDED
