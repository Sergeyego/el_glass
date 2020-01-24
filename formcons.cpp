#include "formcons.h"
#include "ui_formcons.h"

FormCons::FormCons(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCons)
{
    ui->setupUi(this);
    ui->pushButtonUpdCurrentTime->setIcon(this->style()->standardIcon(QStyle::SP_BrowserReload));
    ui->pushButtonUpd->setIcon(this->style()->standardIcon(QStyle::SP_BrowserReload));

    ui->splitterStat->setStretchFactor(0,3);
    ui->splitterStat->setStretchFactor(1,1);

    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEditBeg->setDate(QDate::currentDate().addDays(-7));
    ui->dateEditEnd->setDate(QDate::currentDate());

    modelConsLoad = new ModelConsLoad(this);
    ui->tableViewLoad->setModel(modelConsLoad);
    ui->tableViewLoad->setColumnHidden(0,true);
    ui->tableViewLoad->setColumnWidth(1,80);
    ui->tableViewLoad->setColumnWidth(2,50);
    ui->tableViewLoad->setColumnWidth(3,330);
    ui->tableViewLoad->setColumnWidth(4,70);
    ui->tableViewLoad->setColumnWidth(5,330);

    connect(ui->pushButtonUpd,SIGNAL(clicked(bool)),this,SLOT(updLoad()));
    connect(ui->pushButtonUpdCurrentTime,SIGNAL(clicked(bool)),this,SLOT(updStatCurrentTime()));

    DbDelegate *delegate=qobject_cast<DbDelegate *>(ui->tableViewLoad->itemDelegate());
    if (delegate){
        connect(delegate,SIGNAL(createEdt(QModelIndex)),this,SLOT(setLoadFilter(QModelIndex)));
    }

    updLoad();
}

FormCons::~FormCons()
{
    delete ui;
}

void FormCons::updLoad()
{
    modelConsLoad->refresh(ui->dateEditBeg->date(),ui->dateEditEnd->date());
    if (ui->tableViewLoad->model()->rowCount()){
        ui->tableViewLoad->setCurrentIndex(ui->tableViewLoad->model()->index(0,1));
    }
}

void FormCons::updStat()
{

}

void FormCons::setLoadFilter(QModelIndex ind)
{
    if (ind.column()==5){
        QDate d=ui->tableViewLoad->model()->data(ui->tableViewLoad->model()->index(ind.row(),1),Qt::EditRole).toDate();
        Rels::instance()->setSumpLoadFilter(d);
    }
}

void FormCons::updStatPar(QModelIndex ind)
{

}

void FormCons::updStatCurrentTime()
{
    ui->dateEdit->setDate(QDate::currentDate());
}
