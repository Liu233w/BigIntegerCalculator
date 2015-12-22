#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "about_dialog.h"
#include "state.h"
#include <memory>
#include <array>

using namespace std;

const size_t SAVES_MAX = 4;

namespace Ui {
class MainWindow;
}

class State;
enum class OperatorType;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend class State;
    friend class when_start;
    friend class enter_first_number;
    friend class enter_last_number;
    friend class enter_operator;
    friend class last_start;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void reset_text_broser_algnment();
    //void reset_this_output_text(const string& s);
    void reset_this_output_text(const QString& s);
    void reset_last_output_text(const QString &s);

private slots:
    void on_action_about_triggered();
    void on_action_exit_triggered();

    void on_Set1_clicked();

    void on_Set2_clicked();

    void on_Set3_clicked();

    void on_Set4_clicked();

    void on_Get1_clicked();

    void on_Get2_clicked();

    void on_Get3_clicked();

    void on_Get4_clicked();

    void on_ButtonRes_clicked();

    void on_Button7_clicked();

    void on_Button8_clicked();

    void on_Button9_clicked();

    void on_Button4_clicked();

    void on_Button5_clicked();

    void on_Button6_clicked();

    void on_Button1_clicked();

    void on_Button2_clicked();

    void on_Button3_clicked();

    void on_Button0_clicked();

    void on_ButtonC_clicked();

    void on_ButtonEqual_clicked();

    void on_ButtonPlus_clicked();

    void on_ButtonMinus_clicked();

    void on_ButtonTimes_clicked();

    void on_ButtonDivide_clicked();

    void on_ButtonCE_clicked();

    void on_ButtonWhatsThis_clicked();

private:
    Ui::MainWindow *ui;
    About_dialog *pAbout_dialog;

    unique_ptr<State> state;

    array<QString,SAVES_MAX> saves;
    unique_ptr<QString> res;

    //unique_ptr<BigInteger> this_output;
    unique_ptr<BigInteger> last_output;

    OperatorType operation;
};

#endif // MAINWINDOW_H
