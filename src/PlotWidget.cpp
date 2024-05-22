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
    m_functionColors = {Qt::red, Qt::blue, Qt::darkYellow, Qt::magenta, Qt::cyan};
}

QSize PlotWidget::sizeHint() const {
    return QSize(800, 600);
}

void PlotWidget::setFunctions(const QStringList &functionTexts) {
    m_functionTexts.clear();
    m_functions.clear();
    for (const auto &text : functionTexts) {
        if (!text.isEmpty()) {
            std::function<double(double)> func;
            try { 
                func = parseFunction(text.toStdString());
            }
            catch (std::invalid_argument&) { // in this implementation std::invalid_argument is a sort of parser exception
                continue;
            }

            m_functionTexts.append(text);
            m_functions.append(func);
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

void PlotWidget::setEpsilon(double epsilon) {
    m_epsilon = epsilon;
}

void PlotWidget::setStep(double step) {
    m_step = step;
}

void PlotWidget::setDomain(double min, double max) {
    m_domainMin = min;
    m_domainMax = max;
}

void PlotWidget::paintEvent(__attribute__((unused))QPaintEvent *event) {
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    int w = width();
    int h = height();

    painter.setWindow(-w / 2 + m_offsetX, -h / 2 + m_offsetY, w, h);

    QPen axisPen(Qt::black, 1, Qt::DashLine);
    painter.setPen(axisPen);

    painter.drawLine(m_offsetX - w, 0, m_offsetX + w, 0);

    painter.drawLine(0, m_offsetY - h, 0, m_offsetY + h);
    

    const int tickSpacing = 50;
    QFont font("Arial", 8);
    painter.setFont(font);
    painter.setPen(Qt::black);

    // Draw x-axis ticks and numbers
    for (int i = m_offsetX / tickSpacing - w / tickSpacing; i <= m_offsetX / tickSpacing + w / tickSpacing; ++i) {
        int x = i * tickSpacing;
        painter.drawLine(x, -5, x, 5);
        if (x != 0) {
            painter.drawText(x - 10, 15, QString::number(x / m_scale, 'f', 1));
        }
    }

    // Draw y-axis ticks and numbers
    for (int i = m_offsetY / tickSpacing - h / tickSpacing; i <= m_offsetY / tickSpacing + h / tickSpacing; ++i) {
        int y = i * tickSpacing;
        painter.drawLine(-5, y, 5, y);
        if (y != 0) {
            painter.drawText(10, y + 5, QString::number(-y / m_scale, 'f', 1));
        }
    }

    for (int i = 0; i < m_functions.size(); ++i) {
        auto &func = m_functions[i];
        QColor color = m_functionColors[i % m_functionColors.size()];
        painter.setPen(color);

        QPainterPath path;
        double step = 0.1;
        bool firstPoint = true;
        for (double x = m_offsetX - w / 2; x <= m_offsetX + w / 2; x += step * m_scale) {
            double y = func((x) / m_scale) * m_scale;
            if (firstPoint) {
                path.moveTo(x, -y);
                firstPoint = false;
            } else {
                path.lineTo(x, -y);
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

void PlotWidget::mouseReleaseEvent(__attribute__((unused))QMouseEvent *event) {

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

void PlotWidget::adjustScale(int delta) {
    constexpr double scaleFactor = 1.1;
    if (delta > 0) {
        m_scale *= scaleFactor;
    } else {
        m_scale /= scaleFactor;
    }
}

QVector<QPointF> PlotWidget::findIntersections() {
    QVector<QPointF> points;
    if (m_functionTexts.size() < 2) return points;

    for (int i = 0; i < m_functions.size() - 1; ++i) {
        for (int j = i + 1; j < m_functions.size(); ++j) {
            for (double x = m_domainMin; x <= m_domainMax; x += m_step) {
                double y1 = m_functions[i](x);
                double y2 = m_functions[j](x);
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
    for (const auto &func : m_functions) {
        for (double x = m_domainMin; x <= m_domainMax; x += m_step) {
            double y = func(x);
            if (std::abs(y) < m_epsilon) {
                points.append(QPointF(x * m_scale, 0));
            }
        }
    }
    return points;
}