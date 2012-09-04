#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include <QWidget>

class MainWindow;
class Vector2;
class DrawingData;

/*!
\brief Drawing widget.
*/
class DrawingWidget: public QWidget
{
    Q_OBJECT

    public:
        /*!
        \details Constructor.
        \param parent Parent MainWindow.
        */
        DrawingWidget(MainWindow* parent = 0);

        /*!
        \details Destructor.
        */
        ~DrawingWidget(void);

        /*!
        \details Sets the active tool.
        \param activeTool Active tool.
        \returns true if succeeded, false otherwize (tool identifier out of range or tool currently not permitted).
        */
        bool activeTool(int activeTool);

    private:
        MainWindow* m_mainWindow;
        DrawingData* m_drawingData;
        int m_activeTool;

        void mousePressEvent(QMouseEvent* event);
        void mouseMoveEvent(QMouseEvent* event);
        void mouseReleaseEvent(QMouseEvent* event);
        void paintEvent(QPaintEvent* event);
};

#endif // DRAWINGWIDGET_H
