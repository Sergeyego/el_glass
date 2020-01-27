#include "formcons.h"
#include "ui_formcons.h"

FormCons::FormCons(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCons)
{
    ui->setupUi(this);
    ui->pushButtonUpdCurrentTime->setIcon(this->style()->standardIcon(QStyle::SP_BrowserReload));
    ui->pushButtonUpd->setIcon(this->style()->standardIcon(QStyle::SP_BrowserReload));

    //ui->splitterStat->setStretchFactor(0,3);
    //ui->splitterStat->setStretchFactor(1,1);

    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEditBeg->setDate(QDate::currentDate().addDays(-7));
    ui->dateEditEnd->setDate(QDate::currentDate());

    modelConsLoadPar = new ModelConsLoadPar(this);
    ui->tableViewStatPar->setModel(modelConsLoadPar);
    ui->tableViewStatPar->setColumnHidden(0,true);
    ui->tableViewStatPar->setColumnWidth(1,120);
    ui->tableViewStatPar->setColumnWidth(2,70);
    ui->tableViewStatPar->setColumnWidth(3,70);

    modelConsStatData = new ModelConsStatData(this);
    modelConsStatData->refresh(-1);
    ui->tableViewStatGlass->setModel(modelConsStatData);
    ui->tableViewStatGlass->setColumnHidden(0,true);
    ui->tableViewStatGlass->setColumnWidth(1,50);
    ui->tableViewStatGlass->setColumnWidth(2,80);
    ui->tableViewStatGlass->setColumnWidth(3,60);
    ui->tableViewStatGlass->setColumnWidth(4,80);
    ui->tableViewStatGlass->setColumnWidth(5,60);
    ui->tableViewStatGlass->setColumnWidth(6,60);
    ui->tableViewStatGlass->setColumnWidth(7,80);
    ui->tableViewStatGlass->setColumnHidden(8,true);

    modelConsStat = new ModelConsStat(this);
    ui->tableViewStat->setModel(modelConsStat);
    connect(ui->tableViewStat->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(updStatData(QModelIndex)));
    updStat();
    ui->tableViewStat->setColumnHidden(0,true);
    ui->tableViewStat->setColumnWidth(1,50);
    ui->tableViewStat->setColumnWidth(2,80);
    ui->tableViewStat->setColumnWidth(3,80);
    ui->tableViewStat->setColumnWidth(4,60);
    ui->tableViewStat->setColumnWidth(5,60);
    ui->tableViewStat->setColumnWidth(6,70);

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
    connect(modelConsLoad,SIGNAL(sigUpd()),this,SLOT(updStat()));
    connect(ui->dateEdit,SIGNAL(dateChanged(QDate)),this,SLOT(updStat()));

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
    int currentRow=ui->tableViewStat->currentIndex().row();
    modelConsStat->refresh(ui->dateEdit->date());
    if (currentRow>=0 && currentRow<ui->tableViewStat->model()->rowCount()){
        ui->tableViewStat->setCurrentIndex(ui->tableViewStat->model()->index(currentRow,1));
    } else if (ui->tableViewStat->model()->rowCount()){
        ui->tableViewStat->setCurrentIndex(ui->tableViewStat->model()->index(0,1));
    }
}

void FormCons::setLoadFilter(QModelIndex ind)
{
    QDate d=ui->tableViewLoad->model()->data(ui->tableViewLoad->model()->index(ind.row(),1),Qt::EditRole).toDate();
    if (ind.column()==5){
        Rels::instance()->setSumpLoadFilter(d);
    } else if (ind.column()==3){
        Rels::instance()->setKorrLoadFilter(d);
    }
}

void FormCons::updStatData(QModelIndex ind)
{
    int id_load=ui->tableViewStat->model()->data(ui->tableViewStat->model()->index(ind.row(),0),Qt::EditRole).toInt();
    QString cons=ui->tableViewStat->model()->data(ui->tableViewStat->model()->index(ind.row(),1),Qt::DisplayRole).toString();
    modelConsStatData->refresh(id_load);
    modelConsLoadPar->refresh(id_load);
    ui->labelStatData->setText(QString::fromUtf8("Стекло в расходнике ")+"<b>"+cons+"</b>");
    ui->labelStatPar->setText(QString::fromUtf8("Выходные параметры стекла для расходника ")+"<b>"+cons+"</b>");
}

void FormCons::updStatCurrentTime()
{
    ui->dateEdit->setDate(QDate::currentDate());
}
