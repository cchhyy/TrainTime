#ifndef ACCOUNT_H_INCLUDED
#define ACCOUNT_H_INCLUDED

#include <string>
using namespace std;
/**
账户类，用来表示账户的信息，用户名，密码，种类，联系电话，
常住地址。负责的功能：注册，登录，注销，修改密码，修改个人信息，
同时更新文件数据，获取用户名，种类，电话，地址，展示用户的相关信息。
**/
class account
{
private:
    string id,password,tel,address;
    int kind;               //用户种类  1：游客    2.管理员
    static string fileerr;
public:
    account();
    string getId(); //返回用户名
    int getKind(); //返回用户类别，是否是管理员
    string getPwd(); //返回用户密码
    string getTel(); //返回用户的联系电话
    string getAddr(); //返回用户的地址
    bool login(); //此用户登录
    bool logup(); //此用户注册
    bool logout(); //注销此用户
    bool changePwd(); //修改此用户密码
    bool changeInf(); //修改用户个人信息，选择修改三项
    bool save_account(); //保存此用户信息到文件
    void showAcc(); //输出此用户的各种信息
};
#endif // ACCOUNT_H_INCLUDED
