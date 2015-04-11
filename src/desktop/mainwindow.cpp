#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Message(QString s)
{
    Ui_MainWindow* u = dynamic_cast<Ui_MainWindow*>(ui);
    if (u == nullptr)
        return;
    u->textEdit->setText(s);
}

void MainWindow::on_action_X_triggered()
{
    // TODO
    exit(0);
}

void MainWindow::on_action_Json_triggered()
{
    QString dir = QFileDialog::getOpenFileName(this, "", "", "Json File (*.json)");
    // TODO
}

void MainWindow::on_action_Json_2_triggered()
{
    // TODO
}

void MainWindow::on_action_A_triggered()
{
    QString dir = QFileDialog::getSaveFileName(this, "", "", "Json File (*.json)");
    // TODO
}

void MainWindow::on_action_Q_triggered()
{
    // TODO
}

void MainWindow::on_action_M_triggered()
{
    // TODO
}

void MainWindow::on_action_A_2_triggered()
{

}

//  modes

void MainWindow::on_action_2_triggered(bool checked)
{

}

void MainWindow::on_action_4_triggered(bool checked)
{

}

void MainWindow::on_action_3_triggered(bool checked)
{

}
void MainWindow::on_action_5_triggered(bool checked)
{

}

// functions
void MainWindow::on_action_start_triggered(bool checked)
{

}

void MainWindow::on_action_triggered(bool checked)
{

}

void MainWindow::on_action_center_triggered(bool checked)
{

}

void MainWindow::on_action_6_triggered(bool checked)
{

}
