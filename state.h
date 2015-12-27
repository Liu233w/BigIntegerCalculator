#ifndef STATE_H
#define STATE_H

#include "biginteger.h"
#include "mainwindow.h"
#include <functional>

using namespace std;

//所有的运算操作
const function<BigInteger (BigInteger&,BigInteger&)>
    funs [4] = { [](BigInteger& a,BigInteger& b){return a+b;} ,
                        [](BigInteger& a,BigInteger& b){return a-b;} ,
                        [](BigInteger& a,BigInteger& b){return a*b;} ,
                        [](BigInteger& a,BigInteger& b){return a/b;}
};

//表示运算操作的枚举
enum class OperatorType
{
    Plus =0,
    Minus =1,
    Times =2,
    Divide =3
};

class MainWindow;

//状态基类，交互部分使用状态模式完成
class State
{
protected:
    MainWindow *window;
    void enter_negative();
public:
    explicit State(MainWindow* _window)
        : window(_window) {}
    virtual void press_number (int n);
    virtual void press_operation (OperatorType a);
    virtual void press_set (int n);
    virtual void press_get (int n);
    virtual void press_res ();
    virtual void press_equal ();
    virtual void press_C ();
    virtual void press_CE () =0;
};

//刚开始，还未输入第一个数字时的状态
class when_start
        :public State
{
public:
    explicit when_start(MainWindow* _window)
        : State(_window) {}
    void press_number (int n) final;
    void press_operation (OperatorType a) final;
    void press_set (int n) final;
    void press_get (int n) final;
    void press_res () final;
    void press_equal () final;
    void press_C () final;
    void press_CE () final;
};

//输入第一个运算数时的状态
class enter_first_number
        :public State
{
public:
    explicit enter_first_number(MainWindow* _window)
        :State(_window) {}
    void press_number (int n) final;
    void press_operation (OperatorType a) final;
    void press_set (int n) final;
    void press_get (int n) final;
    void press_res () final;
    void press_equal () final;
    void press_C () final;
    void press_CE () final;
};

//等待按下运算符的状态（在输入第一个操作数时按下GET或RES之后进入）
class enter_operator
        :public State
{
public:
    explicit enter_operator(MainWindow* _window)
        :State(_window) {}
    void press_number (int n) final;
    void press_operation (OperatorType a) final;
    void press_set (int n) final;
    void press_get (int n) final;
    void press_res () final;
    void press_equal () final;
    void press_C () final;
    void press_CE () final;
};

//输入第二个运算数时的状态
class enter_last_number
        :public State
{
public:
    explicit enter_last_number(MainWindow* _window)
        :State(_window) {}
    void press_number (int n) final;
    void press_operation (OperatorType a) final;
    void press_set (int n) final;
    void press_get (int n) final;
    void press_res () final;
    void press_equal () final;
    void press_C () final;
    void press_CE () final;
};

//按下运算符，还未开始输入第二个运算数时的状态
class last_start
        :public State
{
public:
    explicit last_start(MainWindow* _window)
        : State(_window) {}
    void press_number (int n) final;
    void press_operation (OperatorType a) final;
    void press_set (int n) final;
    void press_get (int n) final;
    void press_res () final;
    void press_equal () final;
    void press_C () final;
    void press_CE () final;
};

//等待按下等号时的状态（在输入第二个操作数时按下GET或RES之后进入）
class enter_equal
        :public State
{
public:
    explicit enter_equal(MainWindow* _window)
        : State(_window) {}
    void press_number (int n) final;
    void press_operation (OperatorType a) final;
    void press_set (int n) final;
    void press_get (int n) final;
    void press_res () final;
    void press_equal () final;
    void press_C () final;
    void press_CE () final;
};

//等待用户多次按下等号来进行重复运算时的状态（在第一次运算完成后进入）
class wait_for_equal
        :public State
{
private:
    BigInteger *last_number;
public:
    explicit wait_for_equal(MainWindow* _window,BigInteger *num)
        : State(_window), last_number(num) {}
    void press_number (int n) final;
    void press_operation (OperatorType a) final;
    void press_set (int n) final;
    void press_get (int n) final;
    void press_res () final;
    void press_equal () final;
    void press_C () final;
    void press_CE () final;
};

#endif // STATE_H
