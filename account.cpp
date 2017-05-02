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

string account::fileerr="�ļ�����������Ӧ�ļ��Ƿ�������⡣";

account::account(){}

/**
�û���¼����ʾ�û������û��������롣��ֻ����ʽ��ȡ�洢�û��˻���Ϣ��account�ļ����������е�
������Ϣ�����ҵ�ƥ�����Ϣ��ȷ��Ϊ��ǰ���û�����¼�ɹ��������޷���¼��
**/
bool account::login()
{
    system("cls");
    menu::setColor(1);
    cout<<"\n\n    ��    ��������<<��     ��       ��       ¼>>�������� "<<endl<<endl;
    cout<<"\t\t�û�����";
    cin>>this->id;
    cout<<endl<<"\t\t���룺";
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
    /** �����洢�û���Ϣ���ļ��ж��û����������Ƿ���ȷ**/
    try
    {
        in.open("data\\account.txt");

        if(in.fail())
            throw "�ļ�����";
        else
        {
            char ch=in.get();
            while(!in.eof())
            {
                in>>i>>ps>>k>>t>>a;
                if(i==this->id)
                {
                    isExist=true;
                    //cout<<"���룺"<<ps<<endl;
                    if(ps.compare(this->password)==0)
                    {
                        /** ��������֤��ȷ�����û��ĸ�����Ϣ�����˶���**/
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
        cout<<"\n\n\t\t�û������ڣ�"<<endl;
        return false;
    }
    else
    {
        if(!isRight)
        {
            cout<<"\n\n\t\t�û��������벻ƥ�䣡"<<endl;
            return false;
        }
        else return true;
    }
}

//�����û���
string account::getId()
{
    return this->id;
}

//�����û����
int account::getKind()
{
    return this->kind;
}

/**
��ʾ�û�����ע����Ҫ�ĸ�����Ϣ������Ҫע�����Ա�˺ţ���ȡ����Ȩ�ޣ�
��Ҫ��һ����֤��ͨ������save_account���������˺���Ϣ��account.txt�ļ���
**/
bool account::logup() //�˺�ע��
{
    system("cls");
    menu::setColor(1);
    char p1[50],p2[50],c=' ';
    int len;
    cout<<"\n\n    ��    ��������<<��     ��       ע       ��>>�������� "<<endl<<endl;
    cout<<"\t\t�û�����";
    cin>>this->id;
    getchar();
    cout<<"\n\t\t���룺";
    len=0;
    while((c=getch())!='\r')
    {
        cout<<"*";
        p1[len++]=c;
    }
    p1[len]='\0';

    cout<<"\n\n\t\t����ȷ�ϣ�";
    len=0;
    c='1';
    while((c=getch())!='\r')
    {
        cout<<"*";
        p2[len++]=c;
    }
    p2[len]='\0';

    //�ж���������������Ƿ�һ��
    if(strcmp(p1,p2)!=0)
    {
        menu::setColor(2);
        cout<<"\n\n\t\t���벻һ�£�"<<endl;
        return false;
    }
    else
        password=p1;

    cout<<"\n\t\t�û����ࣨ1.�ο� 2.����Ա����";
    cin>>this->kind;
    /** ���û�ע�����Ա�˻�����Ҫ�ṩ�ض�����֤��**/
    if(this->kind==2)
    {
        cout<<"\t\t������ע�����Ա�������֤�룺";

        string s,r;
        cin>>s;
        /**��ȡ�ļ��е���֤��**/
        ifstream in("data\\manager.txt");
        in>>r;

        if(r.compare(s)!=0) //�ж���֤���Ƿ���ȷ
        {
            menu::setColor(2);
            cout<<"\t\t��֤�����"<<endl;
            return false;
        }
    }

    cout<<"\t\t��ϵ�绰��";
    cin>>this->tel;

    cout<<"\t\t��ס�أ�";
    cin>>this->address;

    string i,p,cot,ad;
    int k;
    /**�жϸ��û��Ƿ��Ѿ�����**/
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
                /**���ļ��д�������û�����ͬ���û��������ܽ���ע��
                ����ʾ�û�����ͬ**/
                if(i.compare(id)==0)
                {
                    menu::setColor(2);
                    cout<<"\n\t\t���û��Ѵ��ڣ�"<<endl;
                    return false;
                }
            }
    }catch(string s){
        cout<<s<<endl;
        return false;
        }
    if(menu::isOk()==true)
    {
        /**���ñ��溯������ע�����Ϣ����������Ӧ��ֵ**/
        if(save_account())
            return true;
        else
            return false;
    }
    else
        return false;
}

/**
�ڵ�¼״̬��ע�����ڵ�¼���˺ţ�
��account.txt�ļ���ɾ����Ӧ���˺���Ϣ��
**/
bool account::logout()
{
    system("cls");
    menu::setColor(1);
    cout<<"\n\n    ��    ��������<<��     ��       ɾ        ��>>�������� "<<endl;
    showAcc();
    //�ȴ��û���һ��ȷ��
    cout<<"\t\t���û�����ɾ��";
    /**if(menu::isOk()==false)
    {
        menu::setColor(2);
        cout<<"\t\t�û�ע��ʧ�ܣ�"<<endl;
        return false;
    }����**/
    queue<account> temp; //����һ�����������洢��ʱ�Ķ���
    account a;
    string i,p;
    int k;
    ifstream in;
    ofstream of;
    try
    {
        in.open("data\\account.txt");
        if(in.fail())
            throw "�ļ�����";
        else
        {
            char ch=in.get();
            while(!in.eof())
            {
                /**�����ȡ��һ����¼���û�������û�����һ��,
                �򽫼�¼�����**/
                in>>a.id>>a.password>>a.kind>>a.tel>>a.address;
                //cout<<endl<<i<<" "<<this->id<<endl;
                if(a.id!=this->id)
                temp.push(a);
            }
            in.close();
        }
        /**���ļ���trunc�ķ�ʽ���Ƚ��ļ���ԭ�����������**/
        of.open("data\\account.txt",ios_base::trunc);

        if(of.fail())
            throw "�ļ�����";
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
��������ֲ����󣬶����ݽ��б��档
�ֱ����Ӻ��޸��������͵Ĳ������д洢���ݡ�
**/
bool account::save_account()
{
    ifstream in;
    queue<account> temp;
    /**������Ǹ��û����ļ����Ƿ��Ѿ�����**/
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
    /**�����м�¼������ʱ���У����ж��û��Ƿ��Ѿ�����**/
    while(!in.eof())
    {
        in>>a.id>>a.password>>a.kind>>a.tel>>a.address;
        if(a.id==this->id) isExist=1;
        temp.push(a);
    }
    in.close();

    ofstream of;

    /**�����û��Ѿ����ڣ�����жԴ��û����޸Ĳ���**/
    if(isExist)
    {
        try
        {
            /**�޸Ĳ���Ҫ�Ƚ�ԭ�ļ��е����ݸ��ǣ�Ȼ��д��**/
            of.open("data\\account.txt",ios_base::trunc);
            if(of.fail())
                throw fileerr;
        }catch(string s){
            cout<<s<<endl;
            return false;
        }

        while(!temp.empty())
        {
            /**�������е��û�������û�����ͬʱ�������µ��û���Ϣ
            ������ͬ���������ʱ�����е��˻���Ϣ**/
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
    /**���û����ļ��У��򽫴���Ϣ��ӵ��ļ���**/
    else
    {
        try
        {
            of.open("data\\account.txt",ios_base::app); //����ӷ�ʽ���ļ�
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
�ڵ�¼״̬���������޸ģ���ʾ������ԭʼ���룬�����������룬
������ȷ�ϲ�����save_account���档������������ַ�ȫ����*��ʾ��
**/
bool account::changePwd()
{
    system("cls");
    menu::setColor(1);
    cout<<"\n\n    ��    ��������<<��     ��       ��       ��>>�������� \n\n"<<endl;
    cout<<"\t\t������ԭʼ���룺";

    int len=0;
    char oldP[50],n1[50],n2[50],c;
    //����ԭʼ����
    while((c=getch())!='\r')
    {
        cout<<"*";
        oldP[len++]=c;
    }
    oldP[len]='\0';

    //�Ƚ������������˶��������
    if(password.compare(oldP)!=0)
    {
        menu::setColor(2);
        cout<<"\n\n\t\tԭʼ�����������\n\n";
        return false;
    }

    /**���������벢��һ��ȷ��**/
    cout<<"\n\n\t\t���������룺";
    len=0;
    while((c=getch())!='\r')
    {
        cout<<"*";
        n1[len++]=c;
    }
    n1[len]='\0';

    cout<<"\n\n\t\t�ٴ��������룺";
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
        cout<<"\n\n\t\t���벻һ�£�";
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
�޸ĸ�����Ϣ����¼״̬�¶Ը��ָ�����Ϣ�����޸ġ�
���������ṩ�˵����û����档
**/
bool account::changeInf()
{
    system("cls");
    menu::setColor(1);
    cout<<"\n\n    ��    ��������<<��   ��   ��   Ϣ   ��   ��>�������� \n\n"<<endl;
            cout<<"          ������������������������������������"<<endl;
		cout<<"          ������������������������������������"<<endl;
		cout<<"          ����                            ����"<<endl;
		cout<<"          ����  1.    �޸���ϵ�绰        ����"<<endl;
		cout<<"          ����                            ����"<<endl;
        cout<<"          ����  2.    �޸ĳ�ס��ַ        ����"<<endl;
        cout<<"          ����                            ����"<<endl;
        cout<<"          ����  0.    ����                ����"<<endl;
        cout<<"          ����                            ����"<<endl;
		cout<<"          ������������������������������������"<<endl;
		cout<<"          ������������������������������������"<<endl;
		cout<<"\n\n\t\t\t\t";
		time_inf::GetCurTime();
		cout<<endl;
		int c;

		cout<<"\t\t����������ѡ��";
		cin>>c;

		switch(c)
		{
        case 1:
            cout<<"\t\t����ǰ��ϵ�绰��"<<this->getTel()<<endl;
            cout<<"\t\t�޸�Ϊ��";
            cin>>this->tel;
            break;
        case 2:
            cout<<"\t\t����ǰ��ס��ַ��"<<this->getAddr()<<endl;
            cout<<"\t\t�޸�Ϊ��";
            cin>>this->address;
            break;
        default:
            cout<<"\t\t�������"<<endl;
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
/**չʾ�û��������Ϣ**/
void account::showAcc()
{
    if(this->kind==1)
        cout<<"\n\n�οͣ�";
    else
        cout<<"\n\n����Ա��";
    cout<<this->id;
}
