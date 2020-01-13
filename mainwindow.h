#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "formsump.h"
#include "formkorr.h"
#include "formcons.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    FormSump *formSump;
    FormKorr *formKorr;
    FormCons *formCons;
};

#endif // MAINWINDOW_H
