#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PolynomialCalculator.h"
#include "ui_AddPolynomialWidget.h"
#include "ui_ErrorMessageWidget.h"
#include "ui_CalculatePolynomialWidget.h"
#include "PolynomialHandler.h"


class PolynomialCalculator : public QMainWindow
{
    Q_OBJECT

    PolynomialHandler* handler;
    class AddPolynomialWidgetClass* addWidget;
    class ErrorMessageWidgetClass* errorWidget;
    class CalculatePolynomialWidgetClass* calculateWidget;

    // Таблица
    std::vector<std::pair<const std::string&, std::string>> cachedPolynomials;
    int selectedRow = -1;


protected:


public:
    PolynomialCalculator(QWidget* parent = nullptr);
    ~PolynomialCalculator();

    void setHandler(PolynomialHandler* inHandler) { handler = inHandler; updateTable(); }
    PolynomialHandler* getHandler() { return handler; }

    void updateTable();

    void showErrorMessage(const std::string& errorMessage);

    void resetSelectedRow() { selectedRow = -1; }

signals:

public slots:

    void currentTableChanged(int newTable);
    void onPolynomialClicked(int x, int y);
    void addPolynomialClicked(bool a);
    void calculatePolynomialClicked(bool a);
    void onDeletePolynomialClicked(bool a);

    void onInputExpressionChanged();
    void onClickedCalculate(bool a);
    void onClickedSave(bool a);


private:
    Ui::PolynomialCalculatorClass ui;
};




class AddPolynomialWidgetClass : public QWidget
{
    Q_OBJECT

    PolynomialCalculator* parentWindow;
    std::string nameCache;
    std::string notationCache;

public:
    AddPolynomialWidgetClass(PolynomialCalculator* inParentWindow, QWidget* parent = nullptr);
    ~AddPolynomialWidgetClass() {}

    void open();

    void openSaveMode(const std::string& polynomialExpression);

signals:
public slots:

    void onPolynomialNameChanged();

    void onPolynomialNotationChanged();

    void onClickedConfirm(bool a);

private:
    Ui::AddPolynomialWidget selfUI;
};



class CalculatePolynomialWidgetClass : public QWidget
{
    Q_OBJECT

    PolynomialCalculator* parentWindow;
    std::string polynomialName;

    int cachedX = 0, cachedY = 0, cachedZ = 0;
    long cachedResult = 0;

public:
    CalculatePolynomialWidgetClass(PolynomialCalculator* inParentWindow, QWidget* parent = nullptr);
    ~CalculatePolynomialWidgetClass() {}

    void open(const std::string& polName, const std::string& polNotation);

signals:
public slots:

    void onXChanged(int newValue);
    void onYChanged(int newValue);
    void onZChanged(int newValue);

    void onClickedCalculate(bool a);

private:
    Ui::CalculatePolynomialWidget selfUI;
};



class ErrorMessageWidgetClass : public QWidget
{
    Q_OBJECT

public:
    ErrorMessageWidgetClass(QWidget* parent = nullptr);
    ~ErrorMessageWidgetClass() {}

    void open(const std::string& errorMessage);

signals:
public slots:

    void onClickedOk(bool a);


private:
    Ui::ErrorMessageWidget selfUI;
};



