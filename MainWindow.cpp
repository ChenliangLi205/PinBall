#include "MainWindow.h"
#include "EditWindow.h"
#include "PinBallWindow.h"
#include <qpushbutton.h>
#include <qlayout.h>

MainWindow::MainWindow(QWidget* parent) :
	QWidget(parent)
{
	resize(300, 400);
	setWindowTitle("Pin Ball");
	setWindowFlags(Qt::WindowCloseButtonHint);
	//Add layout
	QVBoxLayout* mainLayout = new QVBoxLayout();
	mainLayout->setSpacing(5);
	// add buttons
	QPushButton* startButton = new QPushButton("Start Game");
	QPushButton* editButton = new QPushButton("Edit Map");
	mainLayout->addWidget(startButton);
	mainLayout->addWidget(editButton);
	// connect buttons
	QObject::connect(editButton, &QPushButton::clicked, this, &MainWindow::openEditWindow);
	QObject::connect(startButton, &QPushButton::clicked, this, &MainWindow::openGameWindow);
	//Add layout to widget
	setLayout(mainLayout);
}

void MainWindow::openEditWindow()
{
	this->hide();
	EditWindow* w = new EditWindow();
	QObject::connect(w, &EditWindow::returnToMenu, this, &MainWindow::show);
	w->show();
}

void MainWindow::openGameWindow()
{
	this->hide();
	PinBallWindow* w = new PinBallWindow();
	QObject::connect(w, &PinBallWindow::returnToMenu, this, &MainWindow::show);
	w->show();
}
