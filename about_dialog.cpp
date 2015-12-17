#include "about_dialog.h"
#include "ui_about_dialog.h"

About_dialog::About_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About_dialog)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_QuitOnClose,false);
}

About_dialog::~About_dialog()
{
    delete ui;
}

void About_dialog::on_pushButton_clicked()
{
    this->hide();
}
