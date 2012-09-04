#ifndef DRAWINGDATA_H
#define DRAWINGDATA_H

#include <vector>

#include "dynamicline.h"

class Vector2;
typedef DynamicLine<Vector2> Line2;

/*!
\brief Drawing data.
*/
class DrawingData
{
public:
    /*!
    \details Default constructor.
    */
    DrawingData(void);

    /*!
    \details Destructor.
    */
    ~DrawingData(void);

    /*!
    \details Adds a vertex at (x, y).
    \param x X coordinate.
    \param y Y coordinate.
    */
    void addVertex(int x, int y);

    /*!
    \details Deletes a vertex at (x, y) (10px radius).
    \param x X coordinate.
    \param y Y coordinate.
    */
    void deleteVertex(int x, int y);

    /*!
    \details Activates a vertex at (x, y) (10px radius).
    \param x X coordinate.
    \param y Y coordinate.
    */
    void activateVertex(int x, int y);

    /*!
    \details Moves an active vertex to (x, y).
    \param x X coordinate.
    \param y Y coordinate.
    */
    void moveActiveVertex(int x, int y);

    /*!
    \details Adds a line vertex at (x, y).
    \param x X coordinate.
    \param y Y coordinate.
    */
    void addLineVertex(int x, int y);

    /*!
    \details Deletes a line at (x, y) (1px radius).
    \param x X coordinate.
    \param y Y coordinate.
    */
    void deleteLine(int x, int y);

    /*!
    \details Sets focus to vertices/lines at (x, y) (10px/1px radius).
    \param x X coordinate.
    \param y Y coordinate.
    */
    void focus(int x, int y);

    /*!
    \details Returns the amount of vertices.
    \returns Amount of vertices.
    */
    int verticesCount(void) const;

    /*!
    \details Returns all vertices.
    \returns All vertices.
    */
    const std::vector<Vector2*>* vertices(void) const;

    /*!
    \details Returns the index of an active vertex.
    \returns The index of an active vertex.
    */
    int activeVertexIndex(void) const;

    /*!
    \details Returns the index of a focused vertex.
    \returns The index of a focused vertex.
    */
    int focusVertexIndex(void) const;

    /*!
    \details Returns the amount of lines.
    \returns Amount of lines.
    */
    int linesCount(void) const;

    /*!
    \details Returns all lines.
    \returns All lines.
    */
    const std::vector<Line2*>* lines(void) const;

    /*!
    \details Returns the index of a line start vertex.
    \returns The index of a line start vertex.
    */
    int lineStartVertexIndex(void) const;

    /*!
    \details Returns the index of a focused line.
    \returns The index of a focused line.
    */
    int focusLineIndex(void) const;

private:
    std::vector<Vector2*>* m_vertices;
    int m_activeVertexIndex;
    int m_activeVertexOriginalX;
    int m_activeVertexOriginalY;

    std::vector<Line2*>* m_lines;
    int m_lineStartVertexIndex;

    int m_focusVertexIndex;
    int m_focusLineIndex;

    float distanceLinePoint(Line2* line, int x, int y);
};

#endif // DRAWINGDATA_H
