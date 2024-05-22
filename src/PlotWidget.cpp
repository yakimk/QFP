#include "PlotWidget.hpp"
#include "Parser.hpp"
#include <QPainter>
#include <QPainterPath>
#include <QWheelEvent>
#include <QMouseEvent>
#include <cmath>

PlotWidget::PlotWidget(QWidget *parent)
    : QWidget(parent), m_scale(50.0), m_offsetX(0.0), m_offsetY(0.0), 
      m_domainMin(-10.0), m_domainMax(10.0), m_epsilon(0.005), m_step(0.01),
      showIntersections(false), showZeros(false) {
    m_functionColors = {Qt::red, Qt::blue, Qt::green, Qt::magenta, Qt::cyan};
}

QSize PlotWidget::sizeHint() const {
    return QSize(800, 600);
}

void PlotWidget::setFunctions(const QStringList &functionTexts) {
    m_functionTexts.clear();
    for (const auto &text : functionTexts) {
        if (!text.isEmpty()) {
            m_functionTexts.append(text);
        }
    }
    repaint();
}

void PlotWidget::toggleIntersections() {
    showIntersections = !showIntersections;
    repaint();
}

void PlotWidget::toggleZeros() {
    showZeros = !showZeros;
    repaint();
}

void PlotWidget::setDomain(double min, double max) {
    m_domainMin = min;
    m_domainMax = max;
    repaint();
}

void PlotWidget::setEpsilon(double epsilon) {
    m_epsilon = epsilon;
    repaint();
}

void PlotWidget::setStep(double step) {
    m_step = step;
    repaint();
}

void PlotWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    int w = width();
    int h = height();

    painter.setWindow(-w / 2 + m_offsetX, -h / 2 + m_offsetY, w, h);

    // Draw infinite axes
    QPen axisPen(Qt::black, 1, Qt::DashLine);
    painter.setPen(axisPen);

    // Draw x-axis
    painter.drawLine(m_offsetX - w, 0, m_offsetX + w, 0);
    // Draw y-axis
    painter.drawLine(0, m_offsetY - h, 0, m_offsetY + h);

    // Draw the functions
    for (int i = 0; i < m_functionTexts.size(); ++i) {
        const QString &functionText = m_functionTexts[i];
        QColor color = m_functionColors[i % m_functionColors.size()];
        painter.setPen(color);

        QPainterPath path;
        bool firstPoint = true;
        for (double x = m_domainMin; x <= m_domainMax; x += m_step) {
            double y = evaluateFunction(x, functionText);
            if (firstPoint) {
                path.moveTo(x * m_scale, -y * m_scale);
                firstPoint = false;
            } else {
                path.lineTo(x * m_scale, -y * m_scale);
            }
        }
        painter.drawPath(path);
    }

    if (showIntersections) {
        QVector<QPointF> intersections = findIntersections();
        painter.setPen(Qt::red);
        painter.setBrush(Qt::red);
        for (const auto &point : intersections) {
            painter.drawEllipse(point, 3, 3);
        }
    }

    if (showZeros) {
        QVector<QPointF> zeros = findZeros();
        painter.setPen(Qt::blue);
        painter.setBrush(Qt::blue);
        for (const auto &point : zeros) {
            painter.drawEllipse(point, 3, 3);
        }
    }
}

void PlotWidget::wheelEvent(QWheelEvent *event) {
    adjustScale(event->angleDelta().y());
    repaint();
}

void PlotWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_lastPos = event->pos();
    }
}

void PlotWidget::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        int dx = event->x() - m_lastPos.x();
        int dy = event->y() - m_lastPos.y();
        m_offsetX -= dx;
        m_offsetY -= dy;
        m_lastPos = event->pos();
        repaint();
    }
}

void PlotWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // Do nothing for now
    }
}

void PlotWidget::adjustScale(int delta) {
    constexpr double scaleFactor = 1.1;
    if (delta > 0) {
        m_scale *= scaleFactor;
    } else {
        m_scale /= scaleFactor;
    }
}

double PlotWidget::evaluateFunction(double x, const QString &functionText) {
    if (functionText.isEmpty()) return 0.0;
    auto it = mathFunctions.find(functionText.toStdString());
    if (it != mathFunctions.end()) {
        double result = it->second(x);
        return result;
    }
    return 0.0;
}

QVector<QPointF> PlotWidget::findIntersections() {
    QVector<QPointF> points;
    if (m_functionTexts.size() < 2) return points;

    for (int i = 0; i < m_functionTexts.size() - 1; ++i) {
        for (int j = i + 1; j < m_functionTexts.size(); ++j) {
            for (double x = m_domainMin; x <= m_domainMax; x += m_step) {
                double y1 = evaluateFunction(x, m_functionTexts[i]);
                double y2 = evaluateFunction(x, m_functionTexts[j]);
                if (std::abs(y1 - y2) < m_epsilon) {
                    points.append(QPointF(x * m_scale, -y1 * m_scale));
                }
            }
        }
    }
    return points;
}

QVector<QPointF> PlotWidget::findZeros() {
    QVector<QPointF> points;

    for (const auto &functionText : m_functionTexts) {
        for (double x = m_domainMin; x <= m_domainMax; x += m_step) {
            double y = evaluateFunction(x, functionText);
            if (std::abs(y) < m_epsilon) {
                points.append(QPointF(x * m_scale, 0));
            }
        }
    }
    return points;
}
