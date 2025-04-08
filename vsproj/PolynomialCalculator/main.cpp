#include "PolynomialCalculator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PolynomialCalculator w;

    PolynomialHandler* handler = new PolynomialHandler();
    w.setHandler(handler);

    w.show();
    return a.exec();
}
