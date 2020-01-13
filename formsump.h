#ifndef FORMSUMP_H
#define FORMSUMP_H

#include <QWidget>
#include "models.h"

namespace Ui {
class FormSump;
}

class FormSump : public QWidget
{
    Q_OBJECT

public:
    explicit FormSump(QWidget *parent = 0);
    ~FormSump();

private:
    Ui::FormSump *ui;
    ModelSumpLoad *modelSumpLoad;
    ModelSumpLoadPar *modelSumpLoadPar;
    ModelSumpStat *modelSumpStat;
    ModelSumpLoadPar *modelSumpStatPar;

private slots:
    void updLoad();
    void updLoadPar(QModelIndex ind);
    void updStatPar(QModelIndex ind);
    void updStat();
    void updStatCurrentTime();
};

#endif // FORMSUMP_H
