#include "rels.h"

Rels* Rels::rels_instance=0;

Rels *Rels::instance()
{
    if (rels_instance==0)
        rels_instance = new Rels();
    return rels_instance;
}

void Rels::setSumpLoadFilter(QDate d)
{
    QSqlQuery query;
    query.prepare("select l.id from glass_sump_load as l "
                  "where l.dat_load=(select max(ll.dat_load) from glass_sump_load as ll "
                  "where ll.dat_load<= :d1 and ll.id_sump=l.id_sump) "
                  "union "
                  "select l.id from glass_sump_load as l "
                  "where l.dat_load=(select max(ll.dat_load) from glass_sump_load as ll "
                  "where ll.dat_load<= :d2 and ll.id_sump=l.id_sump)");
    query.bindValue(":d1",d);
    query.bindValue(":d2",d.addDays(-1));
    if (query.exec()){
        QString reg;
        while (query.next()){
            if (!reg.isEmpty()){
                reg+="|";
            }
            reg+="^"+query.value(0).toString()+"$";
        }
        //qDebug()<<reg;
        relSumpLoad->proxyModel()->setFilterRegExp(QRegExp(reg));
    } else {
        QMessageBox::critical(NULL,tr("Error"),query.lastError().text(),QMessageBox::Cancel);
    }
}

Rels::Rels(QObject *parent) : QObject(parent)
{
    relSump = new DbRelation(QString("select id, num from glass_sump order by num"),0,1,this);
    relKorr = new DbRelation(QString("select id, num from glass_korr order by num"),0,1,this);
    relCons = new DbRelation(QString("select id, num from glass_cons order by num"),0,1,this);
    relMatr = new DbRelation(QString("select id, nam from matr where id_type=3 order by nam"),0,1,this);
    relGlass = new DbRelation(QString("select id, nam from matr where id_type=4 order by nam"),0,1,this);
    relPar = new DbRelation(QString("select id, nam from glass_par order by nam"),0,1,this);
    QString quSumpLoad=QString::fromUtf8("select l.id, "
                                         "m.nam || '; №: ' || s.num||'; загр: '|| to_char(l.dat_load,'dd.MM.yy')||';'|| COALESCE(' парт.гл: '||l.part_lump||';','') || COALESCE(' M='||l.modul||';',''), "
                                         "l.dat_load "
                                         "from glass_sump_load as l "
                                         "inner join glass_sump as s on s.id=l.id_sump "
                                         "inner join matr as m on m.id=l.id_matr "
                                         "order by s.num, l.dat_load desc");
    relSumpLoad = new DbRelation(quSumpLoad,0,1,this);
    QString quKorrLoad=QString::fromUtf8("select l.id, m.nam || '; №: ' || k.num ||'; загр: '|| to_char(l.dat_load,'dd.MM.yy')||';'|| COALESCE(' парт.ст: '||l.parti_glass||';',''),l.parti_glass "
                                         "from glass_korr_load as l "
                                         "inner join glass_korr as k on k.id=l.id_korr "
                                         "inner join matr as m on m.id=l.id_matr "
                                         "order by k.num, l.dat_load desc");
    relKorrLoad = new DbRelation(quKorrLoad,0,1,this);

    relSumpLoad->proxyModel()->setFilterKeyColumn(0);
}

void Rels::refresh()
{
    relSump->refreshModel();
    relKorr->refreshModel();
    relCons->refreshModel();
    relMatr->refreshModel();
    relGlass->refreshModel();
    relSumpLoad->refreshModel();
    relKorrLoad->refreshModel();
    emit sigRefresh();
}
