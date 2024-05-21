#include "MainWindow.hpp"
#include <QVBoxLayout>
#include <QApplication>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    // Create the text input field
    functionInput = new QLineEdit(this);
    functionInput->setPlaceholderText("Enter function (e.g., sin(x))");

    // Create the plot button
    plotButton = new QPushButton("Plot", this);
    connect(plotButton, &QPushButton::clicked, this, &MainWindow::plotFunction);

    // Create the quit button
    quitButton = new QPushButton("Quit", this);
    connect(quitButton, &QPushButton::clicked, this, &MainWindow::quitApplication);

    // Create the plot widget
    plotWidget = new PlotWidget(this);

    // Create a layout
    QVBoxLayout *layout = new QVBoxLayout;

    // Add widgets to the layout
    layout->addWidget(functionInput);
    layout->addWidget(plotButton);
    layout->addWidget(quitButton);
    layout->addWidget(plotWidget);

    // Set the layout to the central widget
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {
}

void MainWindow::plotFunction() {
    QString functionText = functionInput->text();
    plotWidget->setFunction(functionText);
    plotWidget->repaint();
}

void MainWindow::quitApplication() {
    qApp->quit();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        plotFunction();
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Q) {
        quitApplication();
    } else {
        QMainWindow::keyPressEvent(event);
    }
}
