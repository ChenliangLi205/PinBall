#include "Board.h"
#include <QtWidgets/QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>
#include <QList>
#include "GameController.h"
#include "constants.h"
#include "BounceBoard.h"

Board::Board(qreal x, qreal y, qreal w, qreal h, GameController* g):
	width(w), height(h), gameController(g), curX(x), lastX(x), speed(0)
{
	setPos(x, y);
	setData(GOD_Type, ODT_Board);
}

QRectF Board::boundingRect() const
{
	return QRectF(-width/2,-height/2, width, height);
}

void Board::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
	painter->save();
	painter->setRenderHint(QPainter::Antialiasing);
	painter->fillRect(boundingRect(), Qt::gray);
	painter->restore();
}

QPainterPath Board::shape() const
{
	QPainterPath p;
	p.addRect(boundingRect());
	return p;
}

void Board::advance(int phase)
{
	if (phase == 0) return;
	if (x() + speed < -WindowWidth / 2 + BoardWidth / 2)
		setX(-WindowWidth / 2 + BoardWidth / 2);
	else if (x() + speed > WindowWidth / 2 - BoardWidth / 2)
		setX(WindowWidth / 2 - BoardWidth / 2);
	else moveBy(speed, 0);
}

inline bool inRange(qreal x, qreal left, qreal right)
{
	return (left <= x && x <= right);
}

bool Board::contains(const QPointF& p) const
{
	return inRange(p.x(), x() - BoardWidth / 2, x() + BoardWidth / 2) &&
		inRange(p.y(), y() - BoardHeight / 2, y() + BoardHeight / 2);
}

void Board::setSpeed(qreal v)
{
	speed = v;
}

qreal Board::getSpeed() const
{
	return speed;
}