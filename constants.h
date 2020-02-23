#pragma once
#include <QtWidgets>
#include <qcolor.h>

const qreal BallRadius = 6;
const qreal WindowWidth = 1100;
const qreal WindowHeight = 700;
const qreal BoardWidth = 200;
const qreal BoardHeight = 15;
const qreal BrickWidth = 48;
const qreal BrickHeight = 23;
const qreal MaxBrickWidth = 100;
const qreal MinBrickWidth = 10;
const qreal MaxBrickHeight = 50;
const qreal MinBrickHeight = 10;
const qreal wallThick = 5;
const qreal BoardSpeed = 2;
const qreal hBallSpeedInitial = -2;
const qreal vBallSpeedInitial = -1;
const qreal ballInitialX = 0;
const qreal boardInitialX = 0;
const qreal ballInitialY = WindowHeight/2 - 30;
const qreal boardInitialY = WindowHeight/2 - 15;
const int maxTick = 4;
const qreal BrickRift = 2;
const QColor BrickColor = Qt::yellow;

enum GameObjectData {
	GOD_Type
};

enum ObjectDataTypes {
	ODT_Board,
	ODT_Pinball,
	ODT_Brick,
	ODT_VBBoard,
	ODT_HBBoard
};

enum BoardMoveDirection {
	NoMove,
	LeftMove,
	RightMove,
};
