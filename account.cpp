#include "account.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <cstring>
#include <queue>
#include <windows.h>
#include <sstream>
#include "menu.h"
#include "time.h"
using namespace std;

string account::fileerr="文件错误！请检查相应文件是否出现问题。";

account::account(){}

/**
用户登录：提示用户输入用户名，密码。以只读方式读取存储用户账户信息的account文件，遍历其中的
各条信息，若找到匹配的信息，确定为当前的用户，登录成功；否则无法登录。
**/
bool account::login()
{
    system("cls");
    menu::setColor(1);
    cout<<"\n\n    　    ────<<用     户       登       录>>──── "<<endl<<endl;
    cout<<"\t\t用户名：";
    cin>>this->id;
    cout<<endl<<"\t\t密码：";
    int len=0,k;
    char p[50],c;
    string i,ps,t,a;
    while((c=getch())!='\r')
    {
        p[len++]=c;
        cout<<"*";
    }
    p[len]='\0';

    this->password=p;
    ifstream in;
    bool isExist=0,isRight=0;
    /** 遍历存储用户信息的文件判断用户名与密码是否正确**/
    try
    {
        in.open("data\\account.txt");

        if(in.fail())
            throw "文件错误！";
        else
        {
            char ch=in.get();
            while(!in.eof())
            {
                in>>i>>ps>>k>>t>>a;
                if(i==this->id)
                {
                    isExist=true;
                    //cout<<"密码："<<ps<<endl;
                    if(ps.compare(this->password)==0)
                    {
                        /** 若密码验证正确，将用户的各个信息赋给此对象**/
                        isRight=true;
                        this->kind=k;
                        this->tel=t;
                        this->address=a;
                    }
                }
            }
            in.close();
        }
    }catch(string s){
        cout<<s<<endl;
        return false;
    }
    menu::setColor(2);
    if(!isExist)
    {
        cout<<"\n\n\t\t用户不存在！"<<endl;
        return false;
    }
    else
    {
        if(!isRight)
        {
            cout<<"\n\n\t\t用户名与密码不匹配！"<<endl;
            return false;
        }
        else return true;
    }
}

//返回用户名
string account::getId()
{
    return this->id;
}

//返回用户类别
int account::getKind()
{
    return this->kind;
}

/**
提示用户输入注册需要的各种信息。若需要注册管理员账号，获取更大权限，
需要进一步验证。通过调用save_account函数保存账号信息到account.txt文件。
**/
bool account::logup() //账号注册
{
    system("cls");
    menu::setColor(1);
    char p1[50],p2[50],c=' ';
    int len;
    cout<<"\n\n    　    ────<<用     户       注       册>>──── "<<endl<<endl;
    cout<<"\t\t用户名：";
    cin>>this->id;
    getchar();
    cout<<"\n\t\t密码：";
    len=0;
    while((c=getch())!='\r')
    {
        cout<<"*";
        p1[len++]=c;
    }
    p1[len]='\0';

    cout<<"\n\n\t\t密码确认：";
    len=0;
    c='1';
    while((c=getch())!='\r')
    {
        cout<<"*";
        p2[len++]=c;
    }
    p2[len]='\0';

    //判断两次输入的密码是否一致
    if(strcmp(p1,p2)!=0)
    {
        menu::setColor(2);
        cout<<"\n\n\t\t密码不一致！"<<endl;
        return false;
    }
    else
        password=p1;

    cout<<"\n\t\t用户种类（1.游客 2.管理员）：";
    cin>>this->kind;
    /** 若用户注册管理员账户，需要提供特定的验证码**/
    if(this->kind==2)
    {
        cout<<"\t\t请输入注册管理员所需的验证码：";

        string s,r;
        cin>>s;
        /**读取文件中的验证码**/
        ifstream in("data\\manager.txt");
        in>>r;

        if(r.compare(s)!=0) //判断验证码是否正确
        {
            menu::setColor(2);
            cout<<"\t\t验证码错误！"<<endl;
            return false;
        }
    }

    cout<<"\t\t联系电话：";
    cin>>this->tel;

    cout<<"\t\t常住地：";
    cin>>this->address;

    string i,p,cot,ad;
    int k;
    /**判断该用户是否已经存在**/
    try
    {
        ifstream fi("data\\account.txt");
        if(fi.fail())
            throw fileerr;
        else
            char ch=fi.get();
            while(!fi.eof())
            {
                fi>>i>>p>>k>>cot>>ad;
                /**若文件中存在与此用户名相同的用户名，则不能进行注册
                并提示用户名相同**/
                if(i.compare(id)==0)
                {
                    menu::setColor(2);
                    cout<<"\n\t\t该用户已存在！"<<endl;
                    return false;
                }
            }
    }catch(string s){
        cout<<s<<endl;
        return false;
        }
    if(menu::isOk()==true)
    {
        /**调用保存函数保存注册的信息，并返回相应的值**/
        if(save_account())
            return true;
        else
            return false;
    }
    else
        return false;
}

