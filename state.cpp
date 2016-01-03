#include "state.h"
#include <string>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <memory>

using namespace std;

ostream& operator << (ostream& out, const BigInteger& a);
istream& operator >> (istream& in, BigInteger& a);

//执行运算（将派生类中重复的代码抽出）
inline unique_ptr<BigInteger> State::do_calculate()
{
    //保存第二个操作数
    unique_ptr<BigInteger> b(window->getNum ());
    //运算结果，除数为0时将抛出异常，智能指针保证被正确释放
    unique_ptr<BigInteger> res(new BigInteger(funs[window->operation]
            (*(window->last_output),*b)));
    //更新显示
    window->reset_last_output_text (QString((toString (*(window->last_output))
                                             +operationChar[window->operation]+
                                            toString(*b)).c_str ()));
    window->reset_this_output_text (QString(toString (*res).c_str ()));
    //更新数据
    window->last_output.reset (res);
    window->setRes (res);

    return b;
}

inline void State::enter_negative()
{
    window->reset_this_output_text ("");
    window->ui->ThisOutput->insertPlainText (
                QString('-'));
}

//基类的方法提供了每个派生类共同的操作（不是每个派生类都会调用）
//由各个派生类负责具体的状态切换
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

inline void State::press_get (int n)
{
       window->reset_this_output_text (
                   window->saves[n]);
}

inline void State::press_operation (OperatorType a)
{
    unique_ptr<BigInteger> tem=window->getNum ();
    window->last_output=std::move(tem);
    window->operation=a;
    QString o = window->ui->ThisOutput->
            toPlainText ();
    o+=operationChar[a];
    window->reset_last_output_text (o);
    //因为有在输入第二个运算数之前改变运算符的功能，
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

//各派生类的成员函数，由对应的qt槽函数调用

void when_start::press_number (int n)
{
    //输入0时不切换状态，以免重复输入多个0
    if(n!=0)
    {
        window->reset_this_output_text ("");
        State::press_number(n);
        window->state.reset(new enter_first_number(window));
    }
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
    //使用切换状态之后的成员函数，以减少代码重复
    //直接使用when_start的代码，不必考虑头一个数字是0的情况
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
    //输入的第一个数字不是0，切换状态以输入接下来的数字
    if(n!=0)
    {
        window->reset_this_output_text ("");
        State::press_number(n);
        window->state.reset(new enter_last_number(window));
    }
    else    //是0时切换状态以避免重复输入多个0或者在数字之前写入多余的0
    {
        window->reset_this_output_text ("");
        State::press_number(n);
        window->state.reset(new enter_equal(window));
    }
}

void last_start::press_C ()
{
    State::press_C();
    window->state.reset(new when_start(window));
}

void last_start::press_equal ()
{
    //什么都不做
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
        s+=operationChar[a];
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
    //除数为0时保证程序正常运行
    try
    {
    window->state.reset(new after_equal(window,
                                        State::do_calculate ()));
    }
    catch(logic_error)
    {
        window->reset_last_output_text ("除数为0！");
        window->reset_this_output_text ("0");
        window->state.reset(new when_start(window));
    }
}

void enter_last_number::press_get (int n)
{
    State::press_get (n);
    window->state.reset (new enter_equal
                         (window));
}

//在输入第二个运算数时若直接按下运算符则将计算结果作为下次运算的第一个运算数
void enter_last_number::press_operation (OperatorType a)
{
    try
    {
        //运算上个结果
        unique_ptr<BigInteger> res(new BigInteger(funs[window->operation]
                (*(window->last_output),*(window->getNum ()))));
        //更新数据
        window->setRes (res);
        window->last_output.reset (res);
        window->operation=a;
        //更新输出
        window->reset_last_output_text (QString((
                                                    toString (*res) + operationChar[a]).c_str ()));
        window->reset_this_output_text ("");
        //更新状态
        window->state.reset (new last_start(window));
    }
    catch(logic_error)
    {
        window->reset_last_output_text ("除数为0！");
        window->reset_this_output_text ("0");
        window->state.reset(new when_start(window));
    }
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
    State::press_set (n);
}

void enter_last_number::press_CE ()
{
    window->reset_this_output_text("");
    window->state.reset (new last_start(window));
}

void enter_equal::press_number (int n)
{
    window->state.reset (new last_start(window));
    window->state->press_number (n);
}

void enter_equal::press_C ()
{
    State::press_C();
    window->state.reset(new when_start(window));
}

void enter_equal::press_equal ()
{
    //除数为0时保证程序正常运行
    try
    {
    window->state.reset(new after_equal(window,
                                        State::do_calculate ()));
    }
    catch(logic_error)
    {
        window->reset_last_output_text ("除数为0！");
        window->reset_this_output_text ("0");
        window->state.reset(new when_start(window));
    }
}

void enter_equal::press_get (int n)
{
    State::press_get (n);
}

void enter_equal::press_operation (OperatorType a)
{
    //直接执行enter_last_number中的操作
    enter_last_number(window).press_operation (a);
}

void enter_equal::press_res ()
{
    //如果上次的计算结果不存在，则不进行任何操作
    if(window->res)
    {
        State::press_res ();
    }
}

void enter_equal::press_set (int n)
{
    State::press_set (n);
}

void enter_equal::press_CE ()
{
    window->reset_this_output_text("");
    window->state.reset(new last_start(window));
}

void after_equal::press_number (int n)
{
    window->reset_this_output_text ("");
    window->reset_last_output_text ("");
    window->state.reset(new when_start(window));
    window->state->press_number (n);
}

void after_equal::press_C ()
{
    State::press_C();
    window->state.reset(new when_start(window));
}

void after_equal::press_equal ()
{
    try
    {
        //重复上次运算
        unique_ptr<BigInteger> res(new BigInteger(funs[window->operation]
                                   (*(window->last_output),*last_number)));
        //更新输出
        window->reset_last_output_text (QString((toString (*(window->last_output))
                                                 +operationChar[window->operation]+
                                                toString(*last_number)).c_str ()));
        window->reset_this_output_text (QString(toString(*res).c_str ()));
        //更新数据
        window->setRes (res);
        window->last_output.reset (res);
        //有可能重复按下等号，不更新状态
    }
    catch(logic_error)
    {
        window->reset_last_output_text ("除数为0！");
        window->reset_this_output_text ("0");
        window->state.reset(new when_start(window));
    }
}

void after_equal::press_get (int n)
{
    State::press_get (n);
    window->reset_last_output_text ("0");
    window->state.reset (new enter_operator
                         (window));
}

void after_equal::press_operation (OperatorType a)
{
        State::press_operation (a);
        window->state.reset (new last_start(window));
}

void after_equal::press_res ()
{
    //如果上次的计算结果不存在，则不进行任何操作
    if(window->res)
    {
        State::press_res ();
        window->reset_last_output_text ("0");
        window->state.reset (new enter_operator(
                                 window));
    }
}

void after_equal::press_set (int n)
{
    State::press_set (n);
}

void after_equal::press_CE ()
{
    this->press_C ();
}
