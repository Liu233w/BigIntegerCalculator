#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "about_dialog.h"
#include "state.h"
#include <memory>
#include <array>

using namespace std;

//存储变量的最大空间
const size_t SAVES_MAX = 4;

namespace Ui {
class MainWindow;
}

//另外类的前置声明
class State;
enum OperatorType : int;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    //状态类可直接控制窗口的数据和显示
    friend class State;
    friend class when_start;
    friend class enter_first_number;
    friend class enter_last_number;
    friend class enter_operator;
    friend class last_start;
    friend class enter_equal;
    friend class after_equal;

public:
    //各个函数的说明在函数定义前面

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void reset_text_broser_algnment();

    void reset_this_output_text(const QString& s);
    void reset_last_output_text(const QString &s);

    unique_ptr<BigInteger> getNum();

    void setRes(const BigInteger*n);

private slots:
    //槽函数声明
    void on_action_about_triggered();
    void on_action_exit_triggered();
    void on_Set1_clicked();
    void on_Set2_clicked();
    void on_Set3_clicked();
    void on_Set4_clicked();
    void on_Get1_clicked();
    void on_Get2_clicked();
    void on_Get3_clicked();
    void on_Get4_clicked();
    void on_ButtonRes_clicked();
    void on_Button7_clicked();
    void on_Button8_clicked();
    void on_Button9_clicked();
    void on_Button4_clicked();
    void on_Button5_clicked();
    void on_Button6_clicked();
    void on_Button1_clicked();
    void on_Button2_clicked();
    void on_Button3_clicked();
    void on_Button0_clicked();
    void on_ButtonC_clicked();
    void on_ButtonEqual_clicked();
    void on_ButtonPlus_clicked();
    void on_ButtonMinus_clicked();
    void on_ButtonTimes_clicked();
    void on_ButtonDivide_clicked();
    void on_ButtonCE_clicked();
    void on_ButtonWhatsThis_clicked();

private:
    Ui::MainWindow *ui;
    About_dialog *pAbout_dialog;

    //状态机
    unique_ptr<State> state;
    //存储的大数变量，由于直接放进输入框中，因此采用字符串的形式保存
    array<QString,SAVES_MAX> saves;
    //上次计算的结果，可能为空，因此采用指针表示
    unique_ptr<QString> res;
    //第一个运算数的结果保存，在运算中需要用到
    unique_ptr<BigInteger> last_output;
    //用户按下的运算符，保存于此处
    OperatorType operation;
};

#endif // MAINWINDOW_H
