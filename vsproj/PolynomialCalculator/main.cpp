#include "PolynomialCalculator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PolynomialCalculator w;
    w.show();
    return a.exec();
}
