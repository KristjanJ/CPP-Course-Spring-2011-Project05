#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

class DrawingWidget;
class QLabel;

/*!
\brief Main window.
*/
class MainWindow: public QMainWindow
{
    Q_OBJECT

    public:
        /*!
        \details Constructor.
        \param parent Parent QWidget.
        */
        MainWindow(QWidget* parent = 0);

        /*!
        \details Destructor.
        */
        ~MainWindow(void);

        /*!
        \details Updates the 2nd and 3rd part of the status bar.
        \param verticesCount Vertices count.
        \param linesCount Lines count.
        */
        void updateStatusBar(int verticesCount, int linesCount);

    private:
        DrawingWidget* m_drawingWidget;
        QMenu* m_fileMenu;
        QAction* m_quitAction;
        QMenu* m_helpMenu;
        QAction* m_whatsThisAction;
        QAction* m_aboutQtAction;
        QMenu* m_toolsMenu;
        QAction* m_addVertexAction;
        QAction* m_moveVertexAction;
        QAction* m_deleteVertexAction;
        QAction* m_addLineAction;
        QAction* m_deleteLineAction;
        QStatusBar* m_statusBar;
        QLabel* m_activeToolLabel;
        QLabel* m_verticesCountLabel;
        QLabel* m_linesCountLabel;

        void initMenus(void);
        void addStatusBar(void);
        void retranslateUi(void);
        void changeEvent(QEvent* event);

    private slots:
        void addVertexAction(void);
        void moveVertexAction(void);
        void deleteVertexAction(void);
        void addLineAction(void);
        void deleteLineAction(void);
};

#endif // MAINWINDOW_H
