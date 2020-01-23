#include "formkorr.h"
#include "ui_formkorr.h"

FormKorr::FormKorr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormKorr)
{
    ui->setupUi(this);
    ui->pushButtonUpdCurrentTime->setIcon(this->style()->standardIcon(QStyle::SP_BrowserReload));
    ui->pushButtonUpd->setIcon(this->style()->standardIcon(QStyle::SP_BrowserReload));

    ui->splitterStat->setStretchFactor(0,5);
    ui->splitterStat->setStretchFactor(1,6);
    ui->splitterLoad->setStretchFactor(0,5);
    ui->splitterLoad->setStretchFactor(1,6);

    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEditBeg->setDate(QDate::currentDate().addDays(-7));
    ui->dateEditEnd->setDate(QDate::currentDate());

    modelKorrLoadData = new ModelKorrLoadData(this);
    ui->tableViewLoadGlass->setModel(modelKorrLoadData);
    ui->tableViewLoadGlass->setColumnHidden(0,true);
    ui->tableViewLoadGlass->setColumnWidth(1,350);
    ui->tableViewLoadGlass->setColumnWidth(2,70);

    modelKorrLoadPar = new ModelKorrLoadPar(this);
    ui->tableViewLoadPar->setModel(modelKorrLoadPar);
    ui->tableViewLoadPar->setColumnHidden(0,true);
    ui->tableViewLoadPar->setColumnWidth(1,120);
    ui->tableViewLoadPar->setColumnWidth(2,70);
    ui->tableViewLoadPar->setColumnWidth(3,70);

    modelKorrLoad = new ModelKorrLoad(this);
    ui->tableViewLoad->setModel(modelKorrLoad);
    ui->tableViewLoad->setColumnHidden(0,true);
    ui->tableViewLoad->setColumnWidth(1,90);
    ui->tableViewLoad->setColumnWidth(2,80);
    ui->tableViewLoad->setColumnWidth(3,120);
    ui->tableViewLoad->setColumnWidth(4,70);

    modelKorrStatData = new ModelKorrStatData(this);
    modelKorrStatData->refresh(-1);
    ui->tableViewStatGlass->setModel(modelKorrStatData);
    ui->tableViewStatGlass->setColumnHidden(0,true);
    ui->tableViewStatGlass->setColumnWidth(1,50);
    ui->tableViewStatGlass->setColumnWidth(2,80);
    ui->tableViewStatGlass->setColumnWidth(3,60);
    ui->tableViewStatGlass->setColumnWidth(4,80);
    ui->tableViewStatGlass->setColumnWidth(5,60);
    ui->tableViewStatGlass->setColumnWidth(6,60);
    ui->tableViewStatGlass->setColumnWidth(7,80);

    modelKorrStatPar = new ModelKorrLoadPar(this);
    ui->tableViewStatPar->setModel(modelKorrStatPar);
    ui->tableViewStatPar->setColumnHidden(0,true);
    ui->tableViewStatPar->setColumnWidth(1,120);
    ui->tableViewStatPar->setColumnWidth(2,70);
    ui->tableViewStatPar->setColumnWidth(3,70);

    modelKorrStat = new ModelKorrStat(this);
    ui->tableViewStat->setModel(modelKorrStat);
    connect(ui->tableViewStat->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(updStatData(QModelIndex)));
    updStat();
    ui->tableViewStat->setColumnHidden(0,true);
    ui->tableViewStat->setColumnWidth(1,90);
    ui->tableViewStat->setColumnWidth(2,80);
    ui->tableViewStat->setColumnWidth(3,120);
    ui->tableViewStat->setColumnWidth(4,70);

    connect(ui->tableViewLoad->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(updLoadData(QModelIndex)));
    connect(ui->pushButtonUpd,SIGNAL(clicked(bool)),this,SLOT(updLoad()));
    connect(ui->dateEdit,SIGNAL(dateChanged(QDate)),this,SLOT(updStat()));
    connect(ui->pushButtonUpdCurrentTime,SIGNAL(clicked(bool)),this,SLOT(updStatCurrentTime()));
    connect(modelKorrLoad,SIGNAL(sigUpd()),this,SLOT(updStat()));
    connect(modelKorrLoadData,SIGNAL(sigUpd()),modelKorrStatData,SLOT(select()));
    connect(modelKorrLoadPar,SIGNAL(sigUpd()),modelKorrStatPar,SLOT(select()));
    connect(modelKorrStatPar,SIGNAL(sigUpd()),modelKorrLoadPar,SLOT(select()));

    updLoad();
}

FormKorr::~FormKorr()
{
    delete ui;
}

void FormKorr::updLoad()
{
    modelKorrLoad->refresh(ui->dateEditBeg->date(),ui->dateEditEnd->date());
    if (ui->tableViewLoad->model()->rowCount()){
        ui->tableViewLoad->setCurrentIndex(ui->tableViewLoad->model()->index(0,1));
    }
}

void FormKorr::updStat()
{
    int currentRow=ui->tableViewStat->currentIndex().row();
    modelKorrStat->refresh(ui->dateEdit->date());
    if (currentRow>=0 && currentRow<ui->tableViewStat->model()->rowCount()){
        ui->tableViewStat->setCurrentIndex(ui->tableViewStat->model()->index(currentRow,1));
    } else if (ui->tableViewStat->model()->rowCount()){
        ui->tableViewStat->setCurrentIndex(ui->tableViewStat->model()->index(0,1));
    }
}

void FormKorr::updLoadData(QModelIndex ind)
{
    ui->tableViewLoadGlass->setEnabled(!modelKorrLoad->isAdd());
    ui->tableViewLoadPar->setEnabled(!modelKorrLoad->isAdd());
    int id_korr=ui->tableViewLoad->model()->data(ui->tableViewLoad->model()->index(ind.row(),0),Qt::EditRole).toInt();
    QString korr=ui->tableViewLoad->model()->data(ui->tableViewLoad->model()->index(ind.row(),2),Qt::DisplayRole).toString();
    modelKorrLoadData->refresh(id_korr);
    ui->labelLoadGlass->setText(QString::fromUtf8("Загрузка корректора ")+"<b>"+korr+"</b>");

    modelKorrLoadPar->refresh(id_korr);
    ui->labelLoadPar->setText(QString::fromUtf8("Выходные параметры стекла для корректора ")+"<b>"+korr+"</b>");
}

void FormKorr::updStatData(QModelIndex ind)
{
    int id_load=ui->tableViewStat->model()->data(ui->tableViewStat->model()->index(ind.row(),0),Qt::EditRole).toInt();
    QString korr=ui->tableViewStat->model()->data(ui->tableViewStat->model()->index(ind.row(),1),Qt::DisplayRole).toString();
    modelKorrStatData->refresh(id_load);
    modelKorrStatPar->refresh(id_load);
    ui->labelStatGlass->setText(QString::fromUtf8("Стекло в корректоре ")+"<b>"+korr+"</b>");
    ui->labelStatPar->setText(QString::fromUtf8("Выходные параметры стекла для корректора ")+"<b>"+korr+"</b>");
}

void FormKorr::updStatCurrentTime()
{
    ui->dateEdit->setDate(QDate::currentDate());
}
