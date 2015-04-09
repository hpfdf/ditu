#include "mainwindow.h"
#include "ui_mainwindow.h"

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
