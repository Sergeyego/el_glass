#ifndef FORMCONS_H
#define FORMCONS_H

#include <QWidget>

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
};

#endif // FORMCONS_H
