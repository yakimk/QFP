#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include "PlotWidget.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createControls();
    void setupConnections();

private slots:
    void onApplyFunctions();
    void onShowHelp();

private:
    PlotWidget *plotWidget;
    QVBoxLayout *controlLayout;
    QVBoxLayout *settingsLayout;
    QLineEdit *functionEdits[5];
    QPushButton *applyFunctionsButton;
    QPushButton *showHelpButton;
    QLineEdit *epsilonEdit;
    QLineEdit *stepEdit;
    QLineEdit *domainMinEdit;
    QLineEdit *domainMaxEdit;
    QPushButton *toggleZerosButton;
    QPushButton *toggleIntersectionsButton;
};

#endif // MAINWINDOW_HPP
