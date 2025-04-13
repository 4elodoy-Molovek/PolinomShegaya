#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PolynomialCalculator.h"
#include "ui_AddPolynomialWidget.h"
#include "ui_ErrorMessageWidget.h"
#include "PolynomialHandler.h"


class PolynomialCalculator : public QMainWindow
{
    Q_OBJECT

    PolynomialHandler* handler;
    class AddPolynomialWidgetClass* addWidget;
    class ErrorMessageWidgetClass* errorWidget;

    // Таблица
    std::vector<std::pair<const std::string&, std::string>> cachedPolynomials;
    int selectedRow = -1;


protected:


public:
    PolynomialCalculator(QWidget* parent = nullptr);
    ~PolynomialCalculator();

    void setHandler(PolynomialHandler* inHandler) { handler = inHandler; }
    PolynomialHandler* getHandler() { return handler; }

    void updateTable();

    void showErrorMessage(const std::string& errorMessage);

signals:

public slots:

    void currentTableChanged(int newTable);
    void onPolynomialClicked(int x, int y);
    void addPolynomialClicked(bool a);
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



