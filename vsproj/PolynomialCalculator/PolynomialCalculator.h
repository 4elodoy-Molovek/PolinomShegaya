#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PolynomialCalculator.h"

class PolynomialCalculator : public QMainWindow
{
    Q_OBJECT

public:
    PolynomialCalculator(QWidget *parent = nullptr);
    ~PolynomialCalculator();

private:
    Ui::PolynomialCalculatorClass ui;
};
