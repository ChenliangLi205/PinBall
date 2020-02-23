#include "PinBall.h"
#include <QtWidgets/QMainWindow>
#include <qmath.h>
#include <qdebug.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>
#include <QList>
#include "GameController.h"
#include "Board.h"
#include "Brick.h"
#include "constants.h"
#include "BounceBoard.h"


PinBall::PinBall(qreal x, qreal y, int hs, int vs, GameController* g) :
	gameController(g), hSpeed(hs), vSpeed(vs)
{
	setPos(x, y);
	setData(GOD_Type, ODT_Pinball);
}

QRectF PinBall::boundingRect() const
{
	return QRectF(-BallRadius, -BallRadius, 2*BallRadius, 2*BallRadius);
}

void PinBall::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
	painter->save();
	painter->setRenderHint(QPainter::Antialiasing);
	painter->fillPath(shape(), Qt::gray);
	painter->restore();
}

QPainterPath PinBall::shape() const
{
	QPainterPath p;
	p.addEllipse(QPointF(0, 0), BallRadius, BallRadius);
	return p;
}

void PinBall::advance(int phase)
{
	if (phase == 0) return;
	if (!checkOut())
	{
		handleCollisions();
		if(gameController->getTimeTick() == 0)
			moveBy(hSpeed, vSpeed);
	}
	else
	{
		gameController->gameOver();
	}
}

void PinBall::handleCollisions()
{
	QList<QGraphicsItem*> collidingList = collidingItems();
	QList<Brick*> collidingBricks;
	for (QGraphicsItem* c : collidingList)
	{
		if (c->data(GOD_Type) == ODT_VBBoard)
		{
			hSpeed = -hSpeed;
		}
		if (c->data(GOD_Type) == ODT_HBBoard)
		{
			vSpeed = -vSpeed;
		}
		if (c->data(GOD_Type) == ODT_Brick)
		{
			Brick* b = static_cast<Brick*>(c);
			collidingBricks.append(b);
		}
		if (c->data(GOD_Type) == ODT_Board)
		{
			Board* b = static_cast<Board*>(c);
			bounce(b);
		}
	}
	if (collidingBricks.size() > 0)
	{
		bounce(collidingBricks);
		for (Brick* b : collidingBricks)
			gameController->removeBrick(b);
	}
}

bool PinBall::checkOut()
{
	return y() + 2 * BallRadius >= WindowHeight / 2;
}

inline qreal distance(const QPointF& p1,const QPointF& p2)
{
	return qSqrt(qPow(p1.x() - p2.x(), 2) + qPow(p1.y() - p2.y(), 2));
}

bool PinBall::contains(const QPointF& p) const
{
	return distance(QPointF(x(), y()), p) <= BallRadius;
}

void PinBall::bounce(const QList<Brick*>& collidingBricks)
{
	QPointF p12(x(), y() - BallRadius), p3(x() + BallRadius, y()),
		p6(x(), y() + BallRadius), p9(x()-BallRadius, y());
	bool vReverse = false, hReverse=false;
	for (Brick* b : collidingBricks)
	{
		//check if the brick contains four points of the ball
		// the 12-oclock or 6-oclock point would reverse the ball's vertical speed
		if (b->contains(p12) || b->contains(p6))
		{
			vReverse = true;
			continue;
		}
		// the 3-oclock or 9-oclock point would reverse the ball's horizontal speed
		if (b->contains(p3) || b->contains(p9))
		{
			hReverse = true;
			continue;
		}
		// if the ball bumps into brick's corner reverse both speeds
		QPointF leftTop(b->x() - BrickWidth / 2, b->y() - BrickHeight / 2),
			rightTop(b->x() + BrickWidth / 2, b->y() - BrickHeight / 2),
			leftBottom(b->x() - BrickWidth / 2, b->y() + BrickHeight / 2), 
			rightBottom(b->x() + BrickWidth / 2, b->y() + BrickHeight / 2);
		if (this->contains(leftTop) || this->contains(rightTop)
			|| this->contains(leftBottom) || this->contains(rightBottom))
		{
			vReverse = true;
			hReverse = true;
		}
	}
	if (vReverse) vSpeed = -vSpeed;
	if (hReverse) hSpeed = -hSpeed;
	return;
}

void PinBall::bounce(Board* b)
{
	QPointF p12(x(), y() - BallRadius), p3(x() + BallRadius, y()),
		p6(x(), y() + BallRadius), p9(x() - BallRadius, y());
	bool vReverse = false, hReverse = false;
	QPointF leftTop(b->x() - BoardWidth / 2, b->y() - BoardHeight / 2),
		rightTop(b->x() + BoardWidth / 2, b->y() - BoardHeight / 2),
		leftBottom(b->x() - BoardWidth / 2, b->y() + BoardHeight / 2),
		rightBottom(b->x() + BoardWidth / 2, b->y() + BoardHeight / 2);
	if (this->contains(leftTop) || this->contains(rightTop)
		|| this->contains(leftBottom) || this->contains(rightBottom))
	{
		vReverse = true;
		hReverse = true;
	}
	if (b->contains(p12) || b->contains(p6)) vReverse = true;
	if (b->contains(p3) || b->contains(p9)) hReverse = true;
	if (vReverse) vSpeed = -vSpeed;
	if (b->getSpeed() != 0) hSpeed = b->getSpeed();
	else if (hReverse) hSpeed = -hSpeed;
	return;
}