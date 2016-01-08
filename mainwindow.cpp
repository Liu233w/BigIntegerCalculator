#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWhatsThis>
#include <QGraphicsDropShadowEffect>
#include <QScrollBar>
#include <string>
#include <QGraphicsOpacityEffect>
#include <cmath>

//给组件增加阴影效果，提高立体感
inline void setShadow(QWidget *it)
{
    QGraphicsDropShadowEffect *shadow_effect =
            new QGraphicsDropShadowEffect(it);
    shadow_effect->setOffset(5, 5);
    shadow_effect->setColor(Qt::darkGray);
    shadow_effect->setBlurRadius(8);
    it->setGraphicsEffect(shadow_effect);
}

//设置按钮效果
void styleButton(QPushButton* pushButton,QString str,ButtonSize bs)
{
    static const QString back_name="_pressed";
    static const QString ext_name=".png";

    pushButton->setStyleSheet ("QPushButton:!pressed{"
                               "border-image: url(:/button/material/"
                               +str+ext_name+");}"
                               "QPushButton:pressed{"
                               "border-image: url(:/button/material/"
                               +str+back_name+ext_name+");}");

    setShadow (pushButton);

    //根据屏幕大小设定图标大小
    QScreen *screen = qApp->primaryScreen();
    QSize screenSize = screen->size();
    QFont f = qApp->font();
    int pixelSize = (f.pointSizeF() * screen->logicalDotsPerInch()) / 72;
    if(pixelSize<0) //无法获取像素点大小（f.pointSize返回0）
    {//说明程序运行在android手机上
        int minsize=min(screenSize.width ()/7,screenSize.height ()/8);
        QSize baseSize(minsize*ButtonWidth[bs],minsize*ButtonHight[bs]);
        pushButton->setFixedSize (baseSize);
    }
    else
    {
        QSize buttonSize(static_cast<int>(40.0*ButtonWidth[bs]),
                         static_cast<int>(40.0*ButtonHight[bs]));
        if(screenSize.width() > 2000) //大分辨率屏幕，如surface
        {//解决大分辨率屏幕上按钮过小的问题
                buttonSize *= (pixelSize / 10.0);
        }
        pushButton->setFixedSize (buttonSize);
    }
}

//设置输入框效果，包括浅色的阴影（搭配输入框背景图片的透明效果）
//和自制的窄滚动条
//输入框的背景图片在mainwindow.ui中加入
inline void setBroser(QTextBrowser *it)
{
    QGraphicsDropShadowEffect *shadow_effect =
            new QGraphicsDropShadowEffect(it);
    shadow_effect->setOffset(5, 5);
    shadow_effect->setColor(QColor(0xa0,0xa0,0xa4,128));
    shadow_effect->setBlurRadius(8);
    it->setGraphicsEffect(shadow_effect);

    it->verticalScrollBar()->setStyleSheet(
                "QScrollBar:vertical"
                "{"
                "width:8px;"
                "background-color: rgba(255, 255, 255, 0);"
                "margin:0px,0px,0px,0px;"
                "padding-top:9px;"
                "padding-bottom:9px;"
                "}"
                "QScrollBar::handle:vertical"
                "{"
                "width:8px;"
                "background:rgba(0,0,0,25%);"
                " border-radius:4px;"
                "min-height:20;"
                "}"
                "QScrollBar::handle:vertical:hover"
                "{"
                "width:8px;"
                "background:rgba(0,0,0,50%);"
                " border-radius:4px;"
                "min-height:20;"
                "}"
                "QScrollBar::add-line:vertical"
                "{"
                "height:9px;width:8px;"
                "border-image:url(:/other/material/scrollbar/3.png);"
                "subcontrol-position:bottom;"
                "}"
                "QScrollBar::sub-line:vertical"
                "{"
                "height:9px;width:8px;"
                "border-image:url(:/other/material/scrollbar/1.png);"
                "subcontrol-position:top;"
                "}"
                "QScrollBar::add-line:vertical:hover"
                "{"
                "height:9px;width:8px;"
                "border-image:url(:/other/material/scrollbar/4.png);"
                "subcontrol-position:bottom;"
                "}"
                "QScrollBar::sub-line:vertical:hover"
                "{"
                "height:9px;width:8px;"
                "border-image:url(:/other/material/scrollbar/2.png);"
                "subcontrol-position:top;"
                "}"
                "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical"
                "{"
                "background:rgba(0,0,0,10%);"
                "border-radius:4px;"
                "}"
                );
}

