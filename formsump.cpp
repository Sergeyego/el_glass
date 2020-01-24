#include "formsump.h"
#include "ui_formsump.h"

FormSump::FormSump(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSump)
{
    ui->setupUi(this);
    ui->pushButtonCurTime->setIcon(this->style()->standardIcon(QStyle::SP_BrowserReload));
    ui->pushButtonUpd->setIcon(this->style()->standardIcon(QStyle::SP_BrowserReload));

    ui->splitterCur->setStretchFactor(0,4);
    ui->splitterCur->setStretchFactor(1,2);
    ui->splitterLoad->setStretchFactor(0,4);
    ui->splitterLoad->setStretchFactor(1,2);

    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEditBeg->setDate(QDate::currentDate().addDays(-7));
    ui->dateEditEnd->setDate(QDate::currentDate());

    modelSumpLoadPar = new ModelSumpLoadPar(this);
    ui->tableViewLoadPar->setModel(modelSumpLoadPar);
    ui->tableViewLoadPar->setColumnHidden(0,true);
    ui->tableViewLoadPar->setColumnWidth(1,120);
    ui->tableViewLoadPar->setColumnWidth(2,70);
    ui->tableViewLoadPar->setColumnWidth(3,70);

    modelSumpLoad = new ModelSumpLoad(this);
    ui->tableViewLoad->setModel(modelSumpLoad);
    ui->tableViewLoad->setColumnHidden(0,true);
    ui->tableViewLoad->setColumnWidth(1,90);
    ui->tableViewLoad->setColumnWidth(2,70);
    ui->tableViewLoad->setColumnWidth(3,120);
    ui->tableViewLoad->setColumnWidth(4,70);
    ui->tableViewLoad->setColumnWidth(5,80);
    ui->tableViewLoad->setColumnWidth(6,90);

    modelSumpStatPar = new ModelSumpLoadPar(this);
    ui->tableViewStatPar->setModel(modelSumpStatPar);
    ui->tableViewStatPar->setColumnHidden(0,true);
    ui->tableViewStatPar->setColumnWidth(1,120);
    ui->tableViewStatPar->setColumnWidth(2,70);
    ui->tableViewStatPar->setColumnWidth(3,70);

    modelSumpStat = new ModelSumpStat(this);
    ui->tableViewStat->setModel(modelSumpStat);
    connect(ui->tableViewStat->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(updStatPar(QModelIndex)));
    updStat();
    ui->tableViewStat->setColumnHidden(0,true);
    ui->tableViewStat->setColumnWidth(1,90);
    ui->tableViewStat->setColumnWidth(2,70);
    ui->tableViewStat->setColumnWidth(3,120);
    ui->tableViewStat->setColumnWidth(4,70);
    ui->tableViewStat->setColumnWidth(5,80);
    ui->tableViewStat->setColumnWidth(6,90);

    connect(ui->pushButtonUpd,SIGNAL(clicked(bool)),this,SLOT(updLoad()));
    connect(ui->tableViewLoad->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(updLoadPar(QModelIndex)));
    connect(modelSumpLoad,SIGNAL(sigUpd()),this,SLOT(updStat()));

    connect(modelSumpLoadPar,SIGNAL(sigUpd()),modelSumpStatPar,SLOT(select()));
    connect(modelSumpStatPar,SIGNAL(sigUpd()),modelSumpLoadPar,SLOT(select()));
    connect(ui->dateEdit,SIGNAL(dateChanged(QDate)),this,SLOT(updStat()));
    connect(ui->pushButtonCurTime,SIGNAL(clicked(bool)),this,SLOT(updStatCurrentTime()));
    connect(modelSumpLoad,SIGNAL(sigUpd()),Rels::instance()->relSumpLoad,SLOT(refreshModel()));

    updLoad();
}

FormSump::~FormSump()
{
    delete ui;
}

void FormSump::updLoad()
{
    modelSumpLoad->refresh(ui->dateEditBeg->date(),ui->dateEditEnd->date());
    if (ui->tableViewLoad->model()->rowCount()){
        ui->tableViewLoad->setCurrentIndex(ui->tableViewLoad->model()->index(0,1));
    }
}

void FormSump::updLoadPar(QModelIndex ind)
{
    ui->tableViewLoadPar->setEnabled(!modelSumpLoad->isAdd());
    int id_sump=ui->tableViewLoad->model()->data(ui->tableViewLoad->model()->index(ind.row(),0),Qt::EditRole).toInt();
    QString sump=ui->tableViewLoad->model()->data(ui->tableViewLoad->model()->index(ind.row(),2),Qt::DisplayRole).toString();
    modelSumpLoadPar->refresh(id_sump);
    ui->labelLoad->setText(QString::fromUtf8("Выходные параметры для отстойника ")+"<b>"+sump+"</b>");
}

void FormSump::updStatPar(QModelIndex ind)
{
    int id_sump=ui->tableViewStat->model()->data(ui->tableViewStat->model()->index(ind.row(),0),Qt::EditRole).toInt();
    QString sump=ui->tableViewStat->model()->data(ui->tableViewStat->model()->index(ind.row(),1),Qt::DisplayRole).toString();
    modelSumpStatPar->refresh(id_sump);
    ui->labelStat->setText(QString::fromUtf8("Выходные параметры для отстойника ")+"<b>"+sump+"</b>");
}

void FormSump::updStat()
{
    int currentRow=ui->tableViewStat->currentIndex().row();
    modelSumpStat->refresh(ui->dateEdit->date());
    if (currentRow>=0 && currentRow<ui->tableViewStat->model()->rowCount()){
        ui->tableViewStat->setCurrentIndex(ui->tableViewStat->model()->index(currentRow,1));
    } else if (ui->tableViewStat->model()->rowCount()){
        ui->tableViewStat->setCurrentIndex(ui->tableViewStat->model()->index(0,1));
    }
}

void FormSump::updStatCurrentTime()
{
    ui->dateEdit->setDate(QDate::currentDate());
}
