#include "EditWindow.h"
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <QPainter>
#include <qlayout.h>
#include <qspinbox.h>
#include <qlabel.h>
#include "constants.h"
#include "Brick.h"

void EditWindow::initScene()
{
	scene->setSceneRect(-WindowWidth / 2, -WindowHeight / 2, WindowWidth, WindowHeight);
}

void EditWindow::initSceneBackground()
{
	view->setBackgroundBrush(QBrush(Qt::black));
}

EditWindow::EditWindow(QWidget* p):
	QWidget(p)
{
	scene = new QGraphicsScene(this);
	view = new QGraphicsView(this);
	view->setScene(scene);
	controller = new EditController(scene, this);

	resize(WindowWidth+100, WindowHeight+100);

	//the main layout of the window
	QVBoxLayout* mainLayout = new QVBoxLayout();
	mainLayout->setSpacing(5);
	this->setLayout(mainLayout);
	mainLayout->addWidget(view);
	//the layout for brick color and size area
	QHBoxLayout* brickAreaLayout = new QHBoxLayout();
	brickAreaLayout->setSpacing(2);
	//the layout for save load area
	QHBoxLayout* fileAreaLayout = new QHBoxLayout();
	fileAreaLayout->setSpacing(2);
	// brick color button
	brickColorButton = new QPushButton("Select Color");
	//set brick color button's color
	brickColorButton->setAutoFillBackground(true);
	QPalette buttonPalette = brickColorButton->palette();
	buttonPalette.setColor(QPalette::ButtonText, controller->getColor());
	brickColorButton->setPalette(buttonPalette);
	QObject::connect(brickColorButton, &QPushButton::clicked, this, &EditWindow::changeColor);
	// brick size spinbox
	QSpinBox* widthSpinBox = new QSpinBox(), * heightSpinBox = new QSpinBox();
	widthSpinBox->setRange(MinBrickWidth, MaxBrickWidth);
	heightSpinBox->setRange(MinBrickHeight, MaxBrickHeight);
	void (QSpinBox:: * valueChangedInt)(int) = &QSpinBox::valueChanged;
	// connect to controller
	QObject::connect(widthSpinBox, valueChangedInt, controller, &EditController::setWidth);
	QObject::connect(heightSpinBox, valueChangedInt, controller, &EditController::setHeight);
	widthSpinBox->setValue(BrickWidth);
	heightSpinBox->setValue(BrickHeight);
	//labels for spin boxes
	QLabel* widthLabel = new QLabel("W:"), * heightLabel = new QLabel("H:");
	//add to the screen
	brickAreaLayout->addWidget(widthLabel);
	brickAreaLayout->addWidget(widthSpinBox);
	brickAreaLayout->addWidget(heightLabel);
	brickAreaLayout->addWidget(heightSpinBox);
	brickAreaLayout->addWidget(brickColorButton);
	//load and save button
	QPushButton* loadButton = new QPushButton("Load"), * saveButton = new QPushButton("Save");
	QObject::connect(saveButton, &QPushButton::clicked, this, &EditWindow::saveEdit);
	QObject::connect(loadButton, &QPushButton::clicked, this, &EditWindow::loadEdit);
	//add to the screen
	fileAreaLayout->addWidget(loadButton);
	fileAreaLayout->addWidget(saveButton);
	// add to the main layout
	mainLayout->addLayout(brickAreaLayout);
	mainLayout->addLayout(fileAreaLayout);
	//initialize scene and view
	initScene();
	initSceneBackground();
	// listen to mouse events
	view->installEventFilter(this);
	// free memory when closed
	setAttribute(Qt::WA_DeleteOnClose, true);
}

bool EditWindow::eventFilter(QObject* obj, QEvent* evt)
{
	if (evt->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent* mouseEvt = static_cast<QMouseEvent*>(evt);
		QPointF clickPos = view->mapToScene( mouseEvt->pos() );
		if (mouseEvt->button() == Qt::LeftButton)
		{
			controller->addBrick(clickPos);
		}
		else controller->removeBrick(clickPos);
		return false;
	}
	return QWidget::eventFilter(obj, evt);
}

void EditWindow::changeColor()
{
	QColor color = QColorDialog::getColor(controller->getColor(), this, "Choose Color");
	controller->setColor(color);
	// set button's color
	QPalette buttonPalette = brickColorButton->palette();
	buttonPalette.setColor(QPalette::ButtonText, controller->getColor());
	brickColorButton->setPalette(buttonPalette);
	return;
}

void EditWindow::saveEdit()
{
	QString path = QFileDialog::getSaveFileName(this, "Save File", ".", "Map Files(*.map)");
	controller->save(path);
}

void EditWindow::loadEdit()
{
	QString path = QFileDialog::getOpenFileName(this, "Load File", ".", "Map Files(*.map)");
	controller->load(path);
}

void EditWindow::closeEvent(QCloseEvent* e)
{
	emit returnToMenu();
	e->accept();
}
