#ifndef STATE_H
#define STATE_H

#include "biginteger.h"
#include "mainwindow.h"
#include <functional>

using namespace std;

const function<BigInteger (BigInteger&,BigInteger&)>
    funs [4] = { [](BigInteger& a,BigInteger& b){return a+b;} ,
                        [](BigInteger& a,BigInteger& b){return a-b;} ,
                        [](BigInteger& a,BigInteger& b){return a*b;} ,
                        [](BigInteger& a,BigInteger& b){return a/b;}
};

enum class OperatorType
{
    Plus =0,
    Minus =1,
    Times =2,
    Divide =3
};

class MainWindow;

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

#endif // STATE_H
