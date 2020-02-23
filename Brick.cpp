#include "Brick.h"
#include <QtWidgets/QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>
#include <QList>
#include <qcolor.h>
#include "constants.h"
#include "BounceBoard.h"

Brick::Brick(qreal x, qreal y, qreal w, qreal h, QColor c):
	color(c), width(w), height(h)
{
	setPos(x, y);
	setData(GOD_Type, ODT_Brick);
}

QRectF Brick::boundingRect() const
{
	return QRectF(-width/2, -height/2, width, height);
}

void Brick::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
	painter->save();
	painter->fillRect(boundingRect(), color);
	painter->restore();
}

QPainterPath Brick::shape() const
{
	QPainterPath p;
	p.addRect(boundingRect());
	return p;
}

inline bool inRange(qreal x, qreal left, qreal right)
{
	return (left <= x && x <= right);
}

bool Brick::contains(const QPointF& p) const
{
	return inRange(p.x(), x() - width / 2, x() + width / 2) &&
		inRange(p.y(), y() - height / 2, y() + height / 2);
}

QColor Brick::getColor() const
{
	return color;
}

qreal Brick::getWidth() const
{
	return width;
}

qreal Brick::getHeight() const
{
	return height;
}