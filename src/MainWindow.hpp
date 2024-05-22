#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include "PlotWidget.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void plotFunction();
    void quitApplication();
    void toggleIntersections();
    void toggleZeros();
    void updateDomain();
    void updateEpsilon();
    void updateStep();

private:
    QLineEdit *functionInput1;
    QLineEdit *functionInput2;
    QLineEdit *functionInput3;
    QLineEdit *functionInput4;
    QLineEdit *functionInput5;
    QLineEdit *domainMinInput;
    QLineEdit *domainMaxInput;
    QLineEdit *epsilonInput;
    QLineEdit *stepInput;
    QPushButton *plotButton;
    QPushButton *quitButton;
    QPushButton *intersectionsButton;
    QPushButton *zerosButton;
    PlotWidget *plotWidget;
};

#endif // MAINWINDOW_HPP
