#pragma once
#include <QtWidgets/QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>
#include <QList>
#include "GameController.h"
#include "Board.h"
#include "constants.h"
#include "Brick.h"

class GameController;
class Board;
class Brick;

class PinBall : public QGraphicsItem
{
public:
	PinBall(qreal x, qreal y, int hs, int vs, GameController* g);
	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
	QPainterPath shape() const override;
	void advance(int phase) override;
	void handleCollisions();
	bool checkOut();
	void bounce(Board* b);
	void bounce(const QList<Brick*>& b);
	bool contains(const QPointF& point) const override;
private:
	GameController* gameController;
	qreal vSpeed, hSpeed;
};