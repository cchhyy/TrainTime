#include "train.h"
#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <windows.h>
#include "time.h"
#include "menu.h"
#define MAX 0x3f3f3f3f
using namespace std;

train_inf::train_inf(){}

/**列车信息类构造函数
需提供参数出发地(f)、目的地(t)、列车次(name)、出发时间(ft)、
到达时间(tt)**/
train_inf::train_inf(string f,string t,char* n,time_inf ft,time_inf tt)
{
    from=f; to=t;
    strcpy(name,n);
    from_time=ft;
    to_time=tt;
}

/**返回出发地**/
string train_inf::getFrom()
{
    return from;
}

/**返回目的地**/
string train_inf::getTo()
{
    return to;
}

/**返回列车次**/
char* train_inf::getName()
{
    return name;
}

/**返回出发时间或到达时间**/
time_inf train_inf::getFTtime(int n)
{
    if(n==1)
        return from_time;
    else
        return to_time;
}

/**输出列车信息对象的信息**/
void train_inf::train_show()
{
    cout<<"\t"<<name<<"\t"<<from<<"\t"<<from_time.getTi(2)<<"月"<<from_time.getTi(3)<<"日";
    printf("%02d:%02d\t",from_time.getTi(4),from_time.getTi(5));
    cout<<to<<"\t"<<to_time.getTi(2)<<"月"<<to_time.getTi(3)<<"日"<<to_time.getTi(3)<<"日";
    printf("%02d:%02d\t",to_time.getTi(4),to_time.getTi(5));
}
/**
保存信息。以添加的方式打开文件，提示用户输入
各种信息，并判断数据合法性。通过文件输出流的
方式存入文件。若保存成功，返回TRUE，否则返回FALSE。
**/
bool train_inf::saveInf()
{
    ofstream of;
    try
    {
        //以添加的方式打开文件
        of.open("data\\train.txt",ios_base::app);
        if(of.fail())
            throw "文件错误！";
        else
        {
            of<<endl<<name<<" "<<from<<" "<<from_time.getTi(1)<<" "<<from_time.getTi(2)<<" ";
            of<<from_time.getTi(3)<<" "<<from_time.getTi(4)<<" "<<from_time.getTi(5)<<" ";
            of<<to<<" "<<to_time.getTi(1)<<" "<<to_time.getTi(2)<<" "<<to_time.getTi(3)<<" ";
            of<<to_time.getTi(4)<<" "<<to_time.getTi(5);
        }
        }catch(string s){
            cout<<s<<endl;
            return false;
        }
        of.close();
        return true;
}

/**录入列车信息
提示用户输入列车的各种信息，后调用aveInf()
函数爆粗保存信息到文件。成功保存到文件返回TRUE，
保存失败返回FALSE。
**/
bool train_inf::trainAdd()
{
    system("cls");
    menu::setColor(1);
    cout<<"\n\n    　    ────<<列  车  时  刻  信  息  录  入>>──── "<<endl<<endl;
    int y,mo,d,h,mi;

    cout<<"\t\t列车次：";
    cin>>name;
    cout<<"\t\t起点：";
    cin>>from;
    cout<<"\t\t发车时间（月 日 时 分）：";
    y=time_inf::getCurYear();
    cin>>mo>>d>>h>>mi;
    time_inf t1(y,mo,d,h,mi);
    this->from_time=t1;
    cout<<"\t\t终点：";
    cin>>to;
    cout<<"\t\t到达时间（月 日 时 分）：";
    cin>>mo>>d>>h>>mi;
    time_inf t2(y,mo,d,h,mi);
    this->to_time=t2;
    cout<<endl<<endl;
    cin.clear();
    if(this->saveInf())
        return true;
    else
        return false;
}

