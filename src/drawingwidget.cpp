#include "drawingwidget.h"

#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include "mainwindow.h"

#include "vector2.h"
#include "drawingdata.h"

DrawingWidget::DrawingWidget(MainWindow* parent) : QWidget(parent), m_mainWindow(parent)
{
    setMouseTracking(true);
    m_drawingData = new DrawingData;
    m_activeTool = -1;
}

DrawingWidget::~DrawingWidget(void)
{
    delete m_drawingData;
    m_drawingData = 0;
}

void DrawingWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.fillRect(event->rect(), Qt::white);

    const std::vector<Vector2*>* vertices = m_drawingData->vertices();
    int verticesCount = m_drawingData->verticesCount();
    int activeVertexIndex = m_drawingData->activeVertexIndex();
    int focusVertexIndex = m_drawingData->focusVertexIndex();
    int lineStartVertexIndex = m_drawingData->lineStartVertexIndex();

    const std::vector<Line2*>* lines = m_drawingData->lines();
    int linesCount = m_drawingData->linesCount();
    int focusLineIndex = m_drawingData->focusLineIndex();

    painter.setBrush(QBrush(Qt::black));
    painter.setPen(Qt::NoPen);

    for (int i = 0; i < verticesCount; i++)
    {
        Vector2* vertex = vertices->at(i);

        if (i == activeVertexIndex)
        {
            painter.setBrush(QBrush(Qt::darkGreen));
            painter.drawEllipse(vertex->m_x - 10, vertex->m_y - 10, 20, 20);
            painter.setBrush(QBrush(Qt::black));
        }
        else if (i == lineStartVertexIndex)
        {
            painter.setBrush(QBrush(Qt::darkGreen));
            painter.drawEllipse(vertex->m_x - 10, vertex->m_y - 10, 20, 20);
            painter.setBrush(QBrush(Qt::black));
        }
        else if (i == focusVertexIndex)
        {
            painter.setBrush(QBrush(Qt::red));
            painter.drawEllipse(vertex->m_x - 10, vertex->m_y - 10, 20, 20);
            painter.setBrush(QBrush(Qt::black));
        }
        else
        {
            painter.drawEllipse(vertex->m_x - 10, vertex->m_y - 10, 20, 20);
        }
    }

    painter.setPen(Qt::SolidLine);

    for (int i = 0; i < linesCount; i++)
    {
        Line2* line = lines->at(i);

        if (i == focusLineIndex)
        {
            painter.setPen(Qt::blue);
            painter.drawLine(line->p1->m_x, line->p1->m_y, line->p2->m_x, line->p2->m_y);
            painter.setPen(Qt::black);
        }
        else
        {
            painter.drawLine(line->p1->m_x, line->p1->m_y, line->p2->m_x, line->p2->m_y);
        }
    }

    m_mainWindow->updateStatusBar(m_drawingData->verticesCount(), m_drawingData->linesCount());
}

void DrawingWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() != Qt::LeftButton)
    {
        return;
    }

    int x = event->x();
    int y = event->y();
    int sizeX = this->size().width();
    int sizeY = this->size().height();

    if (x < 0 || x > sizeX || y < 0 || y > sizeY)
    {
        return;
    }

    switch(m_activeTool)
    {
    case 0:
        m_drawingData->addVertex(x, y);
        break;
    case 1:
        m_drawingData->activateVertex(x, y);
        break;
    case 2:
        m_drawingData->deleteVertex(x, y);
        break;
    case 3:
        m_drawingData->addLineVertex(x, y);
        break;
    case 4:
        m_drawingData->deleteLine(x, y);
        break;
    default:
        break;
    }

    m_drawingData->focus(x, y);
    repaint();
}

void DrawingWidget::mouseMoveEvent(QMouseEvent* event)
{
    int x = event->x();
    int y = event->y();
    int sizeX = this->size().width();
    int sizeY = this->size().height();

    if (x < 0 || x > sizeX || y < 0 || y > sizeY)
    {
        return;
    }

    switch(m_activeTool)
    {
    case 0:
        break;
    case 1:
        m_drawingData->moveActiveVertex(x, y);
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    default:
        break;
    }

    m_drawingData->focus(x, y);
    repaint();
}

void DrawingWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() != Qt::LeftButton)
    {
        return;
    }

    int x = event->x();
    int y = event->y();
    int sizeX = this->size().width();
    int sizeY = this->size().height();

    if (x < 0 || x > sizeX || y < 0 || y > sizeY)
    {
        return;
    }

    switch(m_activeTool)
    {
    case 0:
        break;
    case 1:
        m_drawingData->activateVertex(-1, -1);
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    default:
        break;
    }

    m_drawingData->focus(x, y);
    repaint();
}

bool DrawingWidget::activeTool(int activeTool)
{
    bool allowed = false;

    switch (activeTool)
    {
    case 0:
        allowed = (m_drawingData->lineStartVertexIndex() < 0);
        break;
    case 1:
        allowed = (m_drawingData->lineStartVertexIndex() < 0);
        break;
    case 2:
        allowed = (m_drawingData->lineStartVertexIndex() < 0);
        break;
    case 3:
        allowed = (m_drawingData->verticesCount() >= 2);
        break;
    case 4:
        allowed = (m_drawingData->lineStartVertexIndex() < 0);
        break;
    default:
        break;
    }

    if (allowed)
    {
        m_activeTool = activeTool;
    }

    return allowed;
}
