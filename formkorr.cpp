#include "formkorr.h"
#include "ui_formkorr.h"

FormKorr::FormKorr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormKorr)
{
    ui->setupUi(this);
}

FormKorr::~FormKorr()
{
    delete ui;
}
