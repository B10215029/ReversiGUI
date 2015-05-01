#include "reversiwindow.h"
#include <QFile>
#include <QString>
#include <iostream>
#include <vector>
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
}

void ReversiWindow::resizeGL(int w, int h){
	glViewport(0,0,w,h);
}

void ReversiWindow::paintGL(){
	glDrawArrays(GL_TRIANGLE_FAN,0,4);
	update();
}

void ReversiWindow::keyPressEvent(QKeyEvent *event){
	switch(event->key()){
	case Qt::Key_Escape:
		this->close();
		break;
	}
}

void ReversiWindow::mousePressEvent(QMouseEvent *event){

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
		printf("%s\n",vs_source);
	}
	else{
		printf("Impossible to open %s. Are you in the right directory ?"
			   "Don't forget to read the FAQ !\n", vertexFilePath);
		return 0;
	}

	// Read the Fragment Shader code from the file
	QFile FragmentShaderFile(fragmentFilePath);
	if(FragmentShaderFile.open(QIODevice::ReadOnly)){
		FragmentShaderCode=QString(FragmentShaderFile.readAll()).toStdString();
		FragmentShaderFile.close();
		fs_source = FragmentShaderCode.c_str();
		printf("%s\n",fs_source);
	}
	else{
		printf("Impossible to open %s. Are you in the right directory ?"
			"Don't forget to read the FAQ !\n", fragmentFilePath);
		return 0;
	}

	//compile vertex shader
	printf("Compiling shader : %s\n", vertexFilePath);
	glShaderSource(vs,1,&vs_source,NULL);
	glCompileShader(vs);
	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragmentFilePath);
	glShaderSource(fs, 1, &fs_source , NULL);
	glCompileShader(fs);

#ifdef _DEBUG
	GLint Result = GL_FALSE;
	int InfoLogLength;
	// Check Vertex Shader
	glGetShaderiv(vs, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(vs, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("in %s:\n%s\n", vertexFilePath, &VertexShaderErrorMessage[0]);
	}

	// Check Fragment Shader
	glGetShaderiv(fs, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(fs, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("in %s:\n%s\n", fragmentFilePath, &FragmentShaderErrorMessage[0]);
	}
#endif /* DEBUG */

	// Link the program
	printf("Linking program\n");
	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

#ifdef _DEBUG
	// Check the program
	glGetProgramiv(program, GL_LINK_STATUS, &Result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
#endif /* DEBUG */

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
