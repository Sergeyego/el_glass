#include "models.h"

ModelSumpLoad::ModelSumpLoad(QObject *parent) : DbTableModel("glass_sump_load",parent)
{
    addColumn("id",QString::fromUtf8("id"));
    addColumn("dat_load",QString::fromUtf8("Дата"));
    addColumn("id_sump",QString::fromUtf8("Отстой."),NULL,Rels::instance()->relSump);
    addColumn("id_matr",QString::fromUtf8("Стекло"),NULL,Rels::instance()->relGlass);
    addColumn("modul",QString::fromUtf8("Модуль"),new QDoubleValidator(0,100,1,this));
    addColumn("part_lump",QString::fromUtf8("Парт.глыбы"));
    addColumn("dat_cook",QString::fromUtf8("Дата развар."));
    setSort("glass_sump_load.dat_load, glass_sump_load.id_sump");
}

void ModelSumpLoad::refresh(QDate begDate, QDate endDate)
{
    setFilter("glass_sump_load.dat_load between '"+begDate.toString("yyyy-MM-dd")+"' and '"+endDate.toString("yyyy-MM-dd")+"'");
    select();
}

bool ModelSumpLoad::insertRow(int row, const QModelIndex &parent)
{
    setDefaultValue(1,QDate::currentDate());
    return DbTableModel::insertRow(row,parent);
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
        setHeaderData(3,Qt::Horizontal,QString::fromUtf8("Слекло"));
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
    setSort("glass_korr_load.dat_load, glass_korr_load.id_korr");
}

void ModelKorrLoad::refresh(QDate begDate, QDate endDate)
{
    setFilter("glass_korr_load.dat_load between '"+begDate.toString("yyyy-MM-dd")+"' and '"+endDate.toString("yyyy-MM-dd")+"'");
    select();
}

bool ModelKorrLoad::insertRow(int row, const QModelIndex &parent)
{
    setDefaultValue(1,QDate::currentDate());
    return DbTableModel::insertRow(row,parent);
}

ModelKorrLoadData::ModelKorrLoadData(QObject *parent) : DbTableModel("glass_korr_load_data",parent)
{
    addColumn("id_load",QString::fromUtf8("id_load"));
    addColumn("id_sump_load",QString::fromUtf8("Из отстойника"),NULL,Rels::instance()->relSumpLoad);
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
    addColumn("dat",QString::fromUtf8("Дата изм."));
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
    connect(this,SIGNAL(newQuery()),this,SLOT(refreshInPar()));
}

void ModelKorrStatData::refresh(int id_load)
{
    current_id_load=id_load;
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
        setHeaderData(2,Qt::Horizontal,QString::fromUtf8("Стекло"));
        setHeaderData(3,Qt::Horizontal,QString::fromUtf8("Отстой."));
        setHeaderData(4,Qt::Horizontal,QString::fromUtf8("Дата загр.\nотстойника"));
        setHeaderData(5,Qt::Horizontal,QString::fromUtf8("Партия \nглыбы"));
        setHeaderData(6,Qt::Horizontal,QString::fromUtf8("Модуль"));
        setHeaderData(7,Qt::Horizontal,QString::fromUtf8("Дата \nразварки"));
    }
}

QVariant ModelKorrStatData::data(const QModelIndex &item, int role) const
{
    if (role==Qt::ToolTipRole){
        int id=ModelRo::data(index(item.row(),0),Qt::EditRole).toInt();
        QString str;
        QList<QString> l=inPar.values(id);
        foreach (QString s, l) {
            if (!str.isEmpty()){
                str+="\n";
            }
            str+=s;
        }
        if (!str.isEmpty()){
            QString gl=ModelRo::data(index(item.row(),2),Qt::EditRole).toString();
            str.prepend(QString::fromUtf8("Параметры отстойника ")+gl+QString::fromUtf8(":\n"));
        }
        return str;
    }
    return ModelRo::data(item,role);
}