/**
在登录状态下注销正在登录的账号，
从account.txt文件中删除对应的账号信息。
**/
bool account::logout()
{
    system("cls");
    menu::setColor(1);
    cout<<"\n\n    　    ────<<用     户       删        除>>──── "<<endl;
    showAcc();
    //等待用户进一步确认
    cout<<"\t\t本用户将被删除";
    /**if(menu::isOk()==false)
    {
        menu::setColor(2);
        cout<<"\t\t用户注销失败！"<<endl;
        return false;
    }多余**/
    queue<account> temp; //声明一个队列用来存储临时的对象
    account a;
    string i,p;
    int k;
    ifstream in;
    ofstream of;
    try
    {
        in.open("data\\account.txt");
        if(in.fail())
            throw "文件错误！";
        else
        {
            char ch=in.get();
            while(!in.eof())
            {
                /**如果读取的一条记录的用户名与此用户名不一致,
                则将记录入队列**/
                in>>a.id>>a.password>>a.kind>>a.tel>>a.address;
                //cout<<endl<<i<<" "<<this->id<<endl;
                if(a.id!=this->id)
                temp.push(a);
            }
            in.close();
        }
        /**打开文件用trunc的方式，先将文件中原来的数据清除**/
        of.open("data\\account.txt",ios_base::trunc);

        if(of.fail())
            throw "文件错误！";
        else
        {
            while(!temp.empty())
            {
                account t=temp.front();
                of<<endl<<t.getId()<<" "<<t.getPwd()<<" "<<t.getKind()<<" ";
                of<<t.getTel()<<" "<<t.getAddr();
                temp.pop();
            }
            of.close();
            return true;
        }
        }catch(string s){
            cout<<s<<endl;
            return false;
        }
}

/**
进行完各种操作后，对数据进行保存。
分别对添加和修改两种类型的操作进行存储数据。
**/
bool account::save_account()
{
    ifstream in;
    queue<account> temp;
    /**用来标记该用户在文件中是否已经存在**/
    bool isExist=0;
    account a;

    try
    {
        in.open("data\\account.txt");
        if(in.fail())
            throw fileerr;
        }catch(string s){
            cout<<s<<endl;
            return false;
        }
    char ch=in.get();
    /**将所有记录存入临时队列，并判断用户是否已经存在**/
    while(!in.eof())
    {
        in>>a.id>>a.password>>a.kind>>a.tel>>a.address;
        if(a.id==this->id) isExist=1;
        temp.push(a);
    }
    in.close();

    ofstream of;

    /**若果用户已经存在，则进行对此用户的修改操作**/
    if(isExist)
    {
        try
        {
            /**修改操作要先将原文件中的数据覆盖，然后写入**/
            of.open("data\\account.txt",ios_base::trunc);
            if(of.fail())
                throw fileerr;
        }catch(string s){
            cout<<s<<endl;
            return false;
        }

        while(!temp.empty())
        {
            /**当队列中的用户名与此用户名相同时，存入新的用户信息
            若不相同，则存入临时队列中的账户信息**/
            if(temp.front().id==this->id)
            {
                of<<endl<<this->id<<" "<<this->password<<" "<<this->kind<<" ";
                of<<this->tel<<" "<<this->address;
            }
            else
            {
                of<<endl<<temp.front().id<<" "<<temp.front().password<<" "<<temp.front().kind;
                of<<" "<<temp.front().tel<<" "<<temp.front().address;
            }
            temp.pop();
        }
        of.close();
        return true;
    }
    /**若用户在文件中，则将此信息添加到文件中**/
    else
    {
        try
        {
            of.open("data\\account.txt",ios_base::app); //以添加方式打开文件
            if(of.fail())
                throw fileerr;
        }catch(string s){
            cout<<s<<endl;
            return false;
        }
        of<<endl<<this->id<<" "<<this->password<<" "<<this->kind<<" "<<this->tel<<" "<<this->address;
        of.close();
        return true;
    }
}

