#include "PlotWidget.hpp"
#include "Parser.hpp"
#include <QPainter>
#include <QPainterPath>
#include <QWheelEvent>
#include <QMouseEvent>
#include <cmath>  


PlotWidget::PlotWidget(QWidget *parent)
    : QWidget(parent), m_scale(50.0), m_offsetX(0.0), m_offsetY(0.0) {
}

QSize PlotWidget::sizeHint() const {
    return QSize(1920, 1080);
}

void PlotWidget::setFunction(const QString &functionText) {
    m_functionText = functionText;
    repaint();
}

void PlotWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Determine the widget dimensions
    int w = width();
    int h = height();

    // Set up the coordinate system
    painter.setWindow(-w / 2 + m_offsetX, -h / 2 + m_offsetY, w, h);

    // Draw axes
    painter.drawLine(-w / 2, 0, w / 2, 0); // x-axis
    painter.drawLine(0, -h / 2, 0, h / 2); // y-axis

    // Draw arrows on the axes
    painter.drawLine(w / 2 - 10, 5, w / 2, 0); // Arrow on positive x-axis
    painter.drawLine(w / 2 - 10, -5, w / 2, 0);

    painter.drawLine(-5, -h / 2 + 10, 0, -h / 2); // Arrow on negative y-axis
    painter.drawLine(5, -h / 2 + 10, 0, -h / 2);

    // Draw the numbers on the axes
    const int tickSpacing = 50; // Adjust this value for tick spacing
    const int numTicks = w / tickSpacing / 2;
    
    painter.setFont(QFont("Arial", 8));
    painter.setPen(Qt::black);
    for (int i = -numTicks; i <= numTicks; ++i) {
        int x = i * tickSpacing;
        int y = i * tickSpacing;
        
        // Draw x-axis numbers
        if (x != 0) {
            painter.drawLine(x, -5, x, 5);
            painter.drawText(x - 10, 15, QString::number(x / m_scale, 'f', 1));
        }
        
        // Draw y-axis numbers
        if (y != 0) {
            painter.drawLine(-5, y, 5, y);
            painter.drawText(10, y + 5, QString::number(-y / m_scale, 'f', 1)); // Negative because of coordinate system
        }
    }

    // Draw the function
    if (!m_functionText.isEmpty()) {
        QPainterPath path;
        double step = 0.1;
        bool firstPoint = true;
        for (double x = -w / 2; x < w / 2; x += step) {
            double y = evaluateFunction((x - m_offsetX) / m_scale) * m_scale + m_offsetY;
            if (firstPoint) {
                path.moveTo(x, -y);
                firstPoint = false;
            } else {
                path.lineTo(x, -y);
            }
        }
        painter.drawPath(path);
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
        m_offsetX -= dx * 2.0; 
        m_offsetY -= dy * 2.0; 
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

double PlotWidget::evaluateFunction(double x) {
    if (m_functionText == "") return std::sin(x);
    auto it = mathFunctions.find(m_functionText.toStdString());
    if (it != mathFunctions.end()) {

    double result = it->second(x);
    return result;
    }

    return 0.0;
}