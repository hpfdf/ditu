#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "floorview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void Message(QString s);

private slots:

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
