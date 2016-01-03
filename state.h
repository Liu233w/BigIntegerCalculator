#ifndef STATE_H
#define STATE_H

#include "biginteger.h"
#include "mainwindow.h"
#include <functional>
#include <memory>
#include <sstream>

using namespace std;

//所有的运算操作
const function<BigInteger (const BigInteger&,const BigInteger&)>
    funs [4] = { [](const BigInteger& a,const BigInteger& b){return a+b;} ,
                        [](const BigInteger& a,const BigInteger& b){return a-b;} ,
                        [](const BigInteger& a,const BigInteger& b){return a*b;} ,
                        [](const BigInteger& a,const BigInteger& b){return a/b;}
};

//表示运算操作的枚举
enum OperatorType : int
{
    Plus =0,
    Minus =1,
    Times =2,
    Divide =3
};

//运算操作的对应字符表示
const char operationChar[]={'+','-','*','/'};

class MainWindow;

//状态基类，交互部分使用状态模式完成
class State
{
protected:
    MainWindow *window;
    //辅助函数，由派生类调用
    void enter_negative();
    unique_ptr<BigInteger> do_calculate();
public:
    explicit State(MainWindow* _window)
        : window(_window) {}
    //各个成员函数的功能注释与函数定义之前
    virtual void press_number (int n);
    virtual void press_operation (OperatorType a);
    virtual void press_set (int n);
    virtual void press_get (int n);
    virtual void press_res ();
    virtual void press_equal () =0;
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

//在一次运算完成后进入,等待用户使用上次的结果进行运算
class after_equal
        :public State
{
    std::unique_ptr<BigInteger> last_number;
public:
    explicit after_equal(MainWindow* _window,std::unique_ptr<BigInteger> num)
        : State(_window), last_number(std::move(num)) {}
    void press_number (int n) final;
    void press_operation (OperatorType a) final;
    void press_set (int n) final;
    void press_get (int n) final;
    void press_res () final;
    void press_equal () final;
    void press_C () final;
    void press_CE () final;
};

//进行大数类和字符串之间的相互转换，连接大数类和窗体的接口
inline unique_ptr<BigInteger> toBigInteger(const std::string& s)
{
    std::istringstream stin(s);
    //返回智能指针，避免内存溢出
    unique_ptr<BigInteger> tem (new BigInteger);
    stin>>*tem;
    return tem;
}

inline std::string toString(const BigInteger& b)
{
    std::ostringstream sout;
    sout << b;
    return sout.str();
}

#endif // STATE_H
