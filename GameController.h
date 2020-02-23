#pragma once

#include <QtWidgets/QMainWindow>
#include <qevent.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>
#include <QList>
#include <qcolor.h>
#include "PinBallWindow.h"
#include "Board.h"
#include "Brick.h"
#include "PinBall.h"
#include "BounceBoard.h"

class PinBallWindow;
class PinBall;
class Board;
class Brick;
enum BoardMoveDirection;

class GameController : public QObject
{
	Q_OBJECT
public:
	GameController(QGraphicsScene*, PinBallWindow*);
	void addFixedParts();
	void load(const QString& path);
	void pause();
	void resume();
	void addBrick(QPointF, qreal, qreal, QColor);
	void removeBrick(Brick*);
	void gameOver();
	int getTimeTick() const;
	void tick();
	qreal boardMoveDistance();
	void handleKeyPress(QKeyEvent*);
	void handleKeyRelease(QKeyEvent*);
	//bool event(QEvent* e) override;
	
private:
	QGraphicsScene* scene;
	PinBallWindow* window;
	bool paused;
	QTimer timer;
	PinBall* pinBall;
	Board* board;
	BounceBoard* leftWall, *rightWall, *topWall;
	QList<Brick*> bricks;
	int curTick;
	BoardMoveDirection boardDirection;
};
