#include "spectrogram.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_ForceRasterWidgets, false); // https://wiki.astralinux.ru/pages/viewpage.action?pageId=43614493
    Spectrogram w;
    w.show();
    return a.exec();
}
