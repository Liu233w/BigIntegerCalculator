#ifndef ABOUT_DIALOG_H
#define ABOUT_DIALOG_H

#include <QDialog>

namespace Ui {
class About_dialog;
}

class About_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit About_dialog(QWidget *parent = 0);
    ~About_dialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::About_dialog *ui;
};

#endif // ABOUT_DIALOG_H
