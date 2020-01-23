#include "models.h"

ModelSumpLoad::ModelSumpLoad(QObject *parent) : DbTableModel("glass_sump_load",parent)
{
    addColumn("id",QString::fromUtf8("id"));
    addColumn("dat_load",QString::fromUtf8("Дата"));
    addColumn("id_sump",QString::fromUtf8("Отстой."),NULL,Rels::instance()->relSump);
    addColumn("id_matr",QString::fromUtf8("Глыба"),NULL,Rels::instance()->relMatr);
    addColumn("modul",QString::fromUtf8("Модуль"),new QDoubleValidator(0,100,1,this));
    addColumn("part_lump",QString::fromUtf8("Парт. гл."));
    addColumn("dat_cook",QString::fromUtf8("Дата развар."));
    setSort("glass_sump_load.dat_load desc, glass_sump_load.id_sump");
}

void ModelSumpLoad::refresh(QDate begDate, QDate endDate)
{
    setFilter("glass_sump_load.dat_load between '"+begDate.toString("yyyy-MM-dd")+"' and '"+endDate.toString("yyyy-MM-dd")+"'");
    select();
}

ModelSumpLoadPar::ModelSumpLoadPar(QObject *parent) : DbTableModel("glass_sump_load_par",parent)
{
    addColumn("id_load",QString::fromUtf8("id_load"));
    addColumn("id_param",QString::fromUtf8("Параметр"),NULL,Rels::instance()->relPar);
    addColumn("val",QString::fromUtf8("Значение"),new QDoubleValidator(0,1000000,3,this));
    addColumn("temp",QString::fromUtf8("Т изм.,°С"),new QDoubleValidator(-100,100,1,this));
    setSort("glass_sump_load_par.id_param");
    setDefaultValue(3,25.0);
}

void ModelSumpLoadPar::refresh(int id_sump)
{
    setFilter("glass_sump_load_par.id_load = "+QString::number(id_sump));
    setDefaultValue(0,id_sump);
    select();
}

ModelSumpStat::ModelSumpStat(QObject *parent) : ModelRo(parent)
{
    dec=1;
}

void ModelSumpStat::refresh(QDate date)
{
    QSqlQuery query;
    query.prepare("select l.id, s.num, l.dat_load, m.nam, l.modul, l.part_lump, l.dat_cook "
                  "from glass_sump_load as l "
                  "inner join glass_sump as s on s.id=l.id_sump "
                  "inner join matr as m on m.id=l.id_matr "
                  "where l.dat_load=(select max(ll.dat_load) from glass_sump_load as ll where ll.dat_load<= :dat and ll.id_sump=l.id_sump) "
                  "order by s.num");
    query.bindValue(":dat",date);
    if (execQuery(query)){
        setHeaderData(1,Qt::Horizontal,QString::fromUtf8("Отстой."));
        setHeaderData(2,Qt::Horizontal,QString::fromUtf8("Дата загр."));
        setHeaderData(3,Qt::Horizontal,QString::fromUtf8("Глыба"));
        setHeaderData(4,Qt::Horizontal,QString::fromUtf8("Модуль"));
        setHeaderData(5,Qt::Horizontal,QString::fromUtf8("Парт. гл."));
        setHeaderData(6,Qt::Horizontal,QString::fromUtf8("Дата развар."));
    }
}

ModelKorrLoad::ModelKorrLoad(QObject *parent) : DbTableModel("glass_korr_load",parent)
{
    addColumn("id",QString::fromUtf8("id"));
    addColumn("dat_load",QString::fromUtf8("Дата"));
    addColumn("id_korr",QString::fromUtf8("Корректор"),NULL,Rels::instance()->relKorr);
    addColumn("id_matr",QString::fromUtf8("Стекло"),NULL,Rels::instance()->relGlass);
    addColumn("parti_glass",QString::fromUtf8("Партия"));
    setSort("glass_korr_load.dat_load desc, glass_korr_load.id_korr");
}

void ModelKorrLoad::refresh(QDate begDate, QDate endDate)
{
    setFilter("glass_korr_load.dat_load between '"+begDate.toString("yyyy-MM-dd")+"' and '"+endDate.toString("yyyy-MM-dd")+"'");
    select();
}

