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
    QPointF m_lastPos;
    double evaluateFunction(double x, const QString &functionText);
    void adjustScale(int delta);
};

#endif // PLOTWIDGET_HPP
