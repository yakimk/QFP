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

private:
    QLineEdit *functionInput;
    QPushButton *plotButton;
    QPushButton *quitButton;
    PlotWidget *plotWidget;
};

#endif // MAINWINDOW_HPP
