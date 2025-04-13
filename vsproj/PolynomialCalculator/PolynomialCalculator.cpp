#include "PolynomialCalculator.h"
#include <iostream>


// MAIN WINDOW

PolynomialCalculator::PolynomialCalculator(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    addWidget = new AddPolynomialWidgetClass(this);
    errorWidget = new ErrorMessageWidgetClass();

    QObject::connect(ui.tableSelectorBox, &QComboBox::currentIndexChanged, this, &PolynomialCalculator::currentTableChanged);
    QObject::connect(ui.polynomialTable, &QTableWidget::cellClicked, this, &PolynomialCalculator::onPolynomialClicked);
    QObject::connect(ui.addButton, &QPushButton::clicked, this, &PolynomialCalculator::addPolynomialClicked);
    QObject::connect(ui.deleteButton, &QPushButton::clicked, this, &PolynomialCalculator::onDeletePolynomialClicked);
    
    QObject::connect(ui.expressionInputBox, &QTextEdit::textChanged, this, &PolynomialCalculator::onInputExpressionChanged);
    QObject::connect(ui.calculateButton, &QPushButton::clicked, this, &PolynomialCalculator::onClickedCalculate);
    QObject::connect(ui.savePolynomialButton, &QPushButton::clicked, this, &PolynomialCalculator::onClickedSave);

    ui.polynomialTable->setColumnWidth(0, 110);
    ui.polynomialTable->setColumnWidth(1, 320);

    ui.polynomialTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //setSizePolicy(QSizePolicy::Fixed);
}

PolynomialCalculator::~PolynomialCalculator()
{
    delete addWidget;
    delete errorWidget;
}

void PolynomialCalculator::updateTable()
{
    ui.polynomialTable->clear();
    ui.polynomialTable->setRowCount(0);

    cachedPolynomials.clear();
    handler->getAllPolynomials(cachedPolynomials);

    for (auto& pol : cachedPolynomials)
    {
        ui.polynomialTable->insertRow(ui.polynomialTable->rowCount());
        ui.polynomialTable->model()->setData(ui.polynomialTable->model()->index(ui.polynomialTable->rowCount() - 1, 0), QString::fromStdString(pol.first));
        ui.polynomialTable->model()->setData(ui.polynomialTable->model()->index(ui.polynomialTable->rowCount() - 1, 1), QString::fromStdString(pol.second));
    }

    QStringList labels;
    labels.append(QString::fromStdString("Name"));
    labels.append(QString::fromStdString("Polynomial"));
    ui.polynomialTable->setHorizontalHeaderLabels(labels);
}

void PolynomialCalculator::showErrorMessage(const std::string& errorMessage)
{
    errorWidget->open(errorMessage);
}

void PolynomialCalculator::onPolynomialClicked(int x, int y)
{
    selectedRow = x;
}

void PolynomialCalculator::addPolynomialClicked(bool a)
{
    addWidget->open();
}

void PolynomialCalculator::onDeletePolynomialClicked(bool a)
{
    if (selectedRow != -1)
    {
        std::string key = cachedPolynomials[selectedRow].first;
        handler->deletePolynomial(key);

        updateTable();

        selectedRow = -1;
    }
}

void PolynomialCalculator::onInputExpressionChanged()
{
}

void PolynomialCalculator::onClickedCalculate(bool a)
{
    std::string expression = ui.expressionInputBox->toPlainText().toStdString();

    try
    {
        handler->calculatePolynomialExpression(expression);

        ui.resultTextBox->setPlainText(QString::fromStdString(handler->getCachedExpressionResultNotation()));
    }

    catch (std::exception e)    { showErrorMessage(e.what()); }
    catch (std::string e)       { showErrorMessage(e); }
}

void PolynomialCalculator::onClickedSave(bool a)
{
    addWidget->openSaveMode(handler->getCachedExpressionResultNotation());
}

void PolynomialCalculator::currentTableChanged(int newTable)
{
    handler->setActiveTable(newTable);
    updateTable();
}



// ADD POLYNOMIAL WINDOW

AddPolynomialWidgetClass::AddPolynomialWidgetClass(PolynomialCalculator* inParentWindow, QWidget* parent) : QWidget(parent), parentWindow(inParentWindow)
{
    selfUI.setupUi(this);

    QObject::connect(selfUI.nameInputBox, &QTextEdit::textChanged, this, &AddPolynomialWidgetClass::onPolynomialNameChanged);
    QObject::connect(selfUI.polynomialNotationBox, &QTextEdit::textChanged, this, &AddPolynomialWidgetClass::onPolynomialNotationChanged);
    QObject::connect(selfUI.confirmButton, &QPushButton::clicked, this, &AddPolynomialWidgetClass::onClickedConfirm);

    QWidget::setWindowTitle(QString::fromStdString("Add Polynomial"));
}

void AddPolynomialWidgetClass::open()
{
    show();

    selfUI.nameInputBox->clear();
    selfUI.polynomialNotationBox->clear();

    selfUI.polynomialNotationBox->setReadOnly(false);
}

void AddPolynomialWidgetClass::openSaveMode(const std::string& polynomialExpression)
{
    show();
    notationCache = polynomialExpression;

    selfUI.nameInputBox->clear();
    selfUI.polynomialNotationBox->setPlainText(QString::fromStdString(notationCache));

    selfUI.polynomialNotationBox->setReadOnly(true);
}


void AddPolynomialWidgetClass::onPolynomialNameChanged()
{
    nameCache = selfUI.nameInputBox->toPlainText().toStdString();
}

void AddPolynomialWidgetClass::onPolynomialNotationChanged()
{
    notationCache = selfUI.polynomialNotationBox->toPlainText().toStdString();
}

void AddPolynomialWidgetClass::onClickedConfirm(bool a)
{
    bool failure = false;

    if (nameCache.size() == 0 || notationCache.size() == 0)
    {
        parentWindow->showErrorMessage("Polynomial name and notation can not be empty!");
        return;
    }

    try
    {
        parentWindow->getHandler()->addPolynomial(nameCache, notationCache);
    }

    catch (std::exception e)
    {
        failure = true;
        parentWindow->showErrorMessage(e.what());
    }

    if (!failure)
        hide();

    parentWindow->updateTable();
}


// ERROR MESSAGE WIDGET

ErrorMessageWidgetClass::ErrorMessageWidgetClass(QWidget* parent)
{
    selfUI.setupUi(this);

    QObject::connect(selfUI.okButton, &QPushButton::clicked, this, &ErrorMessageWidgetClass::onClickedOk);

    selfUI.errorMessageTitle->setStyleSheet("QLabel {color : red;}");
    selfUI.errorMessageBox->setStyleSheet("QTextEdit {color : red;}");

    QWidget::setWindowTitle(QString::fromStdString("Error"));
}

void ErrorMessageWidgetClass::open(const std::string& errorMessage)
{
    selfUI.errorMessageBox->setPlainText(QString::fromStdString(errorMessage));
    if (isVisible()) hide();
    show();
}

void ErrorMessageWidgetClass::onClickedOk(bool a)
{
    hide();
}