//构造函数
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //生成“关于”窗口
    pAbout_dialog = new About_dialog(this);

    //生成并绘制主窗体
    ui->setupUi(this);
    this->setAttribute(Qt::WA_QuitOnClose,true);
    setBroser (ui->ThisOutput);
    setBroser (ui->LastOutput);
    reset_last_output_text ("0");
    reset_this_output_text ("0");
    setShadow (ui->label);
    setShadow (ui->label_2);
    setShadow (ui->label_3);
    setShadow (ui->label_4);

    //通过设置主窗体最大大小设置输入框大小（用于高分辨率屏幕）
    QScreen *screen = qApp->primaryScreen();
    QSize screenSize = screen->size();
    QFont f = qApp->font();
    int pixelSize = (f.pointSizeF() * screen->logicalDotsPerInch()) / 72;
    if(pixelSize<0) //无法获取像素点大小（f.pointSize返回0）
    {//说明程序运行在android手机上
        QSize baseSize(screenSize.width (),screenSize.height ()/5);
        setMaximumSize (baseSize);
    }
    else
    {
        QSize baseSize(550,550);
        if(screenSize.width() > 2000) //大分辨率屏幕，如surface
        {
                baseSize.rwidth ()*= (pixelSize / 10.0);
                baseSize.rheight ()*= (pixelSize / 13.0);
        }
        setMaximumSize (baseSize);
    }

    //加载按钮资源，使用代码加载减小工程量
    styleButton (ui->Button0,"0",ButtonSize::Mid);
    styleButton (ui->Button1,"1",ButtonSize::Mid);
    styleButton (ui->Button2,"2",ButtonSize::Mid);
    styleButton (ui->Button3,"3",ButtonSize::Mid);
    styleButton (ui->Button4,"4",ButtonSize::Mid);
    styleButton (ui->Button5,"5",ButtonSize::Mid);
    styleButton (ui->Button6,"6",ButtonSize::Mid);
    styleButton (ui->Button7,"7",ButtonSize::Mid);
    styleButton (ui->Button8,"8",ButtonSize::Mid);
    styleButton (ui->Button9,"9",ButtonSize::Mid);
    styleButton (ui->ButtonCE,"CE",ButtonSize::Mid);
    styleButton (ui->ButtonDivide,"divide",ButtonSize::Mid);
    styleButton (ui->ButtonPlus,"add",ButtonSize::Mid);
    styleButton (ui->ButtonMinus,"minus",ButtonSize::Mid);
    styleButton (ui->ButtonEqual,"equal",ButtonSize::Mid);
    styleButton (ui->ButtonTimes,"times",ButtonSize::Mid);
    styleButton (ui->Set1,"set",ButtonSize::Flat);
    styleButton (ui->Set2,"set",ButtonSize::Flat);
    styleButton (ui->Set3,"set",ButtonSize::Flat);
    styleButton (ui->Set4,"set",ButtonSize::Flat);
    styleButton (ui->Get1,"get_disabled",ButtonSize::Flat);
    styleButton (ui->Get2,"get_disabled",ButtonSize::Flat);
    styleButton (ui->Get3,"get_disabled",ButtonSize::Flat);
    styleButton (ui->Get4,"get_disabled",ButtonSize::Flat);
    styleButton (ui->ButtonRes,"res_disabled",ButtonSize::Flat);
    styleButton(ui->ButtonC,"c",ButtonSize::Flat);
    styleButton (ui->ButtonWhatsThis,"question mark",ButtonSize::Small);

    //初始化状态机
    state.reset(new when_start(this));
}

