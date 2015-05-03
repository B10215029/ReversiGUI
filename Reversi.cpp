#define MIN(a,b) ((a) < (b) ? (a) : (b))
#include "Reversi.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

Reversi::Reversi(void){
	restart();
}


Reversi::~Reversi(void){

}

void Reversi::restart(){
	step=maxStep=0;
	round=1;
	rowKey = -1;
	colKey = -1;
	for(int i=0;i<64;++i)
		data[step][0][i] = 0;
	data[step][3][3] = 1;
	data[step][3][4] = 2;
	data[step][4][3] = 2;
	data[step][4][4] = 1;
}

void Reversi::display(){
	string msg =
		"┌─┬─┬─┬─┬─┬─┬─┬─┐┌─　\n"
		"│　│　│　│　│　│　│　│　││Ａ　\n"
		"├─┼─┼─┼─┼─┼─┼─┼─┤┌─　\n"
		"│　│　│　│　│　│　│　│　││Ｂ　\n"
		"├─┼─┼─┼─┼─┼─┼─┼─┤┌─　\n"
		"│　│　│　│　│　│　│　│　││Ｃ　\n"
		"├─┼─┼─┼─┼─┼─┼─┼─┤┌─　\n"
		"│　│　│　│　│　│　│　│　││Ｄ　\n"
		"├─┼─┼─┼─┼─┼─┼─┼─┤┌─　\n"
		"│　│　│　│　│　│　│　│　││Ｅ　\n"
		"├─┼─┼─┼─┼─┼─┼─┼─┤┌─　\n"
		"│　│　│　│　│　│　│　│　││Ｆ　\n"
		"├─┼─┼─┼─┼─┼─┼─┼─┤┌─　\n"
		"│　│　│　│　│　│　│　│　││Ｇ　\n"
		"├─┼─┼─┼─┼─┼─┼─┼─┤┌─　\n"
		"│　│　│　│　│　│　│　│　││Ｈ　\n"
		"└─┴─┴─┴─┴─┴─┴─┴─┘　　　\n"
		"┌─┌─┌─┌─┌─┌─┌─┌─　\n"
		"│１│２│３│４│５│６│７│８　\n"
		"　　　　　　　　　　　　　　　　　\n";
	//繪製棋子
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; j++){
			if (data[step][i][j] == 1)
				msg.replace(39 + i * 82 + 4 + j * 4, 2, "○");
			else if (data[step][i][j] == 2)
				msg.replace(39 + i * 82 + 4 + j * 4, 2, "●");
		}
	}
	//處理按鈕按下的效果
	if (rowKey != -1){
		msg.replace(34 + rowKey * 82, 2, "　");
		msg.replace(36 + rowKey * 82, 2, "　");
		msg.replace(75 + rowKey * 82, 2, "　");
		msg.replace(79 + rowKey * 82, 2, "│");
		msg.replace(118 + rowKey * 82, 2, "─");
		msg.replace(120 + rowKey * 82, 2, "┘");
	}
	if (colKey != -1){
		msg.replace(697+colKey*4, 2, "　");
		msg.replace(699+colKey*4, 2, "　");
		msg.replace(732+colKey*4, 2, "　");
		msg.replace(736+colKey*4, 2, "│");
		msg.replace(769+colKey*4, 2, "─");
		msg.replace(771+colKey*4, 2, "┘");
	}
	//計算黑棋與白棋的數量
	int b=0,w=0;
	for(int i=0;i<64;++i){
		if (data[step][0][i]==1)
			++b;
		if (data[step][0][i]==2)
			++w;
	}
	//輸出資訊
	char tmpstr[100];
	sprintf(tmpstr,"○:%2d\t●:%2d\tNOW->%s\nUndo:Backspace\tRedo:TAB\nRestart:Enter\nAI:SPACE", b, w, round==1?"○":"●");
	msg += tmpstr;

	//清除畫面
	system("cls");
	//printf速度較快比較不會閃爍
	printf("%s",msg.c_str());

}

bool Reversi::setKeyDown(char key){
	if (key >= 97 && key <= 104)
		rowKey = key - 97;
	else if (key >= 65 && key <= 72)
		rowKey = key - 65;
	else if (key >= 49 && key <= 56)
		colKey = key - 49;
	else 
		return false;
	if (rowKey!=-1&&colKey!=-1)
		setPiece(rowKey, colKey);
	return true;
}

