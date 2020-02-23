#pragma once

#include <QtWidgets/QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>
#include <QList>
#include "PinBall.h"
#include "Board.h"
#include "Brick.h"
#include "GameController.h"

class PinBallWindow : public QWidget
{
	Q_OBJECT
public:
	PinBallWindow(QWidget *parent = Q_NULLPTR);
private:
	QGraphicsScene* scene;
	QGraphicsView* view;
	GameController* gameController;
	void initScene();
	void initSceneBackground();
	bool eventFilter(QObject*, QEvent*) override;
	void closeEvent(QCloseEvent*) override;
signals:
	void returnToMenu();
//private slots:
//	void adjustViewSize();
};

