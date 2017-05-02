#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
/**
菜单类的定义，主要用于用户交互。各级菜单的显示，
控制控制台的颜色，等待用户确认等交互操作。
**/
class menu
{
private:
    int kind; //菜单级别
public:
    menu();
    menu(int k);
    int getChose(); //获取用户输入的菜单选项
    static bool isOk(); //进一步提示用户输入确认
    static void waitEnter(); //等待用户输入回车确认
    static void inputWarn(); //用户输入错误提示错误信息
    static void helpInf(); //显示帮助信息
    static void setColor(int i); //控制控制台颜色显示
    static void showHead(); //显示列车时刻信息的表头
};

#endif // MENU_H_INCLUDED
