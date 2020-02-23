#pragma once
#include <qwidget.h>

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent=Q_NULLPTR);
	void openEditWindow();
	void openGameWindow();
};