void ModelKorrStatData::refreshInPar()
{
    QSqlQuery qu;
    qu.prepare("select sl.id, p.nam, lp.val, lp.temp "
               "from glass_korr_load_data as d "
               "inner join glass_sump_load as sl on sl.id=d.id_sump_load "
               "inner join glass_sump_load_par as lp on lp.id_load=sl.id "
               "inner join glass_par as p on p.id=lp.id_param "
               "where d.id_load = :id_load");
    qu.bindValue(":id_load",current_id_load);
    inPar.clear();
    if (qu.exec()){
        while (qu.next()){
            QString val=qu.value(1).toString()+QString::fromUtf8(" = ")+qu.value(2).toString();
            if (!qu.value(3).isNull()){
                val+=QString::fromUtf8(" (")+qu.value(3).toString()+QString::fromUtf8("°С)");
            }
            inPar.insert(qu.value(0).toInt(),val);
        }
    } else {
        QMessageBox::critical(NULL,tr("Error"),qu.lastError().text(),QMessageBox::Cancel);
    }
}

ModelConsLoad::ModelConsLoad(QObject *parent) : DbTableModel("glass_cons_load",parent)
{
    addColumn("id",QString::fromUtf8("id"));
    addColumn("dat_load",QString::fromUtf8("Дата"));
    addColumn("id_cons",QString::fromUtf8("Расх."),NULL,Rels::instance()->relCons);
    addColumn("id_korr_load",QString::fromUtf8("Из корректора"),NULL,Rels::instance()->relKorrLoad);
    addColumn("parti_glass",QString::fromUtf8("Партия"));
    addColumn("id_sump_load",QString::fromUtf8("Из отстойника"),NULL,Rels::instance()->relSumpLoad);
    setSort("glass_cons_load.dat_load, glass_cons_load.id_cons");
}

void ModelConsLoad::refresh(QDate begDate, QDate endDate)
{
    setFilter("glass_cons_load.dat_load between '"+begDate.toString("yyyy-MM-dd")+"' and '"+endDate.toString("yyyy-MM-dd")+"'");
    select();
}

bool ModelConsLoad::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool ok=DbTableModel::setData(index,value,role);
    if (ok && index.column()==3){
        QModelIndex ind=relation(3)->model()->index(relation(3)->modelIndex(value.toString()).row(),2);
        QVariant part=relation(3)->model()->data(ind,Qt::EditRole);
        setData(this->index(index.row(),4),part,Qt::EditRole);
    }
    return ok;
}

bool ModelConsLoad::insertRow(int row, const QModelIndex &parent)
{
    setDefaultValue(1,QDate::currentDate());
    return DbTableModel::insertRow(row,parent);
}

ModelConsLoadPar::ModelConsLoadPar(QObject *parent) : DbTableModel("glass_cons_load_par",parent)
{
    addColumn("id_load",QString::fromUtf8("id_load"));
    addColumn("id_param",QString::fromUtf8("Параметр"),NULL,Rels::instance()->relPar);
    addColumn("val",QString::fromUtf8("Значение"),new QDoubleValidator(0,1000000,3,this));
    addColumn("temp",QString::fromUtf8("Т изм.,°С"),new QDoubleValidator(-100,100,1,this));
    addColumn("dat",QString::fromUtf8("Дата изм."));
    setSort("glass_cons_load_par.id_param, glass_cons_load_par.dat");
    setDefaultValue(3,23.0);
}

void ModelConsLoadPar::refresh(int id_cons)
{
    setFilter("glass_cons_load_par.id_load = "+QString::number(id_cons));
    setDefaultValue(0,id_cons);
    select();
}

bool ModelConsLoadPar::insertRow(int row, const QModelIndex &parent)
{
    setDefaultValue(4,QDate::currentDate());
    return DbTableModel::insertRow(row,parent);
}

ModelConsStat::ModelConsStat(QObject *parent): ModelRo(parent)
{

}

void ModelConsStat::refresh(QDate date)
{
    QSqlQuery query;
    query.prepare("select l.id, c.num, l.dat_load, COALESCE(mk.nam, ms.nam), l.parti_glass, k.num, gl.dat_load "
                  "from glass_cons_load as l "
                  "inner join glass_cons as c on c.id=l.id_cons "
                  "left join glass_korr_load as gl on gl.id=l.id_korr_load "
                  "left join glass_korr as k on k.id=gl.id_korr "
                  "left join matr as mk on mk.id=gl.id_matr "
                  "left join glass_sump_load as sl on sl.id=l.id_sump_load "
                  "left join matr as ms on ms.id=sl.id_matr "
                  "where l.dat_load=(select max(ll.dat_load) from glass_cons_load as ll where ll.dat_load<= :dat and ll.id_cons=l.id_cons) "
                  "order by c.num");
    query.bindValue(":dat",date);
    if (execQuery(query)){
        setHeaderData(1,Qt::Horizontal,QString::fromUtf8("Расх."));
        setHeaderData(2,Qt::Horizontal,QString::fromUtf8("Дата загр."));
        setHeaderData(3,Qt::Horizontal,QString::fromUtf8("Стекло"));
        setHeaderData(4,Qt::Horizontal,QString::fromUtf8("Партия"));
        setHeaderData(5,Qt::Horizontal,QString::fromUtf8("Коррект."));
        setHeaderData(6,Qt::Horizontal,QString::fromUtf8("Загр.кор."));
    }
}

