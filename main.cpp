#include "PinBallWindow.h"
#include "EditWindow.h"
#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <qdebug.h>
#include <qmath.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