//析构函数
MainWindow::~MainWindow()
{
    //使用了unique_ptr，不需手动释放资源

    delete pAbout_dialog;
    delete ui;
}

//重设输入框的显示（下同）
//在改变文字之后必须要右对齐，使用函数减小工程量
void MainWindow::reset_this_output_text(const QString& s)
{
    ui->ThisOutput->setPlainText(s);
    ui->ThisOutput->setAlignment(Qt::AlignRight);
}

void MainWindow::reset_last_output_text(const QString& s)
{
    ui->LastOutput->setPlainText(s);
    ui->LastOutput->setAlignment(Qt::AlignRight);
}

//获取主输入框中显示的数字的大数类的指针
//使用智能指针以避免内存泄露
unique_ptr<BigInteger> MainWindow::getNum()
{
    return toBigInteger (ui->ThisOutput->
                         toPlainText ().toStdString ());
}

//用以设置res按钮的函数（res按钮保存上次的计算结果）
//使用函数以减少代码重复
void MainWindow::setRes(const BigInteger * n)
{
    QString *s_res=new QString(toString(*n).c_str ());
    if(!res)
    {
        ui->ButtonRes->setEnabled (true);
        styleButton (ui->ButtonRes,"res",ButtonSize::Flat);
    }
    ui->ButtonRes->setToolTip (*s_res);
    this->res.reset (s_res);
}

//以下为槽函数，在按下按钮时调用。将使用State的派生类对象方法来具体实现交互

void MainWindow::on_action_about_triggered()
{
    pAbout_dialog->show();
}

void MainWindow::on_action_exit_triggered()
{
    this->close();
}

void MainWindow::on_Set1_clicked()
{
    state->press_set (0);
}

void MainWindow::on_Set2_clicked()
{
    state->press_set (1);
}

void MainWindow::on_Set3_clicked()
{
    state->press_set (2);
}

void MainWindow::on_Set4_clicked()
{
    state->press_set (3);
}

void MainWindow::on_Get1_clicked()
{
    state->press_get (0);
}

void MainWindow::on_Get2_clicked()
{
    state->press_get (1);
}

void MainWindow::on_Get3_clicked()
{
    state->press_get (2);
}

void MainWindow::on_Get4_clicked()
{
    state->press_get (3);
}

void MainWindow::on_ButtonRes_clicked()
{
    state->press_res ();
}

void MainWindow::on_Button7_clicked()
{
    state->press_number (7);
}

void MainWindow::on_Button8_clicked()
{
    state->press_number (8);
}

void MainWindow::on_Button9_clicked()
{
    state->press_number (9);
}

void MainWindow::on_Button4_clicked()
{
    state->press_number (4);
}

void MainWindow::on_Button5_clicked()
{
    state->press_number (5);
}

void MainWindow::on_Button6_clicked()
{
    state->press_number (6);
}

void MainWindow::on_Button1_clicked()
{
    state->press_number (1);
}

void MainWindow::on_Button2_clicked()
{
    state->press_number (2);
}

void MainWindow::on_Button3_clicked()
{
    state->press_number (3);
}

void MainWindow::on_Button0_clicked()
{
    state->press_number (0);
}

void MainWindow::on_ButtonC_clicked()
{
    state->press_C ();
}

void MainWindow::on_ButtonEqual_clicked()
{
    state->press_equal ();
}

void MainWindow::on_ButtonPlus_clicked()
{
    state->press_operation (OperatorType::Plus);
}

void MainWindow::on_ButtonMinus_clicked()
{
    state->press_operation (OperatorType::Minus);
}

void MainWindow::on_ButtonTimes_clicked()
{
    state->press_operation (OperatorType::Times);
}

void MainWindow::on_ButtonDivide_clicked()
{
    state->press_operation (OperatorType::Divide);
}

void MainWindow::on_ButtonCE_clicked()
{
    state->press_CE ();
}

//进入what's this模式，以显示帮助
void MainWindow::on_ButtonWhatsThis_clicked()
{
    QWhatsThis::enterWhatsThisMode ();
}
