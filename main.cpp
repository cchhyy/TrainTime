/**         �г�ʱ�̲�ѯϵͳ��֧��Ŀ��1��2��3��
1.���в�ͬ���͵��г��������     2.���б�ʱ�̱��������
3.�����ʱ�̱�����롢��ѯ������ȹ���    4.�������Ķ���ģ��ʽ
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
        case 1:     /**  �û���¼  **/
            run2=1;
            if(!A.login()) run2=0;
            else cout<<"\n\n\t\t��¼�ɹ���"<<endl;
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
                case 1:      /**��**/
                    if(A.getKind()!=2)
                    {
                        menu::setColor(2);
                        cout<<"\t\t���޴�Ȩ�ޣ�"<<endl;
                        menu::waitEnter();
                        break;
                    }
                    cout<<"\n\n\t\t����Ҫ¼���������";
                    cin>>n;
                    while(n--)
                    {
                        if(!t.trainAdd())
                        {
                            menu::setColor(2);
                            cout<<"\t\t¼�����"<<endl;
                            break;
                        }
                        cin.clear();fflush(stdin);
                        if(n!=0)
                        {
                            cout<<"\t\t���س�¼����һ����¼"<<endl;
                            getchar();
                        }
                    }
                    menu::setColor(2);
                    cout<<"\t\t¼�����"<<endl;
                    menu::waitEnter();
                    break;
                case 2:      /**  ɾ **/
                    cin.clear();fflush(stdin);
                    if(A.getKind()!=2)
                    {
                        menu::setColor(2);
                        cout<<"\t\t���޴�Ȩ�ޣ�"<<endl;
                        menu::waitEnter();
                        break;
                    }
                    f=t.trainDel();
                    if(f==true&&menu::isOk())
                    {
                        cin.clear();fflush(stdin);
                        menu::setColor(2);
                        cout<<"\t\tɾ���ɹ���"<<endl;
                        menu::waitEnter();
                    }
                    else
                    {
                        cin.clear();fflush(stdin);
                        menu::setColor(2);
                        cout<<"\t\tɾ��ʧ�ܣ�"<<endl;
                        menu::waitEnter();
                    }
                    break;
                case 3:      /**  ��  **/
                    if(A.getKind()!=2)
                    {
                        menu::setColor(2);
                        cout<<"\t\t���޴�Ȩ�ޣ�"<<endl;
                        menu::waitEnter();
                        break;
                    }
                    f=t.trainChange();
                    if(f==true)
                    {
                        menu::setColor(2);
                        cout<<"\t\t�޸ĳɹ���"<<endl;
                        menu::waitEnter();
                    }
                    else
                    {
                        menu::setColor(2);
                        cout<<"\t\t�޸�ʧ�ܣ�"<<endl;
                        menu::waitEnter();
                    }
                    break;
                case 4:      /**  ��  **/
                    f=t.trainSearch();
                    if(f==true)
                    {
                        menu::setColor(2);
                        cout<<"\n\t\t���ҳɹ���"<<endl;
                        menu::waitEnter();
                    }
                    else
                    {
                        menu::setColor(2);
                        cout<<"\n\t\t����ʧ�ܣ�"<<endl;
                        menu::waitEnter();
                    }
                    break;
                case 5:      /**  �˺Ź��� **/
                    run3=1;
                    while(run3)
                    {
                        cin.clear();fflush(stdin);
                        menu m3(3);
                        choose3=m3.getChose();
                        /**�û�ע��**/
                        if(choose3==1)
                        {
                            if(A.logout()&&menu::isOk())
                            {
                                    run3=0;
                                    run2=0;
                                    menu::setColor(1);
                                    cout<<"\t\tע���ɹ��������˻�"<<endl;
                                    menu::waitEnter();
                                    break;
                            }
                            else
                            {
                                menu::setColor(2);
                                cout<<"\t\tע��ʧ�ܣ�"<<endl;
                                menu::waitEnter();
                            }
                        }
                        /**�޸Ĵ��û�����**/
                        else if(choose3==2)
                        {
                            if(A.changePwd()&&menu::isOk())
                            {
                                menu::setColor(2);
                                cout<<"\n\n\t\t�����޸ĳɹ���"<<endl;
                            }
                            else
                            {
                                menu::setColor(2);
                                cout<<"\n\n\t\t�����޸�ʧ�ܣ�"<<endl;
                            }
                            menu::waitEnter();
                        }

                        /**�޸��û��ĸ�����Ϣ**/
                        else if(choose3==3)
                        {
                            if(A.changeInf()&&menu::isOk())
                            {
                                menu::setColor(2);
                                cout<<"\t\t�޸���Ϣ�ɹ���"<<endl;
                            }
                            else
                            {
                                menu::setColor(2);
                                cout<<"\t\t�޸���Ϣʧ�ܣ�"<<endl;
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
                case 0:      /**  �˳���¼  **/
                    if(menu::isOk()) run2=0;
                    break;
                default:
                    menu::inputWarn(); break;
                }
            }
            break;

        case 2:              /**  �û�ע��  **/
            if(!A.logup())
            {
                menu::setColor(2);
               cout<<"\n\t\t�û�ע��ʧ�ܣ�"<<endl;
            }
            else
            {
                menu::setColor(2);
                cout<<"\n\t\tע��ɹ���"<<endl;
            }

            menu::waitEnter();
            break;

        case 3:              /**  �û�����  **/
            menu::helpInf();
            break;

        case 0:              /**  �˳�ϵͳ  **/
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
