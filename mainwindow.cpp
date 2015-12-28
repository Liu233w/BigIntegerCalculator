#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWhatsThis>
#include <QGraphicsDropShadowEffect>
#include <QScrollBar>

inline void setShadow(QWidget *it)
{
    QGraphicsDropShadowEffect *shadow_effect =
            new QGraphicsDropShadowEffect(it);
    shadow_effect->setOffset(5, 5);
    shadow_effect->setColor(Qt::darkGray);
    shadow_effect->setBlurRadius(8);
    it->setGraphicsEffect(shadow_effect);
}

inline void custButton(QPushButton* pushButton,QString str)
{
    QPixmap mypixmap;   mypixmap.load(str);
    pushButton->setIcon(mypixmap);
    pushButton->setIconSize(QSize(pushButton->width (),pushButton->height ()));
    pushButton->setFlat (true);
}

inline void styleButton(QPushButton* pushButton,QString str)
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
}

inline void setBroser(QTextBrowser *it)
{
    setShadow (it);
    it->verticalScrollBar()->setStyleSheet(
                "QScrollBar:vertical"
                "{"
                "width:8px;"
                "background:rgba(0,0,0,0%);"
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

//按钮透明样式表：background-color:rgba(255,255,255,0);

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
    setShadow (ui->Get1);
    setShadow (ui->Get2);
    setShadow (ui->Get3);
    setShadow (ui->Get4);
    setShadow (ui->ButtonRes);

    //加载按钮资源，使用代码加载减小工程量
    styleButton (ui->Button0,"0");
    styleButton (ui->Button1,"1");
    styleButton (ui->Button2,"2");
    styleButton (ui->Button3,"3");
    styleButton (ui->Button4,"4");
    styleButton (ui->Button5,"5");
    styleButton (ui->Button6,"6");
    styleButton (ui->Button7,"7");
    styleButton (ui->Button8,"8");
    styleButton (ui->Button9,"9");
    styleButton (ui->ButtonCE,"CE");
    styleButton (ui->ButtonDivide,"divide");
    styleButton (ui->ButtonPlus,"add");
    styleButton (ui->ButtonMinus,"minus");
    styleButton (ui->ButtonEqual,"equal");
    styleButton (ui->ButtonTimes,"times");
    styleButton (ui->Set1,"set");
    styleButton (ui->Set2,"set");
    styleButton (ui->Set3,"set");
    styleButton (ui->Set4,"set");
    styleButton(ui->ButtonC,"c");
    styleButton (ui->ButtonWhatsThis,"question mark");

    //初始化状态机
    state.reset(new when_start(this));
}

MainWindow::~MainWindow()
{
    //使用了unique_ptr，不需手动释放资源

    delete pAbout_dialog;
    delete ui;
}

void MainWindow::reset_text_broser_algnment()
{
    ui->ThisOutput->setAlignment(Qt::AlignRight);
    ui->LastOutput->setAlignment(Qt::AlignRight);
}

void MainWindow::reset_this_output_text(const QString& s)
{
    ui->ThisOutput->setText(s);
    ui->ThisOutput->setAlignment(Qt::AlignRight);
}

void MainWindow::reset_last_output_text(const QString& s)
{
    ui->LastOutput->setText(s);
    ui->LastOutput->setAlignment(Qt::AlignRight);
}

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

void MainWindow::on_ButtonWhatsThis_clicked()
{
    QWhatsThis::enterWhatsThisMode ();
}
