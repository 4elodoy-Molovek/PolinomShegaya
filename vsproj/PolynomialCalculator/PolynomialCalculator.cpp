#include "PolynomialCalculator.h"
#include <iostream>


// MAIN WINDOW

PolynomialCalculator::PolynomialCalculator(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    addWidget = new AddPolynomialWidgetClass(this);
    errorWidget = new ErrorMessageWidgetClass();
    calculateWidget = new CalculatePolynomialWidgetClass(this);

    QObject::connect(ui.tableSelectorBox, &QComboBox::currentIndexChanged, this, &PolynomialCalculator::currentTableChanged);
    QObject::connect(ui.polynomialTable, &QTableWidget::cellClicked, this, &PolynomialCalculator::onPolynomialClicked);
    QObject::connect(ui.addButton, &QPushButton::clicked, this, &PolynomialCalculator::addPolynomialClicked);
    QObject::connect(ui.deleteButton, &QPushButton::clicked, this, &PolynomialCalculator::onDeletePolynomialClicked);
    QObject::connect(ui.calculatePolynomialButton, &QPushButton::clicked, this, &PolynomialCalculator::calculatePolynomialClicked);
    
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

    std::string fectiveName = ".", fectiveValue = "   ";
    cachedPolynomials.push_back({fectiveName, fectiveValue});

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
    if (x == cachedPolynomials.size() - 1) updateTable();
}

void PolynomialCalculator::addPolynomialClicked(bool a)
{
    addWidget->open();
}

void PolynomialCalculator::calculatePolynomialClicked(bool a)
{
    if (ui.polynomialTable->selectedRanges().size() > 0)
    {
        int selectedRow = ui.polynomialTable->selectedRanges().last().bottomRow();
        calculateWidget->open(cachedPolynomials[selectedRow].first, cachedPolynomials[selectedRow].second);
    }
}

void PolynomialCalculator::onDeletePolynomialClicked(bool a)
{
    if (ui.polynomialTable->selectedRanges().size() > 0)
    {
        for (auto& range: ui.polynomialTable->selectedRanges())
        {
            int top = range.topRow();
            int bottom = range.bottomRow();
            for (int i = top; i <= bottom; i++)
            {
                if (i != cachedPolynomials.size() - 1)
                {
                    std::string name = cachedPolynomials[i].first;
                    handler->deletePolynomial(name);
                }
            }
        }

        updateTable();
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


// CALCULATE POLYNOMIAL
CalculatePolynomialWidgetClass::CalculatePolynomialWidgetClass(PolynomialCalculator* inParentWindow, QWidget* parent): QWidget(parent)
{
    parentWindow = inParentWindow;

    selfUI.setupUi(this);

    QObject::connect(selfUI.calculateButton, &QPushButton::clicked, this, &CalculatePolynomialWidgetClass::onClickedCalculate);

    QObject::connect(selfUI.xBox, &QSpinBox::valueChanged, this, &CalculatePolynomialWidgetClass::onXChanged);
    QObject::connect(selfUI.yBox, &QSpinBox::valueChanged, this, &CalculatePolynomialWidgetClass::onYChanged);
    QObject::connect(selfUI.zBox, &QSpinBox::valueChanged, this, &CalculatePolynomialWidgetClass::onZChanged);

    QWidget::setWindowTitle(QString::fromStdString("Calculate Polynomial Value"));
}

void CalculatePolynomialWidgetClass::open(const std::string& polName, const std::string& polNotation)
{
    polynomialName = polName;
    selfUI.polynomialBox->setPlainText(QString::fromStdString(polNotation));

    cachedX = cachedY = cachedZ = 0;
    selfUI.xBox->setValue(0);
    selfUI.yBox->setValue(0);
    selfUI.zBox->setValue(0);

    selfUI.resultBox->setPlainText(QString());

    show();
}

void CalculatePolynomialWidgetClass::onXChanged(int newValue)
{
    cachedX = newValue;
}

void CalculatePolynomialWidgetClass::onYChanged(int newValue)
{
    cachedY = newValue;
}

void CalculatePolynomialWidgetClass::onZChanged(int newValue)
{
    cachedZ = newValue;
}

void CalculatePolynomialWidgetClass::onClickedCalculate(bool a)
{
    try
    {
        cachedResult = parentWindow->getHandler()->calculatePolynomialValue(polynomialName, cachedX, cachedY, cachedZ);
        selfUI.resultBox->setPlainText(QString::fromStdString(std::to_string(cachedResult)));
    }

    catch (std::exception e) { parentWindow->showErrorMessage(e.what()); }
}
