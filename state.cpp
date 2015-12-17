#include "state.h"
#include <sstream>

using namespace std;

ostream& operator << (ostream& out, const BigInteger& a);
istream& operator >> (istream& in, BigInteger& a);

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

inline void State::enter_negative(MainWindow *window)
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
                   toString(*window->saves[n]));
}

inline void State::press_operation (OperatorType a)
{
    //enter
}

inline void State::press_res ()
{
       window->reset_this_output_text (
                   toString(*window->res));
}

inline void State::press_set (int n)
{
    window->saves[n].reset(
                new BigInteger(toBigInteger (
                                   window->ui->ThisOutput
                                   ->toPlainText().toStdString())));
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
    button->setEnabled(true);
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
    //如果不是输入负数就不执行操作
    if(a==OperatorType::Minus)
    {
        enter_negative (window);
        window->state.reset (new enter_first_number(
                                 window));
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
    //enter
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
    //enter
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

/************ 还未修改*****************/

void last_start::press_number (int n)
{
    window->reset_this_output_text ("");

    State::press_number(n);
    window->state.reset(new enter_first_number(window));
}

void last_start::press_C ()
{
    State::press_C();
}

void last_start::press_equal ()
{
    //不执行操作
}

void last_start::press_get (int n)
{
    State::press_get (n);
    window->state.reset (new enter_operator
                         (window));
}

void last_start::press_operation (OperatorType a)
{
    //enter
    //if a is minus, get a negative
}

void last_start::press_res ()
{
    //如果上次的计算结果不存在，则不进行任何操作
    if(window->res)
    {
        State::press_res ();
        window->state.reset (new enter_operator(
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
