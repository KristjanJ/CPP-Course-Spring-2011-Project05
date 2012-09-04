#include "drawingdata.h"

#include <QDebug>

#include "vector2.h"

DrawingData::DrawingData(void)
{
    m_vertices = new std::vector<Vector2*>;
    m_activeVertexIndex = -1;
    m_activeVertexOriginalX = -1;
    m_activeVertexOriginalY = -1;
    m_focusVertexIndex = -1;

    m_lines = new std::vector<Line2*>;
    m_lineStartVertexIndex = -1;
    m_focusLineIndex = -1;
}

DrawingData::~DrawingData(void)
{
    for (unsigned int i = 0; i < m_vertices->size(); i++)
    {
        Vector2* vertex = (*m_vertices)[i];
        delete vertex;
        vertex = 0;
    }

    m_vertices->clear();
    delete m_vertices;
    m_vertices = 0;

    for (unsigned int i = 0; i < m_lines->size(); i++)
    {
        Line2* line = (*m_lines)[i];
        delete line;
        line = 0;
    }

    m_lines->clear();
    delete m_lines;
    m_lines = 0;
}

void DrawingData::addVertex(int x, int y)
{
    bool canAdd = true;
    int verticesCount = m_vertices->size();

    for (int i = 0; i < verticesCount; i++)
    {
        Vector2* vertex = (*m_vertices)[i];

        if (vertex->distanceFrom(x, y) <= 20)
        {
            canAdd = false;
            break;
        }
    }

    if (canAdd)
    {
        Vector2* vertex = new Vector2(x, y);
        m_vertices->push_back(vertex);
    }
}

void DrawingData::deleteVertex(int x, int y)
{
    int verticesCount = m_vertices->size();

    for (int i = 0; i < verticesCount; i++)
    {
        Vector2* vertex = (*m_vertices)[i];

        if (vertex->distanceFrom(x, y) <= 10)
        {
            int linesCount = m_lines->size();

            for (int j = 0; j < linesCount; j++)
            {
                Line2* line = (*m_lines)[j];

                if (line->p1 == vertex || line->p2 == vertex)
                {
                    m_lines->erase(m_lines->begin() + j);

                    delete line;
                    line = 0;

                    linesCount--;
                    j--;
                }
            }

            m_vertices->erase(m_vertices->begin() + i);

            delete vertex;
            vertex = 0;

            break;
        }
    }
}

void DrawingData::activateVertex(int x, int y)
{
    if (x == -1 && y == -1)
    {
        if (m_activeVertexIndex >= 0)
        {
            Vector2* activeVertex = (*m_vertices)[m_activeVertexIndex];

            int verticesCount = m_vertices->size();
            bool canLock = true;

            for (int i = 0; i < verticesCount; i++)
            {
                Vector2* vertex = (*m_vertices)[i];

                if ((vertex != activeVertex) && (vertex->distanceFrom(activeVertex->m_x, activeVertex->m_y) <= 20))
                {
                    canLock = false;
                    break;
                }
            }

            if (!canLock)
            {
                Vector2* vertex = (*m_vertices)[m_activeVertexIndex];
                vertex->m_x = m_activeVertexOriginalX;
                vertex->m_y = m_activeVertexOriginalY;
            }
        }

        m_activeVertexIndex = -1;
        m_activeVertexOriginalX = -1;
        m_activeVertexOriginalY = -1;
    }
    else
    {
        int verticesCount = m_vertices->size();

        for (int i = 0; i < verticesCount; i++)
        {
            Vector2* vertex = (*m_vertices)[i];

            if (vertex->distanceFrom(x, y) <= 10)
            {
                m_activeVertexIndex = i;
                m_activeVertexOriginalX = vertex->m_x;
                m_activeVertexOriginalY = vertex->m_y;
                break;
            }
        }
    }
}

void DrawingData::moveActiveVertex(int x, int y)
{
    if (m_activeVertexIndex >= 0)
    {
        (*m_vertices)[m_activeVertexIndex]->m_x = x;
        (*m_vertices)[m_activeVertexIndex]->m_y = y;
    }
}

