#ifndef FORMKORR_H
#define FORMKORR_H

#include <QWidget>
#include "models.h"

namespace Ui {
class FormKorr;
}

class FormKorr : public QWidget
{
    Q_OBJECT

public:
    explicit FormKorr(QWidget *parent = 0);
    ~FormKorr();

private:
    Ui::FormKorr *ui;
    ModelKorrLoad *modelKorrLoad;
    ModelKorrLoadData *modelKorrLoadData;
    ModelKorrLoadPar *modelKorrLoadPar;
    ModelKorrStat *modelKorrStat;
    ModelKorrStatData *modelKorrStatData;
    ModelKorrLoadPar *modelKorrStatPar;

private slots:
    void updLoad();
    void updStat();
    void updLoadData(QModelIndex ind);
    void updStatData(QModelIndex ind);
    void updStatCurrentTime();
    void setLoadFilter(QModelIndex ind);
};

#endif // FORMKORR_H
