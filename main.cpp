#include "reversiwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ReversiWindow w;
	w.resize(800, 900);
	w.show();

	return a.exec();
}
