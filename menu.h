#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
/**
�˵���Ķ��壬��Ҫ�����û������������˵�����ʾ��
���ƿ���̨����ɫ���ȴ��û�ȷ�ϵȽ���������
**/
class menu
{
private:
    int kind; //�˵�����
public:
    menu();
    menu(int k);
    int getChose(); //��ȡ�û�����Ĳ˵�ѡ��
    static bool isOk(); //��һ����ʾ�û�����ȷ��
    static void waitEnter(); //�ȴ��û�����س�ȷ��
    static void inputWarn(); //�û����������ʾ������Ϣ
    static void helpInf(); //��ʾ������Ϣ
    static void setColor(int i); //���ƿ���̨��ɫ��ʾ
    static void showHead(); //��ʾ�г�ʱ����Ϣ�ı�ͷ
};

#endif // MENU_H_INCLUDED
