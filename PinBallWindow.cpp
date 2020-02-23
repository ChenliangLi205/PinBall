#include "PinBallWindow.h"
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QString>
#include "GameController.h"
#include "Board.h"
#include "Brick.h"
#include "PinBall.h"
#include "constants.h"

void PinBallWindow::initScene()
{
	scene->setSceneRect(-WindowWidth/2, -WindowHeight/2, WindowWidth, WindowHeight);
}

void PinBallWindow::initSceneBackground()
{
	view->setBackgroundBrush(QBrush(Qt::black));
}

PinBallWindow::PinBallWindow(QWidget *parent)
	: QWidget(parent), scene(new QGraphicsScene(this)), view(new QGraphicsView(scene, this)),
	gameController(new GameController(scene, this))
{
	resize(WindowWidth, WindowHeight);
	
	initScene();
	initSceneBackground();

	installEventFilter(this);
	setAttribute(Qt::WA_DeleteOnClose, true);
	//QTimer::singleShot(0, this, SLOT(adjustViewSize()));
	gameController->load(
		QFileDialog::getOpenFileName(this,
			"load map", ".", "map files(*.map)"));
}

void PinBallWindow::closeEvent(QCloseEvent* e)
{
	emit returnToMenu();
	e->accept();
}

bool PinBallWindow::eventFilter(QObject* watched, QEvent* event)
{
	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent* e = static_cast<QKeyEvent*>(event);
		gameController->handleKeyPress(e);
		return false;
	}
	if (event->type() == QEvent::KeyRelease)
	{
		QKeyEvent* e = static_cast<QKeyEvent*>(event);
		gameController->handleKeyRelease(e);
		return false;
	}
	return QWidget::eventFilter(watched, event);
}
