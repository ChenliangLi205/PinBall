#pragma once
#include <QtWidgets/QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>
#include <QList>
#include "BounceBoard.h"
#include "GameController.h"

class BounceBoard;
class GameController;

class Board : public QGraphicsItem
{
public:
	Board(qreal x, qreal y, qreal w, qreal h, GameController* g);
	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
	QPainterPath shape() const override;
	void advance(int phase) override;
	qreal getSpeed() const;
	void setSpeed(qreal);
	bool contains(const QPointF&) const override;
private:
	qreal width, height;
	qreal curX, lastX, speed;
	GameController* gameController;
};
