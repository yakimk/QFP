#include "MainWindow.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
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

    // Create the domain range inputs
    domainMinInput = new QLineEdit(this);
    domainMinInput->setPlaceholderText("Min domain");
    domainMaxInput = new QLineEdit(this);
    domainMaxInput->setPlaceholderText("Max domain");

    connect(domainMinInput, &QLineEdit::editingFinished, this, &MainWindow::updateDomain);
    connect(domainMaxInput, &QLineEdit::editingFinished, this, &MainWindow::updateDomain);

    // Create epsilon and step inputs
    epsilonInput = new QLineEdit(this);
    epsilonInput->setPlaceholderText("Epsilon");
    stepInput = new QLineEdit(this);
    stepInput->setPlaceholderText("Step");

    connect(epsilonInput, &QLineEdit::editingFinished, this, &MainWindow::updateEpsilon);
    connect(stepInput, &QLineEdit::editingFinished, this, &MainWindow::updateStep);

    // Create the plot button
    plotButton = new QPushButton("Plot", this);
    connect(plotButton, &QPushButton::clicked, this, &MainWindow::plotFunction);

    // Create the quit button
    quitButton = new QPushButton("Quit", this);
    connect(quitButton, &QPushButton::clicked, this, &MainWindow::quitApplication);

    // Create the intersection toggle button
    intersectionsButton = new QPushButton("Toggle Intersections", this);
    connect(intersectionsButton, &QPushButton::clicked, this, &MainWindow::toggleIntersections);

    // Create the zeros toggle button
    zerosButton = new QPushButton("Toggle Zeros", this);
    connect(zerosButton, &QPushButton::clicked, this, &MainWindow::toggleZeros);

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
    layout->addWidget(new QLabel("Domain Range:"));
    QHBoxLayout *domainLayout = new QHBoxLayout;
    domainLayout->addWidget(domainMinInput);
    domainLayout->addWidget(domainMaxInput);
    layout->addLayout(domainLayout);
    layout->addWidget(new QLabel("Epsilon:"));
    layout->addWidget(epsilonInput);
    layout->addWidget(new QLabel("Step:"));
    layout->addWidget(stepInput);
    layout->addWidget(plotButton);
    layout->addWidget(intersectionsButton);
    layout->addWidget(zerosButton);
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

void MainWindow::toggleIntersections() {
    plotWidget->toggleIntersections();
}

void MainWindow::toggleZeros() {
    plotWidget->toggleZeros();
}

void MainWindow::updateDomain() {
    bool okMin, okMax;
    double min = domainMinInput->text().toDouble(&okMin);
    double max = domainMaxInput->text().toDouble(&okMax);

    if (okMin && okMax && min < max) {
        plotWidget->setDomain(min, max);
        plotWidget->repaint();
    }
}

void MainWindow::updateEpsilon() {
    bool ok;
    double epsilon = epsilonInput->text().toDouble(&ok);

    if (ok) {
        plotWidget->setEpsilon(epsilon);
        plotWidget->repaint();
    }
}

void MainWindow::updateStep() {
    bool ok;
    double step = stepInput->text().toDouble(&ok);

    if (ok) {
        plotWidget->setStep(step);
        plotWidget->repaint();
    }
}