/**删除列车信息
先提示用户输入要删除的列车次，然后从文件中读取列车
时刻信息，把此列车次的记录输出并编号，以编号来唯一
确定一条信息再提示用户输入要删除记录的序号。
最后利用文件操作删除相应记录。
**/
bool train_inf::trainDel()
{
    system("cls");
    menu::setColor(1);
    cout<<"\n\n    　    ────<<列  车  时  刻  信  息  删  除>>──── "<<endl<<endl;
    cout<<"\n\n请输入要删除的列车次：";
    string n;
    cin>>n;
    cout<<"\n\n列车"<<n<<"的相关信息如下：\n\n";

    ifstream in;
    int c=0,cnum=0;
    queue<train_inf> temp;
    train_inf t;

    try
    {
        in.open("data\\train.txt");
        if(in.fail())
            throw "文件错误！";
        }catch(string s){
            cout<<s<<endl;
            return false;
        }
    char ch=in.get();
    //将文件数据存入临时队列
    menu::showHead();
    while(!in.eof())
    {
        in>>t.name>>t.from>>t.from_time.year>>t.from_time.month>>t.from_time.day;
        in>>t.from_time.hour>>t.from_time.minute>>t.to>>t.to_time.year;
        in>>t.to_time.month>>t.to_time.day>>t.to_time.hour>>t.to_time.minute;
        temp.push(t);
        if(n.compare(t.name)==0)
        {
            cout<<"\t\t"<<++c;
            t.train_show();
        }
    }
    in.close();
    if(c==0)
    {
        menu::setColor(2);
        cout<<"\t\t未找到此列车！"<<endl;
        return false;
    }

    cout<<"请输入要删除的序号：";
    cin>>cnum;
    if(cnum<=0||cnum>c)
    {
        menu::setColor(2);
        cout<<"\t\t无此序号！"<<endl;
        return false;
    }

    ofstream of;
    try
    {
        of.open("data\\train.txt",ios_base::trunc);
        if(of.fail())
            throw "文件错误";
    }catch(string s){
        cout<<s<<endl;
        return false;
    }

    c=0;
    bool hasDel=false;
    while(!temp.empty())
    {
        /**判断是否是用户标记的要删除的那条记录
        用c来记录记录的编号**/
        t=temp.front();
        temp.pop();
        if(n.compare(t.getName())==0) c++;
        if(c==cnum&&!hasDel)
            hasDel=true;
        else
        {
            of<<endl<<t.getName()<<" "<<t.getFrom()<<" "<<t.getFTtime(1).getTi(1)<<" "<<t.getFTtime(1).getTi(2);
            of<<" "<<t.getFTtime(1).getTi(3)<<" "<<t.getFTtime(1).getTi(4)<<" "<<t.getFTtime(1).getTi(5);
            of<<" "<<t.getTo()<<" "<<t.getFTtime(2).getTi(1)<<" "<<t.getFTtime(2).getTi(2);
            of<<" "<<t.getFTtime(2).getTi(3)<<" "<<t.getFTtime(2).getTi(4)<<" "<<t.getFTtime(2).getTi(5);
        }
    }
    of.close();
    cin.clear();
    fflush(stdin);
    return true;
}

