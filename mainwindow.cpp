#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    reset_this_output_text ("0");
    setWindowFlags (windowFlags ()|
                    Qt::WindowContextHelpButtonHint);

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

void MainWindow::reset_this_output_text(const string& s)
{
    ui->ThisOutput->setText(s.c_str ());
    ui->ThisOutput->setAlignment(Qt::AlignRight);
}

void MainWindow::reset_last_output_text(const string& s)
{
    ui->LastOutput->setText(s.c_str ());
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
