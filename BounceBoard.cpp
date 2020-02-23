#include "BounceBoard.h"
#include <QtWidgets/QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>
#include <QList>
#include "constants.h"

BounceBoard::BounceBoard(QGraphicsItem* p, qreal x, qreal y, qreal l, bool v):
	parent(p), len(l), isVertical(v)
{
	setPos(x, y);
	if (v) setData(GOD_Type, ODT_VBBoard);
	else setData(GOD_Type, ODT_HBBoard);
}

QRectF BounceBoard::boundingRect() const
{
	if (isVertical)
		return QRectF(-0.5, -len/2, 1, len);
	else
		return QRectF(-len/2, -0.5, len, 1);
}

void BounceBoard::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
	return;
}

bool BounceBoard::IsVertical() const
{
	return isVertical;
}

QPainterPath BounceBoard::shape() const
{
	QPainterPath p;
	p.addRect(boundingRect());
	return p;
}

QGraphicsItem* BounceBoard::getParent() const
{
	return parent;
}