ModelConsStatData::ModelConsStatData(QObject *parent) :ModelRo(parent)
{
    dec=1;
    connect(this,SIGNAL(newQuery()),this,SLOT(refreshInPar()));
}

void ModelConsStatData::refresh(int id_load)
{
    current_id_load=id_load;
    QSqlQuery query;
    query.prepare("(select d.id_load, d.proc, m.nam, s.num, l.dat_load, l.part_lump, l.modul, l.dat_cook, NULL "
                  "from glass_korr_load_data as d "
                  "inner join glass_sump_load as l on l.id=d.id_sump_load "
                  "inner join matr as m on m.id=l.id_matr "
                  "inner join glass_sump as s on s.id=l.id_sump "
                  "where d.id_load = (select id_korr_load from glass_cons_load where id = :id_load1 ) order by proc) "
                  "union "
                  "(select NULL, 100.0, mm.nam, ss.num, ll.dat_load, ll.part_lump, ll.modul, ll.dat_cook, ll.id "
                  "from glass_sump_load as ll "
                  "inner join matr as mm on mm.id=ll.id_matr "
                  "inner join glass_sump as ss on ss.id=ll.id_sump "
                  "where ll.id = (select id_sump_load from glass_cons_load where id = :id_load2 ))");
    query.bindValue(":id_load1",id_load);
    query.bindValue(":id_load2",id_load);
    if (execQuery(query)){
        setHeaderData(1,Qt::Horizontal,QString::fromUtf8("%"));
        setHeaderData(2,Qt::Horizontal,QString::fromUtf8("Стекло"));
        setHeaderData(3,Qt::Horizontal,QString::fromUtf8("Отстой."));
        setHeaderData(4,Qt::Horizontal,QString::fromUtf8("Дата загр.\nотстойника"));
        setHeaderData(5,Qt::Horizontal,QString::fromUtf8("Партия \nглыбы"));
        setHeaderData(6,Qt::Horizontal,QString::fromUtf8("Модуль"));
        setHeaderData(7,Qt::Horizontal,QString::fromUtf8("Дата \nразварки"));
    }
}

QVariant ModelConsStatData::data(const QModelIndex &item, int role) const
{
    if (role==Qt::ToolTipRole){
        QVariant id=ModelRo::data(index(item.row(),0),Qt::EditRole);
        if (!id.isNull()){
            QString str;
            QList<QString> l=inPar.values(id.toInt());
            foreach (QString s, l) {
                if (!str.isEmpty()){
                    str+="\n";
                }
                str+=s;
            }
            if (!str.isEmpty()){
                str.prepend(QString::fromUtf8("Параметры корректора ")+QString::fromUtf8(":\n"));
            }
            return str;
        }
    }
    return ModelRo::data(item,role);
}

void ModelConsStatData::refreshInPar()
{
    QSqlQuery qu;
    qu.prepare("select l.id_load, p.nam, l.val, l.temp, l.dat "
               "from glass_korr_load_par as l "
               "inner join glass_par as p on p.id=l.id_param "
               "where l.id_load = (select id_korr_load from glass_cons_load where id= :id_load)");
    qu.bindValue(":id_load",current_id_load);
    inPar.clear();
    if (qu.exec()){
        while (qu.next()){
            QString val=qu.value(1).toString()+QString::fromUtf8(" = ")+qu.value(2).toString();
            if (!qu.value(3).isNull()){
                val+=QString::fromUtf8(" (")+qu.value(3).toString()+QString::fromUtf8("°С)");
            }
            val+=" "+qu.value(4).toDate().toString("dd.MM.yy");
            inPar.insert(qu.value(0).toInt(),val);
        }
    } else {
        QMessageBox::critical(NULL,tr("Error"),qu.lastError().text(),QMessageBox::Cancel);
    }
}
