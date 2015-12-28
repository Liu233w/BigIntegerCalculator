#include "about_dialog.h"
#include "ui_about_dialog.h"
#include <QGraphicsDropShadowEffect>

inline void setShadow(QWidget *it)
{
    QGraphicsDropShadowEffect *shadow_effect =
            new QGraphicsDropShadowEffect(it);
    shadow_effect->setOffset(2, 2);
    shadow_effect->setColor(Qt::darkGray);
    shadow_effect->setBlurRadius(8);
    it->setGraphicsEffect(shadow_effect);
}

About_dialog::About_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About_dialog)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_QuitOnClose,false);
    setShadow(ui->label);
    setShadow(ui->label_2);
}

About_dialog::~About_dialog()
{
    delete ui;
}

void About_dialog::on_pushButton_clicked()
{
    this->hide();
}
