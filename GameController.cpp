#include <QtWidgets/QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>
#include <QList>
#include "GameController.h"
#include "Board.h"
#include "Brick.h"
#include "PinBall.h"
#include "constants.h"
#include "BounceBoard.h"

void GameController::addFixedParts()
{
	pinBall = new PinBall(ballInitialX, ballInitialY, hBallSpeedInitial, vBallSpeedInitial, this);
	board = new Board(boardInitialX, boardInitialY, BoardWidth, BoardHeight, this);
	leftWall = new BounceBoard(Q_NULLPTR, -WindowWidth / 2 + 1, 0, WindowHeight, true);
	rightWall = new BounceBoard(Q_NULLPTR, WindowWidth / 2 - 1, 0, WindowHeight, true);
	topWall = new BounceBoard(Q_NULLPTR, 0, -WindowHeight / 2 + 1, WindowWidth, false);

	scene->addItem(pinBall);
	scene->addItem(board);
	scene->addItem(leftWall);
	scene->addItem(rightWall);
	scene->addItem(topWall);
}

GameController::GameController(QGraphicsScene* scene, PinBallWindow* parent) :
	window(parent), scene(scene), curTick(1), boardDirection(NoMove), paused(true)
{
	timer.start(2);

	addFixedParts();
	
	//scene->installEventFilter(this);
	resume();
	pause();
	// load map
}

void GameController::load( const QString& path )
{
	if (path.isEmpty())
	{
		QMessageBox::warning(window, tr("Load"), tr("path cannot be empty !"));
		return;
	}
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::warning(window, tr("Load"), tr("file %1 cannot open !").arg(path));
		return;
	}
	QTextStream inStream(&file);
	QString line;
	QStringList lineList;
	while (!inStream.atEnd())
	{
		line = inStream.readLine();
		lineList = line.split(" ");
		qreal selectedBrickWidth = (qreal)lineList[2].toInt();
		qreal selectedBrickHeight = (qreal)lineList[3].toInt();
		QColor selectedColor = QColor(lineList[4].toInt(), lineList[5].toInt(),
			lineList[6].toInt(), lineList[7].toInt());
		addBrick(QPointF((qreal)lineList[0].toInt(), (qreal)lineList[1].toInt()),
					  selectedBrickWidth, selectedBrickHeight, selectedColor);
	}
	for (Brick* b : bricks)
		scene->addItem(b);
	file.close();
	resume();
	return;
}

void GameController::resume()
{
	connect(&timer, &QTimer::timeout, this->scene, &QGraphicsScene::advance);
	connect(&timer, &QTimer::timeout, this, &GameController::tick);
	paused = false;
}

void GameController::pause()
{
	disconnect(&timer, &QTimer::timeout, this->scene, &QGraphicsScene::advance);
	disconnect(&timer, &QTimer::timeout, this, &GameController::tick);
	paused = true;
}

void GameController::addBrick(QPointF pos, qreal w, qreal h, QColor c)
{
	bricks.append(new Brick(pos.x(), pos.y(), w, h, c));
	return;
}

void GameController::removeBrick(Brick* b)
{
	bricks.removeOne(b);
	scene->removeItem(b);
	return;
}

void GameController::tick()
{
	++curTick;
	curTick %= maxTick;
}

int GameController::getTimeTick() const
{
	return curTick;
}

void GameController::gameOver()
{
	return;
}

qreal GameController::boardMoveDistance()
{
	if (boardDirection == NoMove) return 0;
	if (boardDirection == LeftMove) return -BoardSpeed;
	else return BoardSpeed;
}

void GameController::handleKeyPress(QKeyEvent* e)
{
	if (e->key() == Qt::Key_P)
	{
		if (!paused) pause();
		else resume();
	}
	if ( (e->key() == Qt::Key_Left || e->key() == Qt::Key_A) && !paused)
		board->setSpeed(-BoardSpeed);
	if ( (e->key() == Qt::Key_Right || e->key() == Qt::Key_D) && !paused)
		board->setSpeed(BoardSpeed);
}

void GameController::handleKeyRelease(QKeyEvent* e)
{
	if ( (e->key() == Qt::Key_Left || e->key() == Qt::Key_A ||
		e->key() == Qt::Key_Right || e->key() == Qt::Key_D)
		&& !paused)
		board->setSpeed(0);
}