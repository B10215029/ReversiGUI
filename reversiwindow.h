#ifndef REVERSIWINDOW_H
#define REVERSIWINDOW_H

#include <QWidget>

class ReversiWindow : public QWidget
{
	Q_OBJECT

public:
	ReversiWindow(QWidget *parent = 0);
	~ReversiWindow();
};

#endif // REVERSIWINDOW_H
