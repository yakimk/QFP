#include "MainWindow.hpp"
#include <QMessageBox>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), plotWidget(new PlotWidget(this)) {
    
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create the main layout
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    controlLayout = new QVBoxLayout();
    settingsLayout = new QVBoxLayout();

    // Create and configure the control panel
    createControls();

    // Add control panel to the left side
    QFrame *leftFrame = new QFrame(this);
    QVBoxLayout *leftLayout = new QVBoxLayout(leftFrame);
    leftLayout->addLayout(controlLayout);
    QFrame *horizontalLine = new QFrame(this);
    horizontalLine->setFrameShape(QFrame::HLine);
    horizontalLine->setFrameShadow(QFrame::Sunken);
    leftLayout->addWidget(horizontalLine);
    leftLayout->addLayout(settingsLayout);

    // Add the control panel and the plot widget to the main layout
    mainLayout->addWidget(leftFrame, 1); // 20% of the screen width

    QFrame *verticalLine = new QFrame(this);
    verticalLine->setFrameShape(QFrame::VLine);
    verticalLine->setFrameShadow(QFrame::Sunken);
    mainLayout->addWidget(verticalLine);

    mainLayout->addWidget(plotWidget, 4); // 80% of the screen width

    leftFrame->setStyleSheet("background-color: #2E2E2E; color: white;");
    setupConnections();
}

MainWindow::~MainWindow() {}

void MainWindow::createControls() {
    QLabel *titleLabel = new QLabel("QFP", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");

    controlLayout->addWidget(titleLabel);

    for (int i = 0; i < 5; ++i) {
        functionEdits[i] = new QLineEdit(this);
        functionEdits[i]->setPlaceholderText(QString("Function %1").arg(i + 1));
        controlLayout->addWidget(functionEdits[i]);
    }

    applyFunctionsButton = new QPushButton("Apply Functions", this);
    controlLayout->addWidget(applyFunctionsButton);

    // Add the "Settings" title
    QLabel *settingsLabel = new QLabel("Settings", this);
    settingsLabel->setAlignment(Qt::AlignCenter);
    settingsLabel->setStyleSheet("font-size: 18px; font-weight: bold;");
    settingsLayout->addWidget(settingsLabel);

    QHBoxLayout *epsilonStepLayout = new QHBoxLayout();
    QLabel *epsilonLabel = new QLabel("Epsilon:", this);
    epsilonEdit = new QLineEdit(this);
    epsilonEdit->setPlaceholderText("Epsilon");
    epsilonEdit->setText("0.005");
    epsilonStepLayout->addWidget(epsilonLabel);
    epsilonStepLayout->addWidget(epsilonEdit);

    QLabel *stepLabel = new QLabel("Step:", this);
    stepEdit = new QLineEdit(this);
    stepEdit->setPlaceholderText("Step");
    stepEdit->setText("0.01");
    epsilonStepLayout->addWidget(stepLabel);
    epsilonStepLayout->addWidget(stepEdit);

    settingsLayout->addLayout(epsilonStepLayout);

    QHBoxLayout *domainLayout = new QHBoxLayout();
    QLabel *domainMinLabel = new QLabel("Domain Min:", this);
    domainMinEdit = new QLineEdit(this);
    domainMinEdit->setPlaceholderText("Domain Min");
    domainMinEdit->setText("-10");
    domainLayout->addWidget(domainMinLabel);
    domainLayout->addWidget(domainMinEdit);

    QLabel *domainMaxLabel = new QLabel("Domain Max:", this);
    domainMaxEdit = new QLineEdit(this);
    domainMaxEdit->setPlaceholderText("Domain Max");
    domainMaxEdit->setText("10");
    domainLayout->addWidget(domainMaxLabel);
    domainLayout->addWidget(domainMaxEdit);

    settingsLayout->addLayout(domainLayout);

    QHBoxLayout *toggleButtonsLayout = new QHBoxLayout();
    toggleZerosButton = new QPushButton("Toggle Zeros", this);
    toggleIntersectionsButton = new QPushButton("Toggle Intersections", this);
    toggleButtonsLayout->addWidget(toggleZerosButton);
    toggleButtonsLayout->addWidget(toggleIntersectionsButton);

    settingsLayout->addLayout(toggleButtonsLayout);

    QHBoxLayout *bottomControlsLayout = new QHBoxLayout();

    showHelpButton = new QPushButton("?", this);
    showHelpButton->setFixedSize(30, 30);
    bottomControlsLayout->addWidget(showHelpButton, 0, Qt::AlignLeft);

    // Add quit button
    QPushButton *quitButton = new QPushButton("Quit", this);
    bottomControlsLayout->addWidget(quitButton, 0, Qt::AlignRight);
    connect(quitButton, &QPushButton::clicked, this, &MainWindow::close);

    settingsLayout->addStretch(); 
    settingsLayout->addLayout(bottomControlsLayout);
}

void MainWindow::setupConnections() {
    connect(applyFunctionsButton, &QPushButton::clicked, this, &MainWindow::onApplyFunctions);
    connect(showHelpButton, &QPushButton::clicked, this, &MainWindow::onShowHelp);
    connect(toggleZerosButton, &QPushButton::clicked, plotWidget, &PlotWidget::toggleZeros);
    connect(toggleIntersectionsButton, &QPushButton::clicked, plotWidget, &PlotWidget::toggleIntersections);

    // Connect Enter key to apply functions
    for (int i = 0; i < 5; ++i) {
        connect(functionEdits[i], &QLineEdit::returnPressed, this, &MainWindow::onApplyFunctions);
    }
    connect(epsilonEdit, &QLineEdit::returnPressed, this, &MainWindow::onApplyFunctions);
    connect(stepEdit, &QLineEdit::returnPressed, this, &MainWindow::onApplyFunctions);
    connect(domainMinEdit, &QLineEdit::returnPressed, this, &MainWindow::onApplyFunctions);
    connect(domainMaxEdit, &QLineEdit::returnPressed, this, &MainWindow::onApplyFunctions);
}

void MainWindow::onApplyFunctions() {
    QStringList functions;
    for (int i = 0; i < 5; ++i) {
        functions << functionEdits[i]->text();
    }

    plotWidget->setFunctions(functions);
    plotWidget->setEpsilon(epsilonEdit->text().toDouble());
    plotWidget->setStep(stepEdit->text().toDouble());
    plotWidget->setDomain(domainMinEdit->text().toDouble(), domainMaxEdit->text().toDouble());
    plotWidget->repaint();
}

void MainWindow::onShowHelp() {
    QMessageBox::information(this, "Help", "This is a simple function plotter.\n\n"
                                           "Enter functions in the text fields.\n"
                                           "Set the epsilon and step values to control precision.\n"
                                           "Set the domain range to control the displayed range.\n"
                                           "Click 'Apply Functions' or press Enter to update the plot.");
}
