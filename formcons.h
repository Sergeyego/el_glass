#ifndef FORMCONS_H
#define FORMCONS_H

#include <QWidget>
#include "models.h"

namespace Ui {
class FormCons;
}

class FormCons : public QWidget
{
    Q_OBJECT

public:
    explicit FormCons(QWidget *parent = 0);
    ~FormCons();

private:
    Ui::FormCons *ui;
    ModelConsLoad *modelConsLoad;

private slots:
    void updLoad();
    void updStat();
    void setLoadFilter(QModelIndex ind);
    void updStatPar(QModelIndex ind);
    void updStatCurrentTime();
};

#endif // FORMCONS_H
