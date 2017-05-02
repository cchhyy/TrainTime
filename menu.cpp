#include "menu.h"
#include "time.h"
#include <iostream>
#include <cstdio>
#include <windows.h>
using namespace std;

menu::menu(){}

/**展示各级菜单选项
一级菜单，二级菜单，三级菜单，
并提示用户输入选择**/
menu::menu(int k)
{
    this->kind=k;
    system("cls");
    setColor(1);
    if(kind==1)
    {
        cout<<"\n\n    　    ────<<欢迎使用列车时刻查询系统>>──── "<<endl<<endl;
        cout<<"          ┌────────────────┐"<<endl;
		cout<<"          │┌──────────────┐│"<<endl;
		cout<<"          ││                            ││"<<endl;
		cout<<"          ││  1.    用户登录            ││"<<endl;
		cout<<"          ││                            ││"<<endl;
        cout<<"          ││  2.    用户注册            ││"<<endl;
        cout<<"          ││                            ││"<<endl;
        cout<<"          ││  3.    系统帮助            ││"<<endl;
        cout<<"          ││                            ││"<<endl;
        cout<<"          ││  0.    退出系统            ││"<<endl;
        cout<<"          ││                            ││"<<endl;
		cout<<"          │└──────────────┘│"<<endl;
		cout<<"          └────────────────┘"<<endl;
		cout<<"\t\t\t\t\t当前时间：";
		time_inf::GetCurTime();
		cout<<endl;
		cout<<"     请输入您的选择：";
    }
    else if(kind==2)
    {
		cout<<"\n\n    　    ────<<欢迎使用列车时刻查询系统>>──── "<<endl;
        cout
		<<"     ┌─────────────────┐"<<endl
		<<"     │┌───────────────┐│"<<endl
		<<"     ││                              ││"<<endl
		<<"     ││ 1.    录入列车时刻信息       ││"<<endl
		<<"     ││                              ││"<<endl
		<<"     ││ 2.    删除列车时刻信息       ││"<<endl
		<<"     ││                              ││"<<endl
		<<"     ││ 3.    修改列车时刻信息       ││"<<endl
		<<"     ││                              ││"<<endl
		<<"     ││ 4.    查询列车时刻信息       ││"<<endl
		<<"     ││                              ││"<<endl
		<<"     ││ 5.    账户管理               ││"<<endl
		<<"     ││                              ││"<<endl
		<<"     ││ 0.    退出登录               ││"<<endl
		<<"     ││                              ││"<<endl
		<<"     │└───────────────┘│"<<endl
		<<"     └─────────────────┘"<<endl;
		cout<<"\t\t\t\t\t当前时间：";
		time_inf::GetCurTime();
		cout<<endl;
        cout<<"     请输入您的选择：";
    }
    else if(kind==3)
    {
        cout<<"\n\n    　    ────<<账     户    管    理>>──── "<<endl<<endl;
        cout
		<<"     ┌────────────────┐"<<endl
		<<"     │┌──────────────┐│"<<endl
		<<"     ││                            ││"<<endl
		<<"     ││ 1.    删除此账户           ││"<<endl
		<<"     ││                            ││"<<endl
		<<"     ││ 2.    修改密码             ││"<<endl
		<<"     ││                            ││"<<endl
		<<"     ││ 3.    修改个人信息         ││"<<endl
		<<"     ││                            ││"<<endl
		<<"     ││ 0.    返回上一级           ││"<<endl
		<<"     ││                            ││"<<endl
		<<"     │└──────────────┘│"<<endl
		<<"     └────────────────┘"<<endl;
		cout<<"\t\t\t\t\t当前时间：";
		time_inf::GetCurTime();
		cout<<endl;
        cout<<"     请输入您的选择：";
    }
    else if(kind==4)
    {
        cout<<"";
    }
}

/**提示用户输入选择
接受用户输入的选择，并将值传到主函数。
**/
int menu::getChose()
{
    int choose;
    cin>>choose;
    if(cin.fail())
    {
        setColor(2);
        cout<<"\n\t\t输入格式错误！"<<endl;
        return -1;
    }
    else
        return choose;
}

/**等待用户输入回车，实现与用户的交互**/
void menu::waitEnter()
{
    fflush(stdin);
    cin.clear();
    cout<<"\t按回车继续";
    getchar();
}

/**进一步确定，交互过程。**/
bool menu::isOk()
{
    cout<<"\n\t\t确定？（Y/N）";
    char c;
    cin>>c;
    if(c=='N')
        return false;
    else if(c=='Y')
        return true;
    else
    {
        setColor(2);
        cout<<"输入格式错误！"<<endl;
        menu::waitEnter();
        return false;
    }
}

/**提示输入格式错误**/
void menu::inputWarn()
{
    setColor(2);
    cout<<"\n\t\t输入错误！"<<endl;
    menu::waitEnter();
}

/**
设置控制台颜色，错误信息用红色字体，
正常信息用绿色字体。
**/
void menu::setColor(int i)
{
    //if(i==1)
        //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|BACKGROUND_BLUE);
    //else
        //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|BACKGROUND_BLUE);
}

void menu::showHead()
{
    cout<<"\t\t序号\t列车次\t出发地\t出发时间\t目的地\t到达时间"<<endl;
}

/**显示帮助信息**/
void menu::helpInf()
{
    system("cls");
    setColor(1);
    cout<<endl<<"====================<<关于列车时刻查询系统>>===================="<<endl<<endl;
	cout<<"使用说明:"<<endl
	<<"\t1.请按照操作提示输入正确的格式,以保证系统正常运行;"<<endl<<endl
	<<"\t2.第一次使用系统时，要先注册账号，否则无法进入;"<<endl<<endl
	<<"\t3.当使用管理员登录时,可进行对系统的所有操作;"<<endl<<endl
	<<"\t4.当使用游客身份登陆时,只能浏览和查询列车时刻信息;"<<endl<<endl
	<<"\t5.信息用文本文档格式,保存在本程序data文件夹目录下,可以直接打开查看."<<endl<<endl
	<<"系统说明:"<<endl
	<<"\t本系统为课程设计作品,可以简易的进行列车时刻查询,欢迎提出意见和建议"<<endl<<endl
	<<"\tXXXXX大学XXXX学院XXXXXXX班 学号XXXXXXXXX 姓名：XXXXX   QQ:321783027\t "<<endl<<endl;
	setColor(2);
	menu::waitEnter();
}
