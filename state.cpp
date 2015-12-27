#include "state.h"
#include <sstream>
#include <string>
#include "ui_mainwindow.h"

using namespace std;

ostream& operator << (ostream& out, const BigInteger& a);
istream& operator >> (istream& in, BigInteger& a);

//进行大数类和字符串之间的相互转换，连接大数类和窗体的接口
inline BigInteger toBigInteger(const string& s)
{
    istringstream stin(s);
    BigInteger tem;
    stin>>tem;
    return tem;
}

inline string toString(const BigInteger& b)
{
    ostringstream sout;
    sout << b;
    return sout.str();
}

//基类的方法提供了每个派生类共同的操作（不是每个派生类都会调用）
//由各个派生类负责具体的状态切换
inline void State::enter_negative()
{
    window->reset_this_output_text ("");
    window->ui->ThisOutput->insertPlainText (
                QString('-'));
}

inline void State::press_number (int n)
{
    window->ui->ThisOutput->insertPlainText (
                QString(n+'0'));
}

inline void State::press_C ()
{
    window->reset_last_output_text("0");
    window->last_output.reset();
    window->reset_this_output_text("0");
}

inline void State::press_equal ()
{
    //enter
}

inline void State::press_get (int n)
{
       window->reset_this_output_text (
                   window->saves[n]);
}

inline void State::press_operation (OperatorType a)
{
    BigInteger *tem=new BigInteger(
                toBigInteger (window->ui->ThisOutput->
                              toPlainText ().toStdString ()));
    window->last_output.reset (tem);
    window->operation=a;
    QString o = window->ui->ThisOutput->
            toPlainText ();
    switch(a)
    {
    case OperatorType::Plus:
        o+='+';
        break;
    case OperatorType::Minus:
        o+='-';
        break;
    case OperatorType::Times:
        o+='*';
        break;
    case OperatorType::Divide:
        o+='/';
        break;
    }
    window->reset_last_output_text (o);
    //因为在输入第二个运算数之前有改变此运算符的功能，
    //所以第二个运算数不能默认为0
    window->reset_this_output_text ("");
}

inline void State::press_res ()
{
       window->reset_this_output_text (
                   *window->res);
}

inline void State::press_set (int n)
{
    window->saves[n]=window->ui->
            ThisOutput->toPlainText();
    QPushButton* button;
    switch(n)
    {
    case 0:
        button=window->ui->Get1;
        break;
    case 1:
        button=window->ui->Get2;
        break;
    case 2:
        button=window->ui->Get3;
        break;
    case 3:
        button=window->ui->Get4;
        break;
    }
    if(!button->isEnabled ())
    {
        button->setEnabled(true);
        void styleButton(QPushButton* pushButton,QString str);
        styleButton (button,"get");
    }
    button->setToolTip (
                window->ui->ThisOutput
                ->toPlainText());
}

void when_start::press_number (int n)
{
    window->reset_this_output_text ("");

    State::press_number(n);
    window->state.reset(new enter_first_number(window));
}

void when_start::press_C ()
{
    State::press_C();
}

void when_start::press_equal ()
{
    //不执行操作
}

void when_start::press_get (int n)
{
    State::press_get (n);
    window->state.reset (new enter_operator
                         (window));
}

void when_start::press_operation (OperatorType a)
{
    //如果输入负数执行
    if(a==OperatorType::Minus)
    {
        enter_negative ();
        window->state.reset (new enter_first_number(
                                 window));
    }
    //否则第一个运算数是0
    else
    {
        State::press_operation (a);
        window->state.reset (new last_start(window));
    }
}

void when_start::press_res ()
{
    //如果上次的计算结果不存在，则不进行任何操作
    if(window->res)
    {
        State::press_res ();
        window->state.reset (new enter_operator(
                                 window));
    }
}

void when_start::press_set (int n)
{
    //无操作
}

void when_start::press_CE ()
{
    //无操作
}

void enter_first_number::press_number (int n)
{
    State::press_number (n);
}

void enter_first_number::press_C ()
{
    State::press_C();
    window->state.reset(new when_start(window));
}

void enter_first_number::press_equal ()
{
    //不执行操作
}

void enter_first_number::press_get (int n)
{
    State::press_get (n);
    window->state.reset(new enter_operator(window));
}

void enter_first_number::press_operation (OperatorType a)
{
    State::press_operation (a);
    window->state.reset (new last_start(window));
}

void enter_first_number::press_res ()
{
    if(window->res)
    {
        State::press_res ();
        window->state.reset(new enter_operator(window));
    }
}

void enter_first_number::press_set (int n)
{
    State::press_set (n);
}

void enter_first_number::press_CE ()
{
    window->reset_this_output_text("0");
    window->state.reset (new when_start(window));
}

