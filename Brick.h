#pragma once
#include <QtWidgets/QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>
#include <QList>
#include <qcolor.h>
#include "BounceBoard.h"

class BounceBoard;

class Brick : public QGraphicsItem
{
public:
	Brick(qreal x, qreal y, qreal w, qreal h, QColor);
	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
	QPainterPath shape() const override;
	bool contains(const QPointF&) const override;
	QColor getColor() const;
	qreal getWidth() const;
	qreal getHeight() const;
private:
	QColor color;
	qreal width, height;
};