void DrawingData::addLineVertex(int x, int y)
{
    int verticesCount = m_vertices->size();
    int lineVertex = -1;

    for (int i = 0; i < verticesCount; i++)
    {
        Vector2* vertex = (*m_vertices)[i];

        if (vertex->distanceFrom(x, y) <= 10 && i != m_lineStartVertexIndex)
        {
            lineVertex = i;
            break;
        }
    }

    if (m_lineStartVertexIndex < 0 && lineVertex >= 0)
    {
        m_lineStartVertexIndex = lineVertex;
        //qDebug("start");
    }
    else if (m_lineStartVertexIndex >= 0 && lineVertex >= 0)
    {
        Vector2* startPoint = (*m_vertices)[m_lineStartVertexIndex];
        Vector2* endPoint = (*m_vertices)[lineVertex];
        int x1 = startPoint->m_x;
        int y1 = startPoint->m_y;
        int x2 = endPoint->m_x;
        int y2 = endPoint->m_y;

        int linesCount = m_lines->size();
        bool canAdd = true;

        for (int i = 0; i < linesCount; i++)
        {
            Line2* line = (*m_lines)[i];
            int lx1 = line->p1->m_x;
            int ly1 = line->p1->m_y;
            int lx2 = line->p2->m_x;
            int ly2 = line->p2->m_y;

            if ((x1 == lx1 && y1 == ly1 && x2 == lx2 && y2 == ly2) ||
                            (x1 == lx2 && y1 == ly2 && x2 == lx1 && y2 == ly1))
            {
                canAdd = false;
                break;
            }
        }

        if (canAdd)
        {
            Line2* line = new Line2(startPoint, endPoint);
            m_lines->push_back(line);
            //qDebug("added line");
        }
        else
        {
            //qDebug("exists");
        }

        m_lineStartVertexIndex = -1;
    }
    else
    {
        m_lineStartVertexIndex = -1;
        //qDebug("cancel");
    }
}

void DrawingData::deleteLine(int x, int y)
{
    int linesCount = m_lines->size();

    for (int i = 0; i < linesCount; i++)
    {
        Line2* line = (*m_lines)[i];
        float distance = distanceLinePoint(line, x, y);

        if (distance <= 1)
        {
            m_lines->erase(m_lines->begin() + i);

            delete line;
            line = 0;

            break;
        }
    }
}

void DrawingData::focus(int x, int y)
{
    m_focusVertexIndex = -1;
    m_focusLineIndex = -1;

    int verticesCount = m_vertices->size();
    int linesCount = m_lines->size();

    for (int i = 0; i < verticesCount; i++)
    {
        Vector2* vertex = (*m_vertices)[i];

        if (i != m_activeVertexIndex && vertex->distanceFrom(x, y) <= 10)
        {
            m_focusVertexIndex = i;
            break;
        }
    }

    for (int i = 0; i < linesCount; i++)
    {
        Line2* line = (*m_lines)[i];

        if (distanceLinePoint(line, x, y) <= 1)
        {
            m_focusLineIndex = i;
            break;
        }
    }
}

int DrawingData::verticesCount(void) const
{
    return m_vertices->size();
}

const std::vector<Vector2*>* DrawingData::vertices(void) const
{
    return m_vertices;
}

int DrawingData::activeVertexIndex(void) const
{
    return m_activeVertexIndex;
}

int DrawingData::linesCount(void) const
{
    return m_lines->size();
}

const std::vector<Line2*>* DrawingData::lines(void) const
{
    return m_lines;
}

int DrawingData::lineStartVertexIndex(void) const
{
    return m_lineStartVertexIndex;
}

int DrawingData::focusVertexIndex(void) const
{
    return m_focusVertexIndex;
}

int DrawingData::focusLineIndex(void) const
{
    return m_focusLineIndex;
}

float DrawingData::distanceLinePoint(Line2* line, int x, int y)
{
    float distance = 0;

    int x1 = line->p1->m_x;
    int y1 = line->p1->m_y;
    int x2 = line->p2->m_x;
    int y2 = line->p2->m_y;
    int deltaX = x1 - x2;
    int deltaY = y1 - y2;

    float u = float((x - x1) * deltaX + (y - y1) * deltaY) / float(deltaX * deltaX + deltaY * deltaY);

    Vector2 closestPoint(x1 + u * deltaX, y1 + u * deltaY);

    distance = closestPoint.distanceFrom(x, y);

    return distance;
}
