#pragma once
#include <QtWidgets/QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>
#include <QList>

class BounceBoard : public QGraphicsItem
{
public:
	BounceBoard(QGraphicsItem* p, qreal x, qreal y, qreal l, bool v);
	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
	QPainterPath shape() const override;
	bool IsVertical() const;
	QGraphicsItem* getParent() const;
private:
	QGraphicsItem* parent;
	qreal len;
	bool isVertical;
};
