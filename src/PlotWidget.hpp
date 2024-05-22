#ifndef PLOTWIDGET_HPP
#define PLOTWIDGET_HPP

#include <QWidget>
#include <QPointF>
#include <QStringList>
#include <QVector>
#include <QColor>

class PlotWidget : public QWidget {
    Q_OBJECT

public:
    PlotWidget(QWidget *parent = nullptr);
    QSize sizeHint() const override;
    void setFunctions(const QStringList &functionTexts);
    void toggleIntersections();
    void toggleZeros();
    void setDomain(double min, double max);
    void setEpsilon(double epsilon);
    void setStep(double step);

protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QStringList m_functionTexts;
    QVector<QColor> m_functionColors;
    double m_scale;
    double m_offsetX;
    double m_offsetY;
    double m_domainMin;
    double m_domainMax;
    double m_epsilon;
    double m_step;
    QPointF m_lastPos;
    bool showIntersections;
    bool showZeros;

    QVector<QPointF> findIntersections();
    QVector<QPointF> findZeros();
    double evaluateFunction(double x, const QString &functionText);
    void adjustScale(int delta);
};

#endif // PLOTWIDGET_HPP
