#pragma once

#include <QtWidgets/QMainWindow>
#include <qevent.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>
#include <QList>
#include <qcolor.h>
#include "EditWindow.h"
#include "Brick.h"

class EditWindow;
class Brick;

class EditController : public QObject
{
	Q_OBJECT
public:
	EditController(QGraphicsScene*, EditWindow*);
	inline void addFixedParts();
	void initialize();
	void addBrick(const QPointF&);
	void removeBrick(const QPointF&);
	void save(const QString&) const;
	void load(const QString&);
	void setWidth(int);
	void setHeight(int);
	void setColor(QColor);
	QColor getColor() const;
private:
	QGraphicsScene* scene;
	EditWindow* window;
	QList<Brick*> bricks;
	QColor selectedColor;
	qreal selectedBrickWidth, selectedBrickHeight;
};
