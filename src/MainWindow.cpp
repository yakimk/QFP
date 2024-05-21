#include "MainWindow.hpp"
#include <QVBoxLayout>
#include <QApplication>
#include <QKeyEvent>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    // Create the text input fields
    functionInput1 = new QLineEdit(this);
    functionInput1->setPlaceholderText("Enter function 1 (e.g., sin(x))");
    functionInput2 = new QLineEdit(this);
    functionInput2->setPlaceholderText("Enter function 2 (e.g., cos(x))");
    functionInput3 = new QLineEdit(this);
    functionInput3->setPlaceholderText("Enter function 3 (e.g., tan(x))");
    functionInput4 = new QLineEdit(this);
    functionInput4->setPlaceholderText("Enter function 4 (e.g., exp(x))");
    functionInput5 = new QLineEdit(this);
    functionInput5->setPlaceholderText("Enter function 5 (e.g., log(x))");

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
    layout->addWidget(functionInput1);
    layout->addWidget(functionInput2);
    layout->addWidget(functionInput3);
    layout->addWidget(functionInput4);
    layout->addWidget(functionInput5);
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
    QStringList functionTexts;
    functionTexts << functionInput1->text() << functionInput2->text()
                  << functionInput3->text() << functionInput4->text()
                  << functionInput5->text();
    plotWidget->setFunctions(functionTexts);
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
