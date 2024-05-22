#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QDoubleValidator>
#include "PlotWidget.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    QHBoxLayout *mainLayout = new QHBoxLayout(&window);

    QWidget *leftPanel = new QWidget;
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);

    // Function input fields
    QList<QLineEdit*> functionEdits;
    for (int i = 0; i < 5; ++i) {
        QLineEdit *functionEdit = new QLineEdit;
        functionEdit->setPlaceholderText("Enter function " + QString::number(i + 1));
        functionEdits.append(functionEdit);
        leftLayout->addWidget(functionEdit);
    }

    QPushButton *applyFunctionsButton = new QPushButton("Apply Functions");

    // Toggle buttons
    QPushButton *toggleZerosButton = new QPushButton("Toggle Zeros");
    QPushButton *toggleIntersectionsButton = new QPushButton("Toggle Intersections");

    // Epsilon input field
    QLineEdit *epsilonEdit = new QLineEdit;
    QDoubleValidator *epsilonValidator = new QDoubleValidator(0.0000001, 100, 7);
    epsilonEdit->setValidator(epsilonValidator);
    epsilonEdit->setText("0.005");

    // Step input field
    QLineEdit *stepEdit = new QLineEdit;
    QDoubleValidator *stepValidator = new QDoubleValidator(0.0000001, 100, 7);
    stepEdit->setValidator(stepValidator);
    stepEdit->setText("0.01");

    // Domain min input field
    QLineEdit *domainMinEdit = new QLineEdit;
    QDoubleValidator *domainValidator = new QDoubleValidator(-1000000, 1000000, 7);
    domainMinEdit->setValidator(domainValidator);
    domainMinEdit->setText("-10");

    // Domain max input field
    QLineEdit *domainMaxEdit = new QLineEdit;
    domainMaxEdit->setValidator(domainValidator);
    domainMaxEdit->setText("10");

    // Apply button for epsilon, step, and domain
    QPushButton *applyButton = new QPushButton("Apply Settings");

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("Epsilon:", epsilonEdit);
    formLayout->addRow("Step:", stepEdit);
    formLayout->addRow("Domain Min:", domainMinEdit);
    formLayout->addRow("Domain Max:", domainMaxEdit);
    formLayout->addRow(applyButton);

    leftLayout->addWidget(applyFunctionsButton);
    leftLayout->addWidget(toggleZerosButton);
    leftLayout->addWidget(toggleIntersectionsButton);
    leftLayout->addLayout(formLayout);

    // Plot widget
    PlotWidget *plotWidget = new PlotWidget;

    // Main layout
    mainLayout->addWidget(leftPanel);
    mainLayout->addWidget(plotWidget);
    leftPanel->setFixedWidth(200); // 20% of 1000px width window

    // Connections
    QObject::connect(applyFunctionsButton, &QPushButton::clicked, [&]() {
        QStringList functionTexts;
        for (QLineEdit *edit : functionEdits) {
            functionTexts.append(edit->text());
        }
        plotWidget->setFunctions(functionTexts);
    });

    QObject::connect(toggleZerosButton, &QPushButton::clicked, plotWidget, &PlotWidget::toggleZeros);
    QObject::connect(toggleIntersectionsButton, &QPushButton::clicked, plotWidget, &PlotWidget::toggleIntersections);

    QObject::connect(applyButton, &QPushButton::clicked, [&]() {
        double epsilon = epsilonEdit->text().toDouble();
        double step = stepEdit->text().toDouble();
        double domainMin = domainMinEdit->text().toDouble();
        double domainMax = domainMaxEdit->text().toDouble();

        plotWidget->setEpsilon(epsilon);
        plotWidget->setStep(step);
        plotWidget->setDomain(domainMin, domainMax);
    });

    window.setWindowTitle("Function Plotter");
    window.resize(1000, 600);
    window.show();

    return app.exec();
}
