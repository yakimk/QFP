#ifndef PLOTWIDGET_HPP
#define PLOTWIDGET_HPP

#include <QWidget>
#include <QPointF>

class PlotWidget : public QWidget {
    Q_OBJECT

public:
    PlotWidget(QWidget *parent = nullptr);
    QSize sizeHint() const override;
    void setFunction(const QString &functionText);

protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QString m_functionText;
    double m_scale;
    double m_offsetX;
    double m_offsetY;
    QPointF m_lastPos;
    double evaluateFunction(double x);
    void adjustScale(int delta);
};

#endif // PLOTWIDGET_HPP