/**修改列车信息
确定列车次信息记录的方法与删除列车信息的过程一样，
也是通过将用户输入的列车次编号来唯一确定一条记录，
在通过文件操作进行删除。
**/
bool train_inf::trainChange()
{
    system("cls");
    menu::setColor(1);
    cout<<"\n\n    　    ────<<列  车  时  刻  信  息  修  改>>──── "<<endl<<endl;
    cout<<"\n\n请输入要修改的列车次：";
    string n;
    cin>>n;
    cout<<"\n\n列车"<<n<<"的相关信息如下：\n\n";

    ifstream in;
    int c=0,cnum=0;
    queue<train_inf> temp;
    train_inf t;

    try
    {
        in.open("data\\train.txt");
        if(in.fail())
            throw "文件错误！";
        }catch(string s){
            cout<<s<<endl;
            return false;
        }
    char ch=in.get();
    menu::showHead();
    while(!in.eof())
    {
        in>>t.name>>t.from>>t.from_time.year>>t.from_time.month>>t.from_time.day;
        in>>t.from_time.hour>>t.from_time.minute>>t.to>>t.to_time.year;
        in>>t.to_time.month>>t.to_time.day>>t.to_time.hour>>t.to_time.minute;
        temp.push(t);
        if(n.compare(t.getName())==0)
        {
            cout<<"\t\t"<<++c;
            t.train_show();
        }
    }
    cout<<endl<<endl;
    in.close();
    if(c==0)
    {
        menu::setColor(2);
        cout<<"\t\t未找到此列车信息！"<<endl;
        return false;
    }

    cout<<"请输入要修改的序号：";
    cin>>cnum;
    if(cnum<=0||cnum>c)
    {
        menu::setColor(2);
        cout<<"\t\t无此序号！"<<endl;
        return false;
    }
    ofstream of;
    try
    {
        of.open("data\\train.txt",ios_base::trunc);
        if(of.fail())
            throw "文件错误";
    }catch(string s){
        cout<<s<<endl;
        return false;
    }

    c=0;
    bool hasChanged=false;
    while(!temp.empty())
    {
        t=temp.front();
        temp.pop();
        if(n.compare(t.getName())==0) c++;
        /**若已经到用户标记的那条记录，提示用户重新输入
        列车次的各种信息。
        **/
        if(c==cnum&&!hasChanged)
        {
            string name;
            int mo,d,h,mi;
            int y=time_inf::getCurYear();

            cout<<"\t\t请重新输入信息"<<endl;
            cout<<"\t\t列车次：";
            cin>>name;
            of<<endl<<name<<" ";
            cout<<"\t\t出发地：";
            cin>>name;
            of<<name<<" ";
            cout<<"\t\t出发时间（月 日 时 分）：";
            cin>>mo>>d>>h>>mi;
            of<<y<<" "<<mo<<" "<<d<<" "<<h<<" "<<mi;
            cout<<"\t\t目的地：";
            cin>>name;
            of<<" "<<name;
            cout<<"\t\t到达时间（月 日 时 分）：";
            cin>>mo>>d>>h>>mi;
            of<<" "<<y<<" "<<mo<<" "<<d<<" "<<h<<" "<<mi;
            hasChanged=true;
        }
        else
        {
            of<<endl<<t.getName()<<" "<<t.getFrom()<<" "<<t.getFTtime(1).getTi(1)<<" "<<t.getFTtime(1).getTi(2);
            of<<" "<<t.getFTtime(1).getTi(3)<<" "<<t.getFTtime(1).getTi(4)<<" "<<t.getFTtime(1).getTi(5);
            of<<" "<<t.getTo()<<" "<<t.getFTtime(2).getTi(1)<<" "<<t.getFTtime(2).getTi(2);
            of<<" "<<t.getFTtime(2).getTi(3)<<" "<<t.getFTtime(2).getTi(4)<<" "<<t.getFTtime(2).getTi(5);
        }
    }
    menu::waitEnter();
    return true;
}

