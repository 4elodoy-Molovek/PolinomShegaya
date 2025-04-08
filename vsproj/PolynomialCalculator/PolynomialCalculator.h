#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PolynomialCalculator.h"
#include "ui_AddPolynomialWidget.h"
#include "PolynomialHandler.h"


class PolynomialCalculator : public QMainWindow
{
    Q_OBJECT

    PolynomialHandler* handler;
    class AddPolynomialWidgetClass* addWidget;

public:
    PolynomialCalculator(QWidget* parent = nullptr);
    ~PolynomialCalculator();

    void setHandler(PolynomialHandler* inHandler) { handler = inHandler; }
    PolynomialHandler* getHandler() { return handler; }

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
    AddPolynomialWidgetClass(PolynomialCalculator* inParentWindow, QWidget* parent = nullptr) : QWidget(parent), parentWindow(inParentWindow)
    {
        selfUI.setupUi(this);

        QObject::connect(selfUI.nameInputBox, &QTextEdit::textChanged, this, &AddPolynomialWidgetClass::onPolynomialNameChanged);
        QObject::connect(selfUI.polynomialNotationBox, &QTextEdit::textChanged, this, &AddPolynomialWidgetClass::onPolynomialNotationChanged);
        QObject::connect(selfUI.confirmButton, &QPushButton::clicked, this, &AddPolynomialWidgetClass::onClickedConfirm);
    }
    ~AddPolynomialWidgetClass() {}

signals:
public slots:

    void onPolynomialNameChanged() 
    {
        nameCache = selfUI.nameInputBox->toPlainText().toStdString();
    }

    void onPolynomialNotationChanged()
    {
        notationCache = selfUI.polynomialNotationBox->toPlainText().toStdString();
    }

    void onClickedConfirm(bool a) 
    {
        bool failure = false;

        if (nameCache.size() == 0 || notationCache.size() == 0) return;

        try
        {
            parentWindow->getHandler()->addPolynomial(nameCache, notationCache);
        }

        catch (std::exception e)
        {
            failure = true;
        }

        if (!failure)
            hide();
    }

private:
    Ui::AddPolynomialWidget selfUI;
};



