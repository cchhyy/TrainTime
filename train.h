#ifndef TRAIN_H_INCLUDED
#define TRAIN_H_INCLUDED
/**
�г���Ϣ��Ķ��塣��Ա���������ء�Ŀ�ĵء�
�г��Ρ�����ʱ�䡢����ʱ�䡣
**/
#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <map>
#include "time.h"
using namespace std;

class train_inf
{
private:
    string from,to;
    char name[20];
    time_inf from_time,to_time;

public:
    train_inf();
    train_inf(string f,string t,char* n,time_inf ft,time_inf tt);
    string getFrom(); //���س�����
    string getTo();  //����Ŀ�ĵ�
    char* getName(); //�����г���
    time_inf getFTtime(int n); // n=1���س���ʱ�䣻n=2���ص���ʱ��
    void train_show(); //����г��ĸ�����Ϣ
    bool saveInf(); //����˶����ļ�
    bool trainAdd(); //����г���Ϣ
    bool trainDel(); //ɾ���г���Ϣ
    bool trainChange(); //�޸��г���Ϣ
    /**�ܵ��г�ʱ�̲�ѯ�����������������ƺ������ɸѡ�����������**/
    bool trainSearch();
    /**ɸѡ���г���Ϊname���г���Ϣ**/
    void trainSearchByName(string name,queue<train_inf> &q);
    /**ɸѡ��������Ϊf���г���Ϣ**/
    void trainSearchByFrom(string f,queue<train_inf> &q);
    /**ɸѡ��Ŀ�ĵ�Ϊt���г���Ϣ**/
    void trainSearchByTo(string t,queue<train_inf> &q);
    /**ɸѡ������ʱ��Ϊft���г���Ϣ**/
    void trainSearchByFTime(time_inf ft,queue<train_inf> &q);
    /**ɸѡ������Ϊk���г���Ϣ**/
    void trainSearchByKind(char k,queue<train_inf> &q);
    static int findMinPath(queue<train_inf> q,string from,string to);
    static int findNum(map<int,string> m,string s);
    static bool judgeTime(vector<train_inf> v,map<int,string> m,int i,int k,int j);
};


#endif // TRAIN_H_INCLUDED
