#ifndef ACCOUNT_H_INCLUDED
#define ACCOUNT_H_INCLUDED

#include <string>
using namespace std;
/**
�˻��࣬������ʾ�˻�����Ϣ���û��������룬���࣬��ϵ�绰��
��ס��ַ������Ĺ��ܣ�ע�ᣬ��¼��ע�����޸����룬�޸ĸ�����Ϣ��
ͬʱ�����ļ����ݣ���ȡ�û��������࣬�绰����ַ��չʾ�û��������Ϣ��
**/
class account
{
private:
    string id,password,tel,address;
    int kind;               //�û�����  1���ο�    2.����Ա
    static string fileerr;
public:
    account();
    string getId(); //�����û���
    int getKind(); //�����û�����Ƿ��ǹ���Ա
    string getPwd(); //�����û�����
    string getTel(); //�����û�����ϵ�绰
    string getAddr(); //�����û��ĵ�ַ
    bool login(); //���û���¼
    bool logup(); //���û�ע��
    bool logout(); //ע�����û�
    bool changePwd(); //�޸Ĵ��û�����
    bool changeInf(); //�޸��û�������Ϣ��ѡ���޸�����
    bool save_account(); //������û���Ϣ���ļ�
    void showAcc(); //������û��ĸ�����Ϣ
};
#endif // ACCOUNT_H_INCLUDED