/**
在登录状态进行密码修改，提示先输入原始密码，在输入新密码，
并二次确认并调用save_account保存。密码输入过程字符全部用*显示。
**/
bool account::changePwd()
{
    system("cls");
    menu::setColor(1);
    cout<<"\n\n    　    ────<<密     码       修       改>>──── \n\n"<<endl;
    cout<<"\t\t请输入原始密码：";

    int len=0;
    char oldP[50],n1[50],n2[50],c;
    //输入原始密码
    while((c=getch())!='\r')
    {
        cout<<"*";
        oldP[len++]=c;
    }
    oldP[len]='\0';

    //比较输入的密码与此对象的密码
    if(password.compare(oldP)!=0)
    {
        menu::setColor(2);
        cout<<"\n\n\t\t原始密码输入错误！\n\n";
        return false;
    }

    /**输入新密码并进一步确定**/
    cout<<"\n\n\t\t输入新密码：";
    len=0;
    while((c=getch())!='\r')
    {
        cout<<"*";
        n1[len++]=c;
    }
    n1[len]='\0';

    cout<<"\n\n\t\t再次输入密码：";
    len=0;
    while((c=getch())!='\r')
    {
        cout<<"*";
        n2[len++]=c;
    }
    n2[len]='\0';

    if(strcmp(n1,n2)!=0)
    {
        menu::setColor(2);
        cout<<"\n\n\t\t密码不一致！";
        menu::waitEnter();
        return false;
    }
    this->password=n1;
    if(this->save_account())
        return true;
    else
        return false;
}

/**
修改个人信息。登录状态下对各种个人信息进行修改。
函数本身提供菜单的用户界面。
**/
bool account::changeInf()
{
    system("cls");
    menu::setColor(1);
    cout<<"\n\n    　    ────<<个   人   信   息   修   改>──── \n\n"<<endl;
            cout<<"          ┌────────────────┐"<<endl;
		cout<<"          │┌──────────────┐│"<<endl;
		cout<<"          ││                            ││"<<endl;
		cout<<"          ││  1.    修改联系电话        ││"<<endl;
		cout<<"          ││                            ││"<<endl;
        cout<<"          ││  2.    修改常住地址        ││"<<endl;
        cout<<"          ││                            ││"<<endl;
        cout<<"          ││  0.    返回                ││"<<endl;
        cout<<"          ││                            ││"<<endl;
		cout<<"          │└──────────────┘│"<<endl;
		cout<<"          └────────────────┘"<<endl;
		cout<<"\n\n\t\t\t\t";
		time_inf::GetCurTime();
		cout<<endl;
		int c;

		cout<<"\t\t请输入您的选择：";
		cin>>c;

		switch(c)
		{
        case 1:
            cout<<"\t\t您当前联系电话："<<this->getTel()<<endl;
            cout<<"\t\t修改为：";
            cin>>this->tel;
            break;
        case 2:
            cout<<"\t\t您当前常住地址："<<this->getAddr()<<endl;
            cout<<"\t\t修改为：";
            cin>>this->address;
            break;
        default:
            cout<<"\t\t输入错误！"<<endl;
		}

        if(this->save_account())
            return true;
        else
            return false;
}

string account::getAddr()
{
    return address;
}

string account::getTel()
{
    return tel;
}

string account::getPwd()
{
    return this->password;
}
/**展示用户的相关信息**/
void account::showAcc()
{
    if(this->kind==1)
        cout<<"\n\n游客：";
    else
        cout<<"\n\n管理员：";
    cout<<this->id;
}
