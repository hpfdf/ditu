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

    void on_action_X_triggered();

    void on_action_Json_triggered();

    void on_action_Json_2_triggered();

    void on_action_A_triggered();

    void on_action_Q_triggered();

    void on_action_M_triggered();

    void on_action_A_2_triggered();

    void on_action_start_triggered(bool checked);

    void on_action_2_triggered(bool checked);

    void on_action_4_triggered(bool checked);

    void on_action_3_triggered(bool checked);

    void on_action_triggered(bool checked);

    void on_action_5_triggered(bool checked);

    void on_action_center_triggered(bool checked);

    void on_action_6_triggered(bool checked);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