/**列车时刻查询
提示用户有选择地输入限制条件，可限制也可不限制。
根据实际情况，这里一共设置5个限制条件，列车次、
列车种类、出发地、目的地、出发时间。先将列车记录
存入临时队列，在利用各种限制条件对队列中的记录
进行删选，删除不符合搜索条件的，最后队列里剩下的
即为最终结果。
**/
bool train_inf::trainSearch()
{
    //int adjMax[100][100];
    system("cls");
    menu::setColor(1);
    cout<<"\n\n    　    ────<<列  车  时  刻  信  息  查  询>>──── "<<endl<<endl;
    cout<<"\t\t请输入查询条件，不限制输入^，时间输入-1"<<endl;
    string na,f,t;
    char k;
    int mo,d,h,mi;
    queue<train_inf> temp;
    /****/
    cout<<"\n\t\t列车次：";
    cin>>na;
    cout<<"\n\t\t列车种类：";
    cin>>k;
    cout<<"\n\t\t出发地：";
    cin>>f;
    cout<<"\n\t\t目的地：";
    cin>>t;
    cout<<"\n\t\t出发时间（月 日 时 分）：";
    cin>>mo>>d>>h>>mi;
    time_inf ft(time_inf::getCurYear(),mo,d,h,mi);

    if(cin.fail())
    {
        menu::setColor(2);
        cout<<"\t\t输入错误！"<<endl;
        return false;
    }

    ifstream in;
    try
    {
        in.open("data\\train.txt");
        if(in.fail())
            throw "文件错误！";
        }catch(string s){
            menu::setColor(2);
            cout<<"\t\t"<<s<<endl;
            return false;
        }
    //将各条记录存入临时队列
    char jg=in.get();
    if(jg!='\n')
    {
        menu::setColor(2);
        cout<<"\t\t请先输入列车信息！"<<endl;
        return false;
    }
    while(!in.eof())
    {
        string from,to;
        char name[20];
        int year,month,day,hour,minute;
        in>>name>>from>>year>>month>>day>>hour>>minute;
        time_inf ft(year,month,day,hour,minute);
        in>>to>>year>>month>>day>>hour>>minute;
        time_inf tt(year,month,day,hour,minute);
        train_inf train(from,to,name,ft,tt);
        temp.push(train);
    }
    in.close();


    /**以下几个if语句是对队列中的各条记录进行筛选**/
    if(na.compare("^")!=0)
    {
        trainSearchByName(na,temp);
        //cout<<"size:"<<temp.size()<<endl;
    }
    if(k!='^')
        trainSearchByKind(k,temp);
    if(mo!=-1)
        trainSearchByFTime(ft,temp);

    if(f.compare("^")!=0&&t.compare("^")!=0)
    {
        cout<<"\n\n\t\t查询结果如下：\n"<<endl;
        int c;
        if(!temp.empty())
            c=findMinPath(temp,f,t);
        else
            c=0;
        cout<<endl<<endl;
        if(c==0)
        {
            menu::setColor(2);
            cout<<"\t\t未查到相关信息！"<<endl;
            return false;
        }
        else
            return true;
    }
    else
    {
        menu::showHead();
        while(!temp.empty())
        {
            temp.front().train_show();
            temp.pop();
        }
    }
    fflush(stdin);

}

int train_inf::findNum(map<int,string> m,string s)
{
    int i=0;
    map<int,string>::iterator it;
    for(it=m.begin();it!=m.end();it++)
    {
        if(s.compare((*it).second)==0)
            return i;
        i++;
    }
}

/**乘车路线查询**/
int train_inf::findMinPath(queue<train_inf> q,string from,string to)
{
    set<string> s;
    queue<train_inf> temp=q;
    vector<train_inf> showV;
    queue<train_inf> showQ=q;
    map<int,string> n_city;
    while(!showQ.empty())
    {
        showV.push_back(showQ.front());
        showQ.pop();
    }
    int arcs[100][100],path[100][100]; // 存储邻接矩阵
    train_inf t;
    while(!q.empty())  //找出城市的个数，存入集合s
    {
        t=q.front();t.getFrom();
        string from=t.getFrom(),to=t.getTo();
        s.insert(from); s.insert(to);
        q.pop();
    }


    int n=0,i,j,k;
    /**将所有城市与相应的序号建立映射关系**/
    for(set<string>::iterator it=s.begin();it!=s.end();it++)
    {
        n_city[n++]=*it;
        //cout<<n-1<<":"<<*it<<endl;
    }

    /**建立邻接矩阵**/
    memset(arcs,0x3f3f3f3f,sizeof(arcs));
    while(!temp.empty())
    {
        t=temp.front();
        string from=t.getFrom(),to=t.getTo();
        int a=findNum(n_city,from);
        int b=findNum(n_city,to);
        arcs[a][b]=1;
        temp.pop();
    }


    /**初始化存储路径的矩阵**/
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(arcs[i][j]<MAX)
                path[i][j]=i;
            else
                path[i][j]=-1;

        }
        arcs[i][i]=0;
    }


    /**Floyd算法计算最短路径，任意两点间的最短路径**/
    for(k=0;k<n;k++)
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
            {
                if(arcs[i][k]<MAX&&arcs[k][j]<MAX&&arcs[i][j]>arcs[i][k]+arcs[k][j])//&&judgeTime(showV,n_city,i,k,j)
                {
                    arcs[i][j]=arcs[i][k]+arcs[k][j];
                    path[i][j]=path[k][j];
                }
            }

    /**根据出发地目的地输出乘车路线**/
    int fromN=findNum(n_city,from);
    int toN=findNum(n_city,to);
    if(arcs[fromN][toN]<MAX)
    {
        cout<<"\t\t最少换乘次数："<<arcs[fromN][toN]<<endl<<endl;
        int minPath[100],len=0,i,pre=toN;
        minPath[len++]=pre;
        while(pre!=fromN)
        {
            pre=path[fromN][pre];
            minPath[len++]=pre;
        }
        minPath[len]=pre;
        cout<<"\t\t建议乘车路径"<<endl<<endl;
        menu::showHead();
        for(i=len-1;i>0;i--)
        {
            string p=n_city[minPath[i]],nt=n_city[minPath[i-1]];
            //cout<<p<<"->"<<nt<<endl;
            for(j=0;j<showV.size();j++)
            {
                if(showV[j].getFrom().compare(p)==0&&showV[j].getTo().compare(nt)==0)
                {
                    cout<<"\t\t";
                    showV[j].train_show();
                    cout<<endl;
                }
            }
        }
        return j;
    }
    else
    {
        menu::setColor(2);
        cout<<"\t\t抱歉！未找到您的乘车路线。"<<endl;
        return 0;
    }
}