bool Reversi::setKeyUp(char key){
	if (key >= 97 && key <= 104 && rowKey == key - 97)
		rowKey = -1;
	else if (key >= 65 && key <= 72 && rowKey == key - 65)
		rowKey = -1;
	else if (key >= 49 && key <= 56 && colKey == key - 49)
		colKey = -1;
	else
		return false;
	return true;
}

bool Reversi::setPiece(int x, int y){
	if (x >= 0 && x < 8 && y >= 0 && y < 8 && data[step][x][y] == 0){
		bool success=false;
		bool successIndex[8]={};
		//檢查是否可吃
		//左上
		if (data[step][x-1][y-1] == round % 2 + 1)
			for (int i=2;i<MIN(x,y);++i)
				if(data[step][x-i][y-i]==round)
					success = successIndex[0] = true;
				else if(data[step][x-i][y-i]==0)
					break;
		//上
		if (data[step][x-1][y] == round % 2 + 1)
			for (int i=2;i<=x;++i)
				if(data[step][x-i][y]==round)
					success = successIndex[1] = true;
				else if(data[step][x-i][y]==0)
					break;
		//右上
		if (data[step][x-1][y+1] == round % 2 + 1)
			for (int i=2;i<=MIN(x,7-y);++i)
				if(data[step][x-i][y+i]==round)
					success = successIndex[2] = true;
				else if(data[step][x-i][y+i]==0)
					break;
		//左
		if (data[step][x][y-1] == round % 2 + 1)
			for (int i=2;i<=y;++i)
				if(data[step][x][y-i]==round)
					success = successIndex[3] = true;
				else if(data[step][x][y-i]==0)
					break;
		//右
		if (data[step][x][y+1] == round % 2 + 1)
			for (int i=2;i<=7-y;++i)
				if(data[step][x][y+i]==round)
					success = successIndex[4] = true;
				else if(data[step][x][y+i]==0)
					break;
		//左下
		if (data[step][x+1][y-1] == round % 2 + 1)
			for (int i=2;i<=MIN(7-x,y);++i)
				if(data[step][x+i][y-i]==round)
					success = successIndex[5] = true;
				else if(data[step][x+i][y-i]==0)
					break;
		//下
		if (data[step][x+1][y] == round % 2 + 1)
			for (int i=2;i<=7-x;++i)
				if(data[step][x+i][y]==round)
					success = successIndex[6] = true;
				else if(data[step][x+i][y]==0)
					break;
		//右下
		if (data[step][x+1][y+1] == round % 2 + 1)
			for (int i=2;i<MIN(7-x,7-y);++i)
				if(data[step][x+i][y+i]==round)
					success = successIndex[7] = true;
				else if(data[step][x+i][y+i]==0)
					break;
		//放下棋子與吃棋子
		if(success){
			for(int i=0;i<64;++i)
				data[step+1][0][i]=data[step][0][i];
			maxStep=++step;
			data[step][x][y]=round;
			if(successIndex[0])
				for (int i=1;data[step][x-i][y-i]!=round;++i)
					data[step][x-i][y-i]=round;
			if(successIndex[1])
				for (int i=1;data[step][x-i][y]!=round;++i)
					data[step][x-i][y]=round;
			if(successIndex[2])
				for (int i=1;data[step][x-i][y+i]!=round;++i)
					data[step][x-i][y+i]=round;
			if(successIndex[3])
				for (int i=1;data[step][x][y-i]!=round;++i)
					data[step][x][y-i]=round;
			if(successIndex[4])
				for (int i=1;data[step][x][y+i]!=round;++i)
					data[step][x][y+i]=round;
			if(successIndex[5])
				for (int i=1;data[step][x+i][y-i]!=round;++i)
					data[step][x+i][y-i]=round;
			if(successIndex[6])
				for (int i=1;data[step][x+i][y]!=round;++i)
					data[step][x+i][y]=round;
			if(successIndex[7])
				for (int i=1;data[step][x+i][y+i]!=round;++i)
					data[step][x+i][y+i]=round;
			//換人
			round = round % 2 + 1;
			return true;
		}
	}
	return false;
}

bool Reversi::undo(){
	if(step>0){
		step--;
		round = round % 2 + 1;
		return true;
	}
	return false;
}

bool Reversi::redo(){
	if(step<maxStep){
		step++;
		round = round % 2 + 1;
		return true;
	}
	return false;
}

void Reversi::AI(){
	for(int i=0;!setPiece(i/8, i%8)&&i<64;++i);
}

int* Reversi::getData(){
	return data[step][0];
}
