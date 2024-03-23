#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QApplication::setApplicationName(QStringLiteral("Jamming_SDR"));
    MainWindow w;
    w.show();
    return QApplication::exec();
}
