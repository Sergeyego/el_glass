#include "rels.h"

Rels* Rels::rels_instance=0;

Rels *Rels::instance()
{
    if (rels_instance==0)
        rels_instance = new Rels();
    return rels_instance;
}

Rels::Rels(QObject *parent) : QObject(parent)
{
    relSump = new DbRelation(QString("select id, num from glass_sump order by num"),0,1,this);
    relKorr = new DbRelation(QString("select id, num from glass_korr order by num"),0,1,this);
    relCons = new DbRelation(QString("select id, num from glass_cons order by num"),0,1,this);
    relMatr = new DbRelation(QString("select id, nam from matr where cod='g' order by nam"),0,1,this);
    relPar = new DbRelation(QString("select id, nam from glass_par order by nam"),0,1,this);
    QString quSumpLoad=QString::fromUtf8("select l.id, "
                                         "m.nam || '; отстойник:' || s.num||'; загр:'|| to_char(l.dat_load,'dd.MM.yy')||';'|| COALESCE(' парт.гл:'||l.part_lump||';','') || COALESCE(' модуль:'||l.modul||';',''), "
                                         "l.dat_load "
                                         "from glass_sump_load as l "
                                         "inner join glass_sump as s on s.id=l.id_sump "
                                         "inner join matr as m on m.id=l.id_matr "
                                         "order by l.dat_load desc, s.num");
    relSumpLoad = new DbRelation(quSumpLoad,0,1,this);
}

void Rels::refresh()
{
    relSump->refreshModel();
    relKorr->refreshModel();
    relCons->refreshModel();
    relMatr->refreshModel();
    relSumpLoad->refreshModel();
    emit sigRefresh();
}
