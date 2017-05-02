#include "menu.h"
#include "time.h"
#include <iostream>
#include <cstdio>
#include <windows.h>
using namespace std;

menu::menu(){}

/**չʾ�����˵�ѡ��
һ���˵��������˵��������˵���
����ʾ�û�����ѡ��**/
menu::menu(int k)
{
    this->kind=k;
    system("cls");
    setColor(1);
    if(kind==1)
    {
        cout<<"\n\n    ��    ��������<<��ӭʹ���г�ʱ�̲�ѯϵͳ>>�������� "<<endl<<endl;
        cout<<"          ������������������������������������"<<endl;
		cout<<"          ������������������������������������"<<endl;
		cout<<"          ����                            ����"<<endl;
		cout<<"          ����  1.    �û���¼            ����"<<endl;
		cout<<"          ����                            ����"<<endl;
        cout<<"          ����  2.    �û�ע��            ����"<<endl;
        cout<<"          ����                            ����"<<endl;
        cout<<"          ����  3.    ϵͳ����            ����"<<endl;
        cout<<"          ����                            ����"<<endl;
        cout<<"          ����  0.    �˳�ϵͳ            ����"<<endl;
        cout<<"          ����                            ����"<<endl;
		cout<<"          ������������������������������������"<<endl;
		cout<<"          ������������������������������������"<<endl;
		cout<<"\t\t\t\t\t��ǰʱ�䣺";
		time_inf::GetCurTime();
		cout<<endl;
		cout<<"     ����������ѡ��";
    }
    else if(kind==2)
    {
		cout<<"\n\n    ��    ��������<<��ӭʹ���г�ʱ�̲�ѯϵͳ>>�������� "<<endl;
        cout
		<<"     ��������������������������������������"<<endl
		<<"     ��������������������������������������"<<endl
		<<"     ����                              ����"<<endl
		<<"     ���� 1.    ¼���г�ʱ����Ϣ       ����"<<endl
		<<"     ����                              ����"<<endl
		<<"     ���� 2.    ɾ���г�ʱ����Ϣ       ����"<<endl
		<<"     ����                              ����"<<endl
		<<"     ���� 3.    �޸��г�ʱ����Ϣ       ����"<<endl
		<<"     ����                              ����"<<endl
		<<"     ���� 4.    ��ѯ�г�ʱ����Ϣ       ����"<<endl
		<<"     ����                              ����"<<endl
		<<"     ���� 5.    �˻�����               ����"<<endl
		<<"     ����                              ����"<<endl
		<<"     ���� 0.    �˳���¼               ����"<<endl
		<<"     ����                              ����"<<endl
		<<"     ��������������������������������������"<<endl
		<<"     ��������������������������������������"<<endl;
		cout<<"\t\t\t\t\t��ǰʱ�䣺";
		time_inf::GetCurTime();
		cout<<endl;
        cout<<"     ����������ѡ��";
    }
    else if(kind==3)
    {
        cout<<"\n\n    ��    ��������<<��     ��    ��    ��>>�������� "<<endl<<endl;
        cout
		<<"     ������������������������������������"<<endl
		<<"     ������������������������������������"<<endl
		<<"     ����                            ����"<<endl
		<<"     ���� 1.    ɾ�����˻�           ����"<<endl
		<<"     ����                            ����"<<endl
		<<"     ���� 2.    �޸�����             ����"<<endl
		<<"     ����                            ����"<<endl
		<<"     ���� 3.    �޸ĸ�����Ϣ         ����"<<endl
		<<"     ����                            ����"<<endl
		<<"     ���� 0.    ������һ��           ����"<<endl
		<<"     ����                            ����"<<endl
		<<"     ������������������������������������"<<endl
		<<"     ������������������������������������"<<endl;
		cout<<"\t\t\t\t\t��ǰʱ�䣺";
		time_inf::GetCurTime();
		cout<<endl;
        cout<<"     ����������ѡ��";
    }
    else if(kind==4)
    {
        cout<<"";
    }
}

/**��ʾ�û�����ѡ��
�����û������ѡ�񣬲���ֵ������������
**/
int menu::getChose()
{
    int choose;
    cin>>choose;
    if(cin.fail())
    {
        setColor(2);
        cout<<"\n\t\t�����ʽ����"<<endl;
        return -1;
    }
    else
        return choose;
}

/**�ȴ��û�����س���ʵ�����û��Ľ���**/
void menu::waitEnter()
{
    fflush(stdin);
    cin.clear();
    cout<<"\t���س�����";
    getchar();
}

/**��һ��ȷ�����������̡�**/
bool menu::isOk()
{
    cout<<"\n\t\tȷ������Y/N��";
    char c;
    cin>>c;
    if(c=='N')
        return false;
    else if(c=='Y')
        return true;
    else
    {
        setColor(2);
        cout<<"�����ʽ����"<<endl;
        menu::waitEnter();
        return false;
    }
}

/**��ʾ�����ʽ����**/
void menu::inputWarn()
{
    setColor(2);
    cout<<"\n\t\t�������"<<endl;
    menu::waitEnter();
}

/**
���ÿ���̨��ɫ��������Ϣ�ú�ɫ���壬
������Ϣ����ɫ���塣
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
    cout<<"\t\t���\t�г���\t������\t����ʱ��\tĿ�ĵ�\t����ʱ��"<<endl;
}

/**��ʾ������Ϣ**/
void menu::helpInf()
{
    system("cls");
    setColor(1);
    cout<<endl<<"====================<<�����г�ʱ�̲�ѯϵͳ>>===================="<<endl<<endl;
	cout<<"ʹ��˵��:"<<endl
	<<"\t1.�밴�ղ�����ʾ������ȷ�ĸ�ʽ,�Ա�֤ϵͳ��������;"<<endl<<endl
	<<"\t2.��һ��ʹ��ϵͳʱ��Ҫ��ע���˺ţ������޷�����;"<<endl<<endl
	<<"\t3.��ʹ�ù���Ա��¼ʱ,�ɽ��ж�ϵͳ�����в���;"<<endl<<endl
	<<"\t4.��ʹ���ο���ݵ�½ʱ,ֻ������Ͳ�ѯ�г�ʱ����Ϣ;"<<endl<<endl
	<<"\t5.��Ϣ���ı��ĵ���ʽ,�����ڱ�����data�ļ���Ŀ¼��,����ֱ�Ӵ򿪲鿴."<<endl<<endl
	<<"ϵͳ˵��:"<<endl
	<<"\t��ϵͳΪ�γ������Ʒ,���Լ��׵Ľ����г�ʱ�̲�ѯ,��ӭ�������ͽ���"<<endl<<endl
	<<"\tXXXXX��ѧXXXXѧԺXXXXXXX�� ѧ��XXXXXXXXX ������XXXXX   QQ:321783027\t "<<endl<<endl;
	setColor(2);
	menu::waitEnter();
}
