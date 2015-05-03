#include "reversiwindow.h"
#include <QFile>
#include <QString>
#include <QKeyEvent>
#include <QMouseEvent>

ReversiWindow::ReversiWindow(QWidget *parent) : QOpenGLWidget(parent)
{
	reversi = new Reversi;
}

ReversiWindow::~ReversiWindow()
{

}

void ReversiWindow::initializeGL(){
	initializeOpenGLFunctions();
	GLuint program = loadShaders(":/shaders/reversi.vert",":/shaders/reversi.frag");
	glUseProgram(program);
	resolutionUniform = glGetUniformLocation(program,"resolution");
	dataUinform = glGetUniformLocation(program,"data");
}

void ReversiWindow::resizeGL(int w, int h){
	width = w;
	height = h;
	glViewport(0,0,w,h);
}

void ReversiWindow::paintGL(){
	glUniform2f(resolutionUniform,width,height);
	glUniform1iv(dataUinform, 64, reversi->getData());
	glDrawArrays(GL_TRIANGLE_FAN,0,4);
	//update();
}

void ReversiWindow::keyPressEvent(QKeyEvent *event){
	switch(event->key()){
	case Qt::Key_Tab:
		reversi->redo();
		break;
	case Qt::Key_Backspace:
		reversi->undo();
		break;
	case Qt::Key_Return:
		reversi->restart();
		break;
	case Qt::Key_Space:
		reversi->AI();
		break;
	case Qt::Key_Escape:
		this->close();
		break;
	}
	update();
}

void ReversiWindow::mousePressEvent(QMouseEvent *event){
	reversi->setPiece((float)event->x()/width*8, (float)event->y()/height*8*1.125);
	update();
}

GLuint ReversiWindow::loadShaders(const char* vertexFilePath, const char* fragmentFilePath){
	GLuint program;
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

	std::string VertexShaderCode;
	std::string FragmentShaderCode;
	const char* vs_source;
	const char* fs_source;

	// Read the Vertex Shader code from the file
	QFile VertexShaderFile(vertexFilePath);
	if(VertexShaderFile.open(QIODevice::ReadOnly)){
		VertexShaderCode=QString(VertexShaderFile.readAll()).toStdString();
		VertexShaderFile.close();
		vs_source = VertexShaderCode.c_str();
	}
	else{
		return 0;
	}

	// Read the Fragment Shader code from the file
	QFile FragmentShaderFile(fragmentFilePath);
	if(FragmentShaderFile.open(QIODevice::ReadOnly)){
		FragmentShaderCode=QString(FragmentShaderFile.readAll()).toStdString();
		FragmentShaderFile.close();
		fs_source = FragmentShaderCode.c_str();
	}
	else{
		return 0;
	}

	// Compile vertex shader
	glShaderSource(vs,1,&vs_source,NULL);
	glCompileShader(vs);
	// Compile Fragment Shader
	glShaderSource(fs, 1, &fs_source , NULL);
	glCompileShader(fs);
	// Link the program
	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	// Delete shader
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