bool train_inf::judgeTime(vector<train_inf> v,map<int,string> m,int i,int k,int j)
{
    int t;
    train_inf inf1,inf2;
    string from=m[i],mid=m[k],to=m[j];

    for(t=0;t<v.size();t++)
    {
        string pre=v[t].getFrom(),nt=v[t].getTo();
        if(pre.compare(from)==0&&nt.compare(mid)==0)
        {
            inf1=v[t];
            break;
        }
    }

    for(t=0;t<v.size();t++)
    {
        string pre=v[t].getFrom(),nt=v[t].getTo();
        if(pre.compare(mid)==0&&nt.compare(to)==0)
        {
            inf2=v[t];
            break;
        }
    }
    if(inf1.getFTtime(2).compare(inf2.getFTtime(1))<0)
        return true;
    else
        return false;
}




/**筛选出列车名为name的记录，即从队列中删除名字不是name的记录**/
void train_inf::trainSearchByName(string name,queue<train_inf>& q)
{
    train_inf t;
    int i=0,v=q.size();

    while(i<=v&&!q.empty())
    {

        t=q.front();
        q.pop();
        if(name.compare(t.getName())==0)
        {
            q.push(t);
        }
        i++;
    }
}

/**删除队列中出发地不是f的记录**/
void train_inf::trainSearchByFrom(string f,queue<train_inf>& q)
{
    train_inf t;
    int i=0,v=q.size();
    while(i<=v&&!q.empty())
    {
        t=q.front();
        if(f.compare(t.getFrom())==0)
            q.push(t);
        q.pop();
        i++;
    }
}

/**删除队列中目的地不是t的记录**/
void train_inf::trainSearchByTo(string t,queue<train_inf>& q)
{
    train_inf tt;
    int i=0,v=q.size();
    while(i<=v&&!q.empty())
    {
        tt=q.front();
        if(t.compare(tt.getTo())==0)
            q.push(tt);
        q.pop();
        i++;
    }
}

/**删除队列中出发时间在ft之前的记录**/
void train_inf::trainSearchByFTime(time_inf ft,queue<train_inf>& q)
{
    train_inf t;
    int i=0,v=q.size();
    while(i<=v&&!q.empty())
    {
        t=q.front();

        int flag=ft.compare(t.getFTtime(1));
        if(flag<0)
            q.push(t);
        q.pop();
        i++;
    }
}

/**删除列车类别不是k的记录。列车次名字的第一个字符
为列车的类别。**/
void train_inf::trainSearchByKind(char k,queue<train_inf>& q)
{
    train_inf t;
    int i=0,v=q.size();
    while(i<=v&&!q.empty())
    {
        t=q.front();
        if(k==*t.getName())
            q.push(t);
        q.pop();
        i++;
    }
}
