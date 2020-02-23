#pragma once
#include <QtWidgets/QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>
#include <qpushbutton.h>
#include "EditController.h"

class EditController;

class EditWindow : public QWidget
{
	Q_OBJECT
public:
	EditWindow(QWidget* parent=Q_NULLPTR);
private:
	QGraphicsScene* scene;
	QGraphicsView* view;
	EditController* controller;
	QPushButton* brickColorButton;
	void initScene();
	void initSceneBackground();
	bool eventFilter(QObject*, QEvent*) override;
	void changeColor();
	void saveEdit();
	void loadEdit();
	void closeEvent(QCloseEvent*) override;
	//private slots:
	//	void adjustViewSize();
signals:
	void returnToMenu();
};
