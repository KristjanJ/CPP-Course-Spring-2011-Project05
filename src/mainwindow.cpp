#include "mainwindow.h"

#include <QAction>
#include <QApplication>
#include <QEvent>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QLabel>
#include <QWhatsThis>
#include "drawingwidget.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    initMenus();
    addStatusBar();

    m_drawingWidget = new DrawingWidget(this);
    m_drawingWidget->setFixedSize(800, 600);
    setCentralWidget(m_drawingWidget);
    retranslateUi();
    setFixedSize(sizeHint());
}

MainWindow::~MainWindow(void)
{
    // Intentionally empty
    // All components of 'this' are parented by 'this', they will be automatically deleted.
}

void MainWindow::initMenus(void)
{
    m_fileMenu = new QMenu(this);
    menuBar()->addMenu(m_fileMenu);

    m_quitAction = new QAction(this);
    m_quitAction->setMenuRole(QAction::QuitRole);
    connect(m_quitAction, SIGNAL(triggered()),
            this, SLOT(close()));
    m_fileMenu->addAction(m_quitAction);

    m_toolsMenu = new QMenu(this);
    m_addVertexAction = new QAction(this);
    m_moveVertexAction = new QAction(this);
    m_deleteVertexAction = new QAction(this);
    m_addLineAction = new QAction(this);
    m_deleteLineAction = new QAction(this);
    m_toolsMenu->addAction(m_addVertexAction);
    m_toolsMenu->addAction(m_moveVertexAction);
    m_toolsMenu->addAction(m_deleteVertexAction);
    m_toolsMenu->addAction(m_addLineAction);
    m_toolsMenu->addAction(m_deleteLineAction);
    connect(m_addVertexAction, SIGNAL(triggered()), this, SLOT(addVertexAction()));
    connect(m_moveVertexAction, SIGNAL(triggered()), this, SLOT(moveVertexAction()));
    connect(m_deleteVertexAction, SIGNAL(triggered()), this, SLOT(deleteVertexAction()));
    connect(m_addLineAction, SIGNAL(triggered()), this, SLOT(addLineAction()));
    connect(m_deleteLineAction, SIGNAL(triggered()), this, SLOT(deleteLineAction()));
    menuBar()->addMenu(m_toolsMenu);

    m_helpMenu = new QMenu(this);
    menuBar()->addMenu(m_helpMenu);

    m_whatsThisAction = QWhatsThis::createAction(this);
    m_helpMenu->addAction(m_whatsThisAction);

    m_aboutQtAction = new QAction(this);
    m_aboutQtAction->setMenuRole(QAction::AboutQtRole);
    m_helpMenu->addAction(m_aboutQtAction);
    connect(m_aboutQtAction, SIGNAL(triggered()),
            qApp, SLOT(aboutQt()));
}

void MainWindow::addStatusBar(void)
{
    m_statusBar = new QStatusBar(this);
    m_statusBar->setSizeGripEnabled(false);
    m_activeToolLabel = new QLabel(tr("N/A"), this);
    m_verticesCountLabel = new QLabel(tr("N/A"), this);
    m_linesCountLabel = new QLabel(tr("N/A"), this);
    m_statusBar->addWidget(m_activeToolLabel);
    m_statusBar->addWidget(m_verticesCountLabel);
    m_statusBar->addWidget(m_linesCountLabel);
    this->setStatusBar(m_statusBar);
}

void MainWindow::retranslateUi(void)
{
    setWindowTitle(tr("Drawing"));

    m_fileMenu->setTitle(tr("&File"));
        m_quitAction->setText(tr("&Quit"));
        m_quitAction->setStatusTip(tr("Quits this application"));
        m_quitAction->setToolTip(tr("Quits this application"));
        m_quitAction->setWhatsThis(tr("Activate this item to quit this application. You will"
                                      " be asked for confirmation."));

    m_helpMenu->setTitle(tr("&Help"));
        m_whatsThisAction->setText(tr("&Whats this?"));
        m_aboutQtAction->setText(tr("About &Qt"));

    m_toolsMenu->setTitle(tr("&Tools"));
    m_addVertexAction->setText(tr("&Add vertex"));
    m_moveVertexAction->setText(tr("&Move vertex"));
    m_deleteVertexAction->setText(tr("&Delete vertex"));
    m_addLineAction->setText(tr("&Add line"));
    m_deleteLineAction->setText(tr("&Delete line"));
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        retranslateUi();
        statusBar()->showMessage(tr("Language changed"));
    }
    QMainWindow::changeEvent(event);
}

void MainWindow::updateStatusBar(int verticesCount, int linesCount)
{
    QString verticesInfo = "Vertices: " + QString::number(verticesCount);
    QString linesInfo = "Lines: " + QString::number(linesCount);
    m_verticesCountLabel->setText(verticesInfo);
    m_linesCountLabel->setText(linesInfo);
}

void MainWindow::addVertexAction(void)
{
    bool allowed = m_drawingWidget->activeTool(0);

    if (allowed)
    {
        m_activeToolLabel->setText(tr("Adding vertices"));
    }
}

void MainWindow::moveVertexAction(void)
{
    bool allowed = m_drawingWidget->activeTool(1);

    if (allowed)
    {
        m_activeToolLabel->setText(tr("Moving vertices"));
    }
}

void MainWindow::deleteVertexAction(void)
{
    bool allowed = m_drawingWidget->activeTool(2);

    if (allowed)
    {
        m_activeToolLabel->setText(tr("Deleting vertices"));
    }
}

void MainWindow::addLineAction(void)
{
    bool allowed = m_drawingWidget->activeTool(3);

    if (allowed)
    {
        m_activeToolLabel->setText(tr("Adding lines"));
    }
}

void MainWindow::deleteLineAction(void)
{
    bool allowed = m_drawingWidget->activeTool(4);

    if (allowed)
    {
        m_activeToolLabel->setText(tr("Deleting lines"));
    }
}
