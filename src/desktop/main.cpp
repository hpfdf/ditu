#include <QApplication>
#include <QWidget>
#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT

};

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
