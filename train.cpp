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

/**�г���Ϣ�๹�캯��
���ṩ����������(f)��Ŀ�ĵ�(t)���г���(name)������ʱ��(ft)��
����ʱ��(tt)**/
train_inf::train_inf(string f,string t,char* n,time_inf ft,time_inf tt)
{
    from=f; to=t;
    strcpy(name,n);
    from_time=ft;
    to_time=tt;
}

/**���س�����**/
string train_inf::getFrom()
{
    return from;
}

/**����Ŀ�ĵ�**/
string train_inf::getTo()
{
    return to;
}

/**�����г���**/
char* train_inf::getName()
{
    return name;
}

/**���س���ʱ��򵽴�ʱ��**/
time_inf train_inf::getFTtime(int n)
{
    if(n==1)
        return from_time;
    else
        return to_time;
}

/**����г���Ϣ�������Ϣ**/
void train_inf::train_show()
{
    cout<<"\t"<<name<<"\t"<<from<<"\t"<<from_time.getTi(2)<<"��"<<from_time.getTi(3)<<"��";
    printf("%02d:%02d\t",from_time.getTi(4),from_time.getTi(5));
    cout<<to<<"\t"<<to_time.getTi(2)<<"��"<<to_time.getTi(3)<<"��"<<to_time.getTi(3)<<"��";
    printf("%02d:%02d\t",to_time.getTi(4),to_time.getTi(5));
}
/**
������Ϣ������ӵķ�ʽ���ļ�����ʾ�û�����
������Ϣ�����ж����ݺϷ��ԡ�ͨ���ļ��������
��ʽ�����ļ���������ɹ�������TRUE�����򷵻�FALSE��
**/
bool train_inf::saveInf()
{
    ofstream of;
    try
    {
        //����ӵķ�ʽ���ļ�
        of.open("data\\train.txt",ios_base::app);
        if(of.fail())
            throw "�ļ�����";
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

/**¼���г���Ϣ
��ʾ�û������г��ĸ�����Ϣ�������aveInf()
�������ֱ�����Ϣ���ļ����ɹ����浽�ļ�����TRUE��
����ʧ�ܷ���FALSE��
**/
bool train_inf::trainAdd()
{
    system("cls");
    menu::setColor(1);
    cout<<"\n\n    ��    ��������<<��  ��  ʱ  ��  ��  Ϣ  ¼  ��>>�������� "<<endl<<endl;
    int y,mo,d,h,mi;

    cout<<"\t\t�г��Σ�";
    cin>>name;
    cout<<"\t\t��㣺";
    cin>>from;
    cout<<"\t\t����ʱ�䣨�� �� ʱ �֣���";
    y=time_inf::getCurYear();
    cin>>mo>>d>>h>>mi;
    time_inf t1(y,mo,d,h,mi);
    this->from_time=t1;
    cout<<"\t\t�յ㣺";
    cin>>to;
    cout<<"\t\t����ʱ�䣨�� �� ʱ �֣���";
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

/**ɾ���г���Ϣ
����ʾ�û�����Ҫɾ�����г��Σ�Ȼ����ļ��ж�ȡ�г�
ʱ����Ϣ���Ѵ��г��εļ�¼�������ţ��Ա����Ψһ
ȷ��һ����Ϣ����ʾ�û�����Ҫɾ����¼����š�
��������ļ�����ɾ����Ӧ��¼��
**/
bool train_inf::trainDel()
{
    system("cls");
    menu::setColor(1);
    cout<<"\n\n    ��    ��������<<��  ��  ʱ  ��  ��  Ϣ  ɾ  ��>>�������� "<<endl<<endl;
    cout<<"\n\n������Ҫɾ�����г��Σ�";
    string n;
    cin>>n;
    cout<<"\n\n�г�"<<n<<"�������Ϣ���£�\n\n";

    ifstream in;
    int c=0,cnum=0;
    queue<train_inf> temp;
    train_inf t;

    try
    {
        in.open("data\\train.txt");
        if(in.fail())
            throw "�ļ�����";
        }catch(string s){
            cout<<s<<endl;
            return false;
        }
    char ch=in.get();
    //���ļ����ݴ�����ʱ����
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
        cout<<"\t\tδ�ҵ����г���"<<endl;
        return false;
    }

    cout<<"������Ҫɾ������ţ�";
    cin>>cnum;
    if(cnum<=0||cnum>c)
    {
        menu::setColor(2);
        cout<<"\t\t�޴���ţ�"<<endl;
        return false;
    }

    ofstream of;
    try
    {
        of.open("data\\train.txt",ios_base::trunc);
        if(of.fail())
            throw "�ļ�����";
    }catch(string s){
        cout<<s<<endl;
        return false;
    }

    c=0;
    bool hasDel=false;
    while(!temp.empty())
    {
        /**�ж��Ƿ����û���ǵ�Ҫɾ����������¼
        ��c����¼��¼�ı��**/
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

/**�޸��г���Ϣ
ȷ���г�����Ϣ��¼�ķ�����ɾ���г���Ϣ�Ĺ���һ����
Ҳ��ͨ�����û�������г��α����Ψһȷ��һ����¼��
��ͨ���ļ���������ɾ����
**/
bool train_inf::trainChange()
{
    system("cls");
    menu::setColor(1);
    cout<<"\n\n    ��    ��������<<��  ��  ʱ  ��  ��  Ϣ  ��  ��>>�������� "<<endl<<endl;
    cout<<"\n\n������Ҫ�޸ĵ��г��Σ�";
    string n;
    cin>>n;
    cout<<"\n\n�г�"<<n<<"�������Ϣ���£�\n\n";

    ifstream in;
    int c=0,cnum=0;
    queue<train_inf> temp;
    train_inf t;

    try
    {
        in.open("data\\train.txt");
        if(in.fail())
            throw "�ļ�����";
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
        cout<<"\t\tδ�ҵ����г���Ϣ��"<<endl;
        return false;
    }

    cout<<"������Ҫ�޸ĵ���ţ�";
    cin>>cnum;
    if(cnum<=0||cnum>c)
    {
        menu::setColor(2);
        cout<<"\t\t�޴���ţ�"<<endl;
        return false;
    }
    ofstream of;
    try
    {
        of.open("data\\train.txt",ios_base::trunc);
        if(of.fail())
            throw "�ļ�����";
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
        /**���Ѿ����û���ǵ�������¼����ʾ�û���������
        �г��εĸ�����Ϣ��
        **/
        if(c==cnum&&!hasChanged)
        {
            string name;
            int mo,d,h,mi;
            int y=time_inf::getCurYear();

            cout<<"\t\t������������Ϣ"<<endl;
            cout<<"\t\t�г��Σ�";
            cin>>name;
            of<<endl<<name<<" ";
            cout<<"\t\t�����أ�";
            cin>>name;
            of<<name<<" ";
            cout<<"\t\t����ʱ�䣨�� �� ʱ �֣���";
            cin>>mo>>d>>h>>mi;
            of<<y<<" "<<mo<<" "<<d<<" "<<h<<" "<<mi;
            cout<<"\t\tĿ�ĵأ�";
            cin>>name;
            of<<" "<<name;
            cout<<"\t\t����ʱ�䣨�� �� ʱ �֣���";
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

/**�г�ʱ�̲�ѯ
��ʾ�û���ѡ�����������������������Ҳ�ɲ����ơ�
����ʵ�����������һ������5�������������г��Ρ�
�г����ࡢ�����ء�Ŀ�ĵء�����ʱ�䡣�Ƚ��г���¼
������ʱ���У������ø������������Զ����еļ�¼
����ɾѡ��ɾ�����������������ģ���������ʣ�µ�
��Ϊ���ս����
**/
bool train_inf::trainSearch()
{
    //int adjMax[100][100];
    system("cls");
    menu::setColor(1);
    cout<<"\n\n    ��    ��������<<��  ��  ʱ  ��  ��  Ϣ  ��  ѯ>>�������� "<<endl<<endl;
    cout<<"\t\t�������ѯ����������������^��ʱ������-1"<<endl;
    string na,f,t;
    char k;
    int mo,d,h,mi;
    queue<train_inf> temp;
    /****/
    cout<<"\n\t\t�г��Σ�";
    cin>>na;
    cout<<"\n\t\t�г����ࣺ";
    cin>>k;
    cout<<"\n\t\t�����أ�";
    cin>>f;
    cout<<"\n\t\tĿ�ĵأ�";
    cin>>t;
    cout<<"\n\t\t����ʱ�䣨�� �� ʱ �֣���";
    cin>>mo>>d>>h>>mi;
    time_inf ft(time_inf::getCurYear(),mo,d,h,mi);

    if(cin.fail())
    {
        menu::setColor(2);
        cout<<"\t\t�������"<<endl;
        return false;
    }

    ifstream in;
    try
    {
        in.open("data\\train.txt");
        if(in.fail())
            throw "�ļ�����";
        }catch(string s){
            menu::setColor(2);
            cout<<"\t\t"<<s<<endl;
            return false;
        }
    //��������¼������ʱ����
    char jg=in.get();
    if(jg!='\n')
    {
        menu::setColor(2);
        cout<<"\t\t���������г���Ϣ��"<<endl;
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


    /**���¼���if����ǶԶ����еĸ�����¼����ɸѡ**/
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
        cout<<"\n\n\t\t��ѯ������£�\n"<<endl;
        int c;
        if(!temp.empty())
            c=findMinPath(temp,f,t);
        else
            c=0;
        cout<<endl<<endl;
        if(c==0)
        {
            menu::setColor(2);
            cout<<"\t\tδ�鵽�����Ϣ��"<<endl;
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

/**�˳�·�߲�ѯ**/
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
    int arcs[100][100],path[100][100]; // �洢�ڽӾ���
    train_inf t;
    while(!q.empty())  //�ҳ����еĸ��������뼯��s
    {
        t=q.front();t.getFrom();
        string from=t.getFrom(),to=t.getTo();
        s.insert(from); s.insert(to);
        q.pop();
    }


    int n=0,i,j,k;
    /**�����г�������Ӧ����Ž���ӳ���ϵ**/
    for(set<string>::iterator it=s.begin();it!=s.end();it++)
    {
        n_city[n++]=*it;
        //cout<<n-1<<":"<<*it<<endl;
    }

    /**�����ڽӾ���**/
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


    /**��ʼ���洢·���ľ���**/
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


    /**Floyd�㷨�������·�����������������·��**/
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

    /**���ݳ�����Ŀ�ĵ�����˳�·��**/
    int fromN=findNum(n_city,from);
    int toN=findNum(n_city,to);
    if(arcs[fromN][toN]<MAX)
    {
        cout<<"\t\t���ٻ��˴�����"<<arcs[fromN][toN]<<endl<<endl;
        int minPath[100],len=0,i,pre=toN;
        minPath[len++]=pre;
        while(pre!=fromN)
        {
            pre=path[fromN][pre];
            minPath[len++]=pre;
        }
        minPath[len]=pre;
        cout<<"\t\t����˳�·��"<<endl<<endl;
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
        cout<<"\t\t��Ǹ��δ�ҵ����ĳ˳�·�ߡ�"<<endl;
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




/**ɸѡ���г���Ϊname�ļ�¼�����Ӷ�����ɾ�����ֲ���name�ļ�¼**/
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

/**ɾ�������г����ز���f�ļ�¼**/
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

/**ɾ��������Ŀ�ĵز���t�ļ�¼**/
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

/**ɾ�������г���ʱ����ft֮ǰ�ļ�¼**/
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

/**ɾ���г������k�ļ�¼���г������ֵĵ�һ���ַ�
Ϊ�г������**/
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
