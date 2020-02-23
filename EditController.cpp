#include <QtWidgets/QMainWindow>
#include <qevent.h>
#include <qmessagebox.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>
#include <QList>
#include <qcolor.h>
#include <qfile.h>
#include <qtextstream.h>
#include "constants.h"
#include "EditController.h"
#include "EditWindow.h"
#include "Brick.h"
#include "PinBall.h"
#include "Board.h"
#include "BounceBoard.h"

EditController::EditController(QGraphicsScene* s, EditWindow* w):
	scene(s), window(w)
{
	selectedColor = Qt::yellow;
	selectedBrickHeight = BrickHeight;
	selectedBrickWidth = BrickWidth;
	addFixedParts();
}

inline void EditController::addFixedParts()
{
	scene->addItem(new PinBall(ballInitialX, ballInitialY, 0, 0, nullptr));
	scene->addItem(new Board(boardInitialX, boardInitialY, BoardWidth, BoardHeight, nullptr));
}

void EditController::initialize()
{
	for (Brick* b : bricks)
		scene->removeItem(b);
	bricks.clear();
	selectedColor = Qt::yellow;
	selectedBrickHeight = BrickHeight;
	selectedBrickWidth = BrickWidth;
}

void EditController::save(const QString& path) const
{
	if (path.isEmpty())
	{
		QMessageBox::warning(window, tr("Save"), tr("path cannot be empty !"));
		return;
	}
	QFile file(path);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QFile::Truncate))
	{
		QMessageBox::warning(window, tr("save"), tr("file %1 cannot open !").arg(path));
		return;
	}
	QTextStream outStream(&file);
	for (Brick* b : bricks)
	{
		outStream << b->x() << " " << b->y() << " "
			<< b->getWidth() << " " << b->getHeight() << " " <<
			b->getColor().red() << " " << b->getColor().green() << " " <<
			b->getColor().blue() << " " << b->getColor().alpha() << endl;
	}
	file.close();
	return;
}

void EditController::load(const QString& path)
{
	if (path.isEmpty())
	{
		QMessageBox::warning(window, tr("Load"), tr("path cannot be empty !"));
		return;
	}
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::warning(window, tr("Load"), tr("file %1 cannot open !").arg(path));
		return;
	}
	QTextStream inStream(&file);
	initialize();
	QString line;
	QStringList lineList;
	while (!inStream.atEnd())
	{
		line = inStream.readLine();
		lineList = line.split(" ");
		selectedBrickWidth = (qreal)lineList[2].toInt();
		selectedBrickHeight = (qreal)lineList[3].toInt();
		selectedColor = QColor(lineList[4].toInt(), lineList[5].toInt(), 
			lineList[6].toInt(), lineList[7].toInt());
		addBrick(QPointF( (qreal)lineList[0].toInt(), (qreal)lineList[1].toInt() ) );
	}
	file.close();
	return;
}

void EditController::addBrick(const QPointF& pos)
{
	Brick* newBrick = new Brick(pos.x(), pos.y(),
		selectedBrickWidth, selectedBrickHeight, selectedColor);
	// Check if the brick is out of boundary
	if (newBrick->x() - selectedBrickWidth / 2 <= -(scene->width() / 2) ||
		newBrick->x() + selectedBrickWidth / 2 >= scene->width() / 2 ||
		newBrick->y() - selectedBrickHeight / 2 <= -(scene->height() / 2) ||
		newBrick->y() + selectedBrickHeight / 2 >= scene->height() / 2)
	{
		delete newBrick;
		return;
	}
	scene->addItem(newBrick);
	QList<QGraphicsItem*> collidings = newBrick->collidingItems();
	if (!collidings.isEmpty()) scene->removeItem(newBrick);
	else bricks.append(newBrick);
	return;
}

void EditController::removeBrick(const QPointF& pos)
{
	Brick* toRemove = nullptr;
	for (Brick* b : bricks)
	{
		if (b->contains(pos))
		{
			toRemove = b;
			break;
		}
	}
	if (toRemove != nullptr)
	{
		bricks.removeOne(toRemove);
		scene->removeItem(toRemove);
	}
	return;
}

void EditController::setWidth(int i)
{
	selectedBrickWidth = (qreal)i;
}

void EditController::setHeight(int i)
{
	selectedBrickHeight = (qreal)i;
}

void EditController::setColor(QColor c)
{
	selectedColor = c;
}

QColor EditController::getColor() const
{
	return selectedColor;
}
