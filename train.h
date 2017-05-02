#ifndef TRAIN_H_INCLUDED
#define TRAIN_H_INCLUDED
/**
列车信息类的定义。成员包括出发地、目的地、
列车次、出发时间、到达时间。
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
    string getFrom(); //返回出发地
    string getTo();  //返回目的地
    char* getName(); //返回列车次
    time_inf getFTtime(int n); // n=1返回出发时间；n=2返回到达时间
    void train_show(); //输出列车的各个信息
    bool saveInf(); //保存此对象到文件
    bool trainAdd(); //添加列车信息
    bool trainDel(); //删除列车信息
    bool trainChange(); //修改列车信息
    /**总的列车时刻查询函数，调用其它限制函数层层筛选，最后输出结果**/
    bool trainSearch();
    /**筛选出列车次为name的列车信息**/
    void trainSearchByName(string name,queue<train_inf> &q);
    /**筛选出出发地为f的列车信息**/
    void trainSearchByFrom(string f,queue<train_inf> &q);
    /**筛选出目的地为t的列车信息**/
    void trainSearchByTo(string t,queue<train_inf> &q);
    /**筛选出出发时间为ft的列车信息**/
    void trainSearchByFTime(time_inf ft,queue<train_inf> &q);
    /**筛选出种类为k的列车信息**/
    void trainSearchByKind(char k,queue<train_inf> &q);
    static int findMinPath(queue<train_inf> q,string from,string to);
    static int findNum(map<int,string> m,string s);
    static bool judgeTime(vector<train_inf> v,map<int,string> m,int i,int k,int j);
};


#endif // TRAIN_H_INCLUDED
