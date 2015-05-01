#pragma once
class Reversi
{
public:
	Reversi(void);
	~Reversi(void);
	void display();
	void restart();
	bool check(int, int, int);
	bool setKeyDown(char);
	bool setKeyUp(char);
	bool setPiece(int, int);
	bool undo();
	bool redo();
	void AI();

private:
	int data[64][8][8];
	char rowKey;
	char colKey;
	int round;
	int step;
	int maxStep;
};