void enter_operator::press_number (int n)
{
    window->state.reset (new when_start(window));
    window->state->press_number (n);
}

void enter_operator::press_C ()
{
    State::press_C();
    window->state.reset(new when_start(window));
}

void enter_operator::press_equal ()
{
    //不执行操作
}

void enter_operator::press_get (int n)
{
    State::press_get(n);
}

void enter_operator::press_operation (OperatorType a)
{
    State::press_operation (a);
    window->state.reset (new last_start(window));
}

void enter_operator::press_res ()
{
    if(window->res)
    {
        State::press_res ();
    }
}

void enter_operator::press_set (int n)
{
    State::press_set(n);
}

void enter_operator::press_CE ()
{
    window->reset_this_output_text("0");
    window->state.reset (new when_start(window));
}

void last_start::press_number (int n)
{
    window->reset_this_output_text ("");

    State::press_number(n);
    window->state.reset(new enter_last_number(window));
}

void last_start::press_C ()
{
    State::press_C();
    window->state.reset(new when_start(window));
}

void last_start::press_equal ()
{
    //enter
}

void last_start::press_get (int n)
{
    State::press_get (n);
    window->state.reset (new enter_equal
                         (window));
}

//还未输入第二个运算数时按下别的运算符可以改变上次输入的运算符
void last_start::press_operation (OperatorType a)
{
    //如果按下的运算符和之前的运算符相同，不执行操作
    if(window->operation!=a)
    {
        QString s=window->ui->LastOutput->toPlainText ();
        s.remove (s.size ()-1,1);
        switch(a)
        {
        case OperatorType::Plus:
            s+='+';
            break;
        case OperatorType::Minus:
            s+='-';
            break;
        case OperatorType::Times:
            s+='*';
            break;
        case OperatorType::Divide:
            s+='/';
            break;
        }
        window->operation=a;
        window->reset_last_output_text (s);
    }
}

void last_start::press_res ()
{
    //如果上次的计算结果不存在，则不进行任何操作
    if(window->res)
    {
        State::press_res ();
        window->state.reset (new enter_equal(
                                 window));
    }
}

void last_start::press_set (int n)
{
    //无操作
}

void last_start::press_CE ()
{
    //无操作
}

/************ 还未修改*****************/

void enter_last_number::press_number (int n)
{
    State::press_number (n);
}

void enter_last_number::press_C ()
{
    State::press_C();
    window->state.reset(new when_start(window));
}

void enter_last_number::press_equal ()
{
    //不执行操作
}

void enter_last_number::press_get (int n)
{
    State::press_get (n);
    window->state.reset (new enter_equal
                         (window));
}

void enter_last_number::press_operation (OperatorType a)
{
    QString s=window->ui->LastOutput->toPlainText ();
    s.remove (s.size ()-1,1);
    switch(a)
    {
    case OperatorType::Plus:
        s+='+';
        break;
    case OperatorType::Minus:
        s+='-';
        break;
    case OperatorType::Times:
        s+='*';
        break;
    case OperatorType::Divide:
        s+='/';
        break;
    }
    window->operation=a;
    window->ui->LastOutput->setPlainText (s);
}

void enter_last_number::press_res ()
{
    //如果上次的计算结果不存在，则不进行任何操作
    if(window->res)
    {
        State::press_res ();
        window->state.reset (new enter_equal(
                                 window));
    }
}

void enter_last_number::press_set (int n)
{
    //无操作
}

void enter_last_number::press_CE ()
{
    //无操作
}

void enter_equal::press_number (int n)
{
//enter
}

void enter_equal::press_C ()
{
    State::press_C();
    window->state.reset(new when_start(window));
}

void enter_equal::press_equal ()
{
    //不执行操作
}

void enter_equal::press_get (int n)
{
    State::press_get (n);
    window->state.reset (new enter_equal
                         (window));
}

void enter_equal::press_operation (OperatorType a)
{
    QString s=window->ui->LastOutput->toPlainText ();
    s.remove (s.size ()-1,1);
    switch(a)
    {
    case OperatorType::Plus:
        s+='+';
        break;
    case OperatorType::Minus:
        s+='-';
        break;
    case OperatorType::Times:
        s+='*';
        break;
    case OperatorType::Divide:
        s+='/';
        break;
    }
    window->operation=a;
    window->ui->LastOutput->setPlainText (s);
}

void enter_equal::press_res ()
{
    //如果上次的计算结果不存在，则不进行任何操作
    if(window->res)
    {
        State::press_res ();
        window->state.reset (new enter_equal(
                                 window));
    }
}

void enter_equal::press_set (int n)
{
    //无操作
}

void enter_equal::press_CE ()
{
    //无操作
}
