#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWhatsThis>

inline void custButton(QPushButton* pushButton,QString str)
{
    QPixmap mypixmap;   mypixmap.load(str);
    pushButton->setIcon(mypixmap);
    pushButton->setIconSize(QSize(pushButton->width (),pushButton->height ()));
    pushButton->setFlat (true);
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
    QPalette pe;
    pe.setColor(QPalette::ButtonText,Qt::red);
    ui->ButtonC->setPalette(pe);
    pe.setColor(QPalette::ButtonText,Qt::darkGreen);
    ui->ButtonRes->setPalette(pe);
    this->setAttribute(Qt::WA_QuitOnClose,true);
    reset_last_output_text ("0");
    reset_this_output_text (QString("0"));
    setWindowFlags (windowFlags ()|
                    Qt::WindowContextHelpButtonHint);

    //加载按钮资源
    custButton (ui->Button0,":/new/prefix1/material/0.png");
    custButton (ui->Button1,":/new/prefix1/material/1.png");
    custButton (ui->Button2,":/new/prefix1/material/2.png");
    custButton (ui->Button3,":/new/prefix1/material/3.png");
    custButton (ui->Button4,":/new/prefix1/material/4.png");
    custButton (ui->Button5,":/new/prefix1/material/5.png");
    custButton (ui->Button6,":/new/prefix1/material/6.png");
    custButton (ui->Button7,":/new/prefix1/material/7.png");
    custButton (ui->Button8,":/new/prefix1/material/8.png");
    custButton (ui->Button9,":/new/prefix1/material/9.png");
    custButton (ui->ButtonCE,":/new/prefix1/material/CE.png");
    custButton (ui->ButtonDivide,":/new/prefix1/material/divide.png");
    custButton (ui->ButtonPlus,":/new/prefix1/material/add.png");
    custButton (ui->ButtonMinus,":/new/prefix1/material/minus.png");
    custButton (ui->ButtonEqual,":/new/prefix1/material/equal.png");
    custButton (ui->ButtonTimes,":/new/prefix1/material/times.png");

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
