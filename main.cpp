#include "reversiwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ReversiWindow w;
	w.show();

	return a.exec();
}
