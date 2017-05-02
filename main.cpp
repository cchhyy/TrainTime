/**         列车时刻查询系统（支撑目标1、2、3）
1.具有不同类型的列车类的描述     2.有列表时刻表类的描述
3.能完成时刻表的输入、查询、保存等功能    4.多样化的对象建模方式
**/
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<time.h>
#include<windows.h>
#include "account.h"
#include "train.h"
#include "menu.h"
using namespace std;

int main()
{
    int run1=1,run2=1,run3=1,n;
    int choose1,choose2,choose3;
    account A;

    while(run1)
    {
        cin.clear();fflush(stdin);
        menu m1(1);
        choose1=m1.getChose();

        switch(choose1)
        {
        case 1:     /**  用户登录  **/
            run2=1;
            if(!A.login()) run2=0;
            else cout<<"\n\n\t\t登录成功！"<<endl;
            menu::waitEnter();
            while(run2)
            {
                cin.clear();fflush(stdin);
                menu m2(2);
                choose2=m2.getChose();
                train_inf t;
                bool f;
                switch(choose2)
                {
                case 1:      /**增**/
                    if(A.getKind()!=2)
                    {
                        menu::setColor(2);
                        cout<<"\t\t您无此权限！"<<endl;
                        menu::waitEnter();
                        break;
                    }
                    cout<<"\n\n\t\t输入要录入的数量：";
                    cin>>n;
                    while(n--)
                    {
                        if(!t.trainAdd())
                        {
                            menu::setColor(2);
                            cout<<"\t\t录入错误！"<<endl;
                            break;
                        }
                        cin.clear();fflush(stdin);
                        if(n!=0)
                        {
                            cout<<"\t\t按回车录入下一条记录"<<endl;
                            getchar();
                        }
                    }
                    menu::setColor(2);
                    cout<<"\t\t录入结束"<<endl;
                    menu::waitEnter();
                    break;
                case 2:      /**  删 **/
                    cin.clear();fflush(stdin);
                    if(A.getKind()!=2)
                    {
                        menu::setColor(2);
                        cout<<"\t\t您无此权限！"<<endl;
                        menu::waitEnter();
                        break;
                    }
                    f=t.trainDel();
                    if(f==true&&menu::isOk())
                    {
                        cin.clear();fflush(stdin);
                        menu::setColor(2);
                        cout<<"\t\t删除成功！"<<endl;
                        menu::waitEnter();
                    }
                    else
                    {
                        cin.clear();fflush(stdin);
                        menu::setColor(2);
                        cout<<"\t\t删除失败！"<<endl;
                        menu::waitEnter();
                    }
                    break;
                case 3:      /**  改  **/
                    if(A.getKind()!=2)
                    {
                        menu::setColor(2);
                        cout<<"\t\t您无此权限！"<<endl;
                        menu::waitEnter();
                        break;
                    }
                    f=t.trainChange();
                    if(f==true)
                    {
                        menu::setColor(2);
                        cout<<"\t\t修改成功！"<<endl;
                        menu::waitEnter();
                    }
                    else
                    {
                        menu::setColor(2);
                        cout<<"\t\t修改失败！"<<endl;
                        menu::waitEnter();
                    }
                    break;
                case 4:      /**  查  **/
                    f=t.trainSearch();
                    if(f==true)
                    {
                        menu::setColor(2);
                        cout<<"\n\t\t查找成功！"<<endl;
                        menu::waitEnter();
                    }
                    else
                    {
                        menu::setColor(2);
                        cout<<"\n\t\t查找失败！"<<endl;
                        menu::waitEnter();
                    }
                    break;
                case 5:      /**  账号管理 **/
                    run3=1;
                    while(run3)
                    {
                        cin.clear();fflush(stdin);
                        menu m3(3);
                        choose3=m3.getChose();
                        /**用户注销**/
                        if(choose3==1)
                        {
                            if(A.logout()&&menu::isOk())
                            {
                                    run3=0;
                                    run2=0;
                                    menu::setColor(1);
                                    cout<<"\t\t注销成功，即将退回"<<endl;
                                    menu::waitEnter();
                                    break;
                            }
                            else
                            {
                                menu::setColor(2);
                                cout<<"\t\t注销失败！"<<endl;
                                menu::waitEnter();
                            }
                        }
                        /**修改此用户密码**/
                        else if(choose3==2)
                        {
                            if(A.changePwd()&&menu::isOk())
                            {
                                menu::setColor(2);
                                cout<<"\n\n\t\t密码修改成功！"<<endl;
                            }
                            else
                            {
                                menu::setColor(2);
                                cout<<"\n\n\t\t密码修改失败！"<<endl;
                            }
                            menu::waitEnter();
                        }

                        /**修改用户的个人信息**/
                        else if(choose3==3)
                        {
                            if(A.changeInf()&&menu::isOk())
                            {
                                menu::setColor(2);
                                cout<<"\t\t修改信息成功！"<<endl;
                            }
                            else
                            {
                                menu::setColor(2);
                                cout<<"\t\t修改信息失败！"<<endl;
                            }
                            menu::waitEnter();
                        }
                        else if(choose3==0)
                        {
                            if(menu::isOk())
                            {
                                run3=0;
                                menu::waitEnter();
                                break;
                            }
                            else
                                run3=1;
                        }
                    }
                    break;
                case 0:      /**  退出登录  **/
                    if(menu::isOk()) run2=0;
                    break;
                default:
                    menu::inputWarn(); break;
                }
            }
            break;

        case 2:              /**  用户注册  **/
            if(!A.logup())
            {
                menu::setColor(2);
               cout<<"\n\t\t用户注册失败！"<<endl;
            }
            else
            {
                menu::setColor(2);
                cout<<"\n\t\t注册成功！"<<endl;
            }

            menu::waitEnter();
            break;

        case 3:              /**  用户帮助  **/
            menu::helpInf();
            break;

        case 0:              /**  退出系统  **/
            if(menu::isOk()) run1=0;
            break;

        default:
            menu::inputWarn();
            //menu::waitEnter();
            break;
        }
        cin.clear();fflush(stdin);
    }
    return 0;
}
