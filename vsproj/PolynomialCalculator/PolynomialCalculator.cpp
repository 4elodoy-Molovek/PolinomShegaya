#include "PolynomialCalculator.h"
#include <iostream>

PolynomialCalculator::PolynomialCalculator(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    addWidget = new AddPolynomialWidgetClass(this);

    QObject::connect(ui.tableSelectorBox, &QComboBox::currentIndexChanged, this, &PolynomialCalculator::currentTableChanged);
    QObject::connect(ui.polynomialTable, &QTableWidget::cellClicked, this, &PolynomialCalculator::onPolynomialClicked);
    QObject::connect(ui.addButton, &QPushButton::clicked, this, &PolynomialCalculator::addPolynomialClicked);
    QObject::connect(ui.deleteButton, &QPushButton::clicked, this, &PolynomialCalculator::onDeletePolynomialClicked);
    //QObject::connect(ui.tableSelectorBox, &QComboBox::currentIndexChanged, this, &PolynomialCalculator::currentTableChanged);
    
}

PolynomialCalculator::~PolynomialCalculator()
{}

void PolynomialCalculator::onPolynomialClicked(int x, int y)
{
}

void PolynomialCalculator::addPolynomialClicked(bool a)
{
    addWidget->show();
}

void PolynomialCalculator::onDeletePolynomialClicked(bool a)
{
}

void PolynomialCalculator::onInputExpressionChanged()
{
}

void PolynomialCalculator::onClickedCalculate(bool a)
{
}

void PolynomialCalculator::onClickedSave(bool a)
{
    addWidget->show();
}

void PolynomialCalculator::currentTableChanged(int newTable)
{
    handler->setActiveTable(newTable);
}
