#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    formSump = new FormSump(this);
    ui->tabSump->setLayout(new QVBoxLayout(ui->tabSump));
    ui->tabSump->layout()->addWidget(formSump);

    formKorr = new FormKorr(this);
    ui->tabKorr->setLayout(new QVBoxLayout(ui->tabKorr));
    ui->tabKorr->layout()->addWidget(formKorr);

    formCons = new FormCons(this);
    ui->tabCons->setLayout(new QVBoxLayout(ui->tabCons));
    ui->tabCons->layout()->addWidget(formCons);
}

MainWindow::~MainWindow()
{
    delete ui;
}