ModelKorrLoadData::ModelKorrLoadData(QObject *parent) : DbTableModel("glass_korr_load_data",parent)
{
    addColumn("id_load",QString::fromUtf8("id_load"));
    addColumn("id_sump_load",QString::fromUtf8("Отстойник"),NULL,Rels::instance()->relSumpLoad);
    addColumn("proc",QString::fromUtf8("Процент"),new QDoubleValidator(0,100,1,this));
    setSort("glass_korr_load_data.id_sump_load");
}

void ModelKorrLoadData::refresh(int id_korr)
{
    setFilter("glass_korr_load_data.id_load = "+QString::number(id_korr));
    setDefaultValue(0,id_korr);
    select();
}

ModelKorrLoadPar::ModelKorrLoadPar(QObject *parent) : DbTableModel("glass_korr_load_par",parent)
{
    addColumn("id_load",QString::fromUtf8("id_load"));
    addColumn("id_param",QString::fromUtf8("Параметр"),NULL,Rels::instance()->relPar);
    addColumn("val",QString::fromUtf8("Значение"),new QDoubleValidator(0,1000000,3,this));
    addColumn("temp",QString::fromUtf8("Т изм.,°С"),new QDoubleValidator(-100,100,1,this));
    setSort("glass_korr_load_par.id_param");
    setDefaultValue(3,23.0);
}

void ModelKorrLoadPar::refresh(int id_korr)
{
    setFilter("glass_korr_load_par.id_load = "+QString::number(id_korr));
    setDefaultValue(0,id_korr);
    select();
}

ModelKorrStat::ModelKorrStat(QObject *parent) : ModelRo(parent)
{
    dec=1;
}

void ModelKorrStat::refresh(QDate date)
{
    QSqlQuery query;
    query.prepare("select l.id, k.num, l.dat_load, m.nam, l.parti_glass "
                  "from glass_korr_load as l "
                  "inner join glass_korr as k on k.id=l.id_korr "
                  "inner join matr as m on m.id=l.id_matr "
                  "where l.dat_load=(select max(ll.dat_load) from glass_korr_load as ll where ll.dat_load<= :dat and ll.id_korr=l.id_korr) "
                  "order by k.num");
    query.bindValue(":dat",date);
    if (execQuery(query)){
        setHeaderData(1,Qt::Horizontal,QString::fromUtf8("Корректор"));
        setHeaderData(2,Qt::Horizontal,QString::fromUtf8("Дата загр."));
        setHeaderData(3,Qt::Horizontal,QString::fromUtf8("Стекло"));
        setHeaderData(4,Qt::Horizontal,QString::fromUtf8("Партия"));
    }
}

ModelKorrStatData::ModelKorrStatData(QObject *parent) : ModelRo(parent)
{
    dec=1;
}

void ModelKorrStatData::refresh(int id_load)
{
    QSqlQuery query;
    query.prepare("select l.id, d.proc, m.nam, s.num, l.dat_load, l.part_lump, l.modul, l.dat_cook "
                  "from glass_korr_load_data as d "
                  "inner join glass_sump_load as l on l.id=d.id_sump_load "
                  "inner join matr as m on m.id=l.id_matr "
                  "inner join glass_sump as s on s.id=l.id_sump "
                  "where d.id_load = :id_load order by proc");
    query.bindValue(":id_load",id_load);
    if (execQuery(query)){
        setHeaderData(1,Qt::Horizontal,QString::fromUtf8("%"));
        setHeaderData(2,Qt::Horizontal,QString::fromUtf8("Глыба"));
        setHeaderData(3,Qt::Horizontal,QString::fromUtf8("Отстой."));
        setHeaderData(4,Qt::Horizontal,QString::fromUtf8("Дата \nзагр. отст."));
        setHeaderData(5,Qt::Horizontal,QString::fromUtf8("Партия \nглыбы"));
        setHeaderData(6,Qt::Horizontal,QString::fromUtf8("Модуль"));
        setHeaderData(7,Qt::Horizontal,QString::fromUtf8("Дата \nразварки"));
    }

    //QSqlQuery qu;
    //qu.prepare("select d.id_sump_load from glass_korr_load_data as d where d.id_load = :id_load");
    //qu.bindValue(":id_load",id_load);
}

QVariant ModelKorrStatData::data(const QModelIndex &item, int role) const
{
    return ModelRo::data(item,role);
}
