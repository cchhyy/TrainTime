#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

/**
ʱ����Ķ��壬��Ա���ꡢ�¡��ա�ʱ����
�ṩ������ʱ�������
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
    int getTi(int n);   //1-5���ֱ𷵻�y,m,d,h,m
    /**��õ�ǰϵͳʱ�䣬ͨ���⺯��**/
    static char* GetCurTime();
    /** �жϴ�ʱ������Ƿ��Ѿ�������ǰʱ�䣬���Ƿ���1�����򷵻�0**/
    bool isOverCur();
    /**����һ��ʱ�������бȽϣ����ڣ����ڣ�С��**/
    int compare(time_inf t);
    /**���Ա�����ã�Ϊ���û�����ֱ���ú�����ȡ���**/
    static int getCurYear();
};

#endif // TIME_H_INCLUDED
