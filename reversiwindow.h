#ifndef REVERSIWINDOW_H
#define REVERSIWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Core>
#include "Reversi.h"

class ReversiWindow : public QOpenGLWidget, protected QOpenGLFunctions_4_3_Core
{
	Q_OBJECT

public:
	ReversiWindow(QWidget *parent = 0);
	~ReversiWindow();
protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
	void keyPressEvent(QKeyEvent *event);
	void mousePressEvent(QMouseEvent *event);
	GLuint loadShaders(const char* vertexFilePath, const char* fragmentFilePath);
	Reversi *reversi;
};

#endif // REVERSIWINDOW_H
