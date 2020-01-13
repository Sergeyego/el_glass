#include "formcons.h"
#include "ui_formcons.h"

FormCons::FormCons(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCons)
{
    ui->setupUi(this);
}

FormCons::~FormCons()
{
    delete ui;
}
