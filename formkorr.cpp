#include "formkorr.h"
#include "ui_formkorr.h"

FormKorr::FormKorr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormKorr)
{
    ui->setupUi(this);
    ui->pushButtonUpdCurrentTime->setIcon(this->style()->standardIcon(QStyle::SP_BrowserReload));
    ui->pushButtonUpd->setIcon(this->style()->standardIcon(QStyle::SP_BrowserReload));

    //ui->splitterStat->setStretchFactor(0,3);
    //ui->splitterStat->setStretchFactor(1,2);
    //ui->splitterLoad->setStretchFactor(0,3);
    //ui->splitterLoad->setStretchFactor(1,2);

    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEditBeg->setDate(QDate::currentDate().addDays(-7));
    ui->dateEditEnd->setDate(QDate::currentDate());

    modelKorrLoadData = new ModelKorrLoadData(this);
    ui->tableViewLoadGlass->setModel(modelKorrLoadData);
    ui->tableViewLoadGlass->setColumnHidden(0,true);

    modelKorrLoad = new ModelKorrLoad(this);
    ui->tableViewLoad->setModel(modelKorrLoad);
    ui->tableViewLoad->setColumnHidden(0,true);
    ui->tableViewLoad->setColumnWidth(1,90);
    ui->tableViewLoad->setColumnWidth(2,80);
    ui->tableViewLoad->setColumnWidth(3,70);
    ui->tableViewLoad->setColumnWidth(4,120);

    connect(ui->tableViewLoad->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(updLoadData(QModelIndex)));

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

void FormKorr::updLoadData(QModelIndex ind)
{
    int id_korr=ui->tableViewLoad->model()->data(ui->tableViewLoad->model()->index(ind.row(),0),Qt::EditRole).toInt();
    QString korr=ui->tableViewLoad->model()->data(ui->tableViewLoad->model()->index(ind.row(),2),Qt::DisplayRole).toString();
    modelKorrLoadData->refresh(id_korr);
    ui->labelLoadGlass->setText(QString::fromUtf8("Стекло для корректора ")+"<b>"+korr+"</b>");
}
