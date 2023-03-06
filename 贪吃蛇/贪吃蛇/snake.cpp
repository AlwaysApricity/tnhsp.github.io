#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>

/*
	课程内容：贪吃蛇
	知识点：结构体，循环，函数，easyx，数组
*/

//做界面
//1.创建一个窗口，图形窗口

//蛇的结构
#define SNAKE_NUM 500	//蛇的最大节数

enum DIR {//表示蛇的方向
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

struct Snake{
	int size;	//蛇的节数
	int dir;	//蛇的方向
	int speed;	//移动速度
	POINT coor[SNAKE_NUM];	//坐标
}snake;

//食物结构
struct Food {
	int x;
	int y;
	int r;			//食物大小
	bool flag;		//食物是否被吃了
	DWORD color;	//食物颜色
}food;


//数据的初始化
void GameInit() {
	//init 初始化 graph 图形窗口	SHOWCONSOLE显示控制台
	initgraph(640, 480/*, SHOWCONSOLE*/);

	//设置随机数种子
	//GetTickCount();获取系统开机，到现在所经过的毫秒数
	srand(GetTickCount());

	//初始化蛇，一开始有三节
	snake.size = 3;
	snake.speed = 10;
	snake.dir = RIGHT;

	for (int i = 0; i < snake.size; i++) {
		snake.coor[i].x = 40 - 10 * i;
		snake.coor[i].y = 10;
	}

	//初始化食物 rand()随机产生一个整数，如果没有设计随机数种子，每次产生的都是固定的整数
	//设置种子需要头文件stdlib.h
	//一般把时间设置为种子，因为时间是不断变化的
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.r = rand() % 5 + 5;
	food.flag = true;
}


void GameDraw() {
	//双缓冲绘图
	BeginBatchDraw();

	//设置背景颜色
	setbkcolor(RGB(28, 115, 119));
	cleardevice();//清空绘图设备

	//绘制蛇
	setfillcolor(RED);
	for (int i = 0; i < snake.size; i++) {
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}

	//绘制食物
	if (food.flag) {
		solidcircle(food.x, food.y, food.r);
	}

	EndBatchDraw();//双缓冲结束
}

//移动蛇
void snakeMove() {
	for (int i = snake.size - 1; i > 0; i--) {
		snake.coor[i] = snake.coor[i - 1];
	}

	switch (snake.dir) {
	case UP:
		snake.coor[0].y -= snake.speed;
		if (snake.coor[0].y + 10 <= 0) { //超出了上面的边界
			snake.coor[0].y = 480;
		}
		break;
	case DOWN:
		snake.coor[0].y += snake.speed;
		if (snake.coor[0].y - 10 >= 480) {
			snake.coor[0].y = 0;
		}
		break;
	case LEFT:
		snake.coor[0].x -= snake.speed;
		if (snake.coor[0].x + 10 <= 0) {
			snake.coor[0].x = 640;
		}
		break;
	case RIGHT:
		snake.coor[0].x += snake.speed;
		if (snake.coor[0].x - 10 >= 640) {
			snake.coor[0].x = 0;
		}
		break;
	}
}

//通过按键开遍蛇的移动方向
void keyControl() {//阻塞函数

	//判断有没有按键
	if (_kbhit()) {	//如果有按键返回为真，否则返回为假
		//72 80 75 77 上下左右键值
		switch (_getch()) {
		case 'W':
		case 'w':
		case 72://上
			if (snake.dir != DOWN) {
				snake.dir = UP;
			}
			break;
		case 'S':
		case 's':
		case 80://下
			if (snake.dir != UP) {
				snake.dir = DOWN;
			}
			break;
		case 'A':
		case 'a':
		case 75://左
			if (snake.dir != RIGHT) {
				snake.dir = LEFT;
			}
			break;
		case 'D':
		case 'd':
		case 77://右
			if (snake.dir != LEFT) {
				snake.dir = RIGHT;
			}
			break;
		case ' '://游戏暂停逻辑
			while (1) {
				if (_getch() == ' ') {
					return;
				}
			}
		}
	}
}

void EatFood() {
	if (snake.coor[0].x >= (food.x - food.r) && 
		snake.coor[0].x <= (food.x + food.r) &&
		snake.coor[0].y >= (food.y - food.r) &&
		snake.coor[0].y <= (food.y + food.r) &&
		food.flag
		) {
		food.flag = false;
		snake.size++;
	}

	//如果食物消失，则重新生成一个食物
	if (!food.flag) {
		food.x = rand() % 640;
		food.y = rand() % 480;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.r = rand() % 5 + 5;
		food.flag = true;
	}
}


 
int main() {
	GameInit();
	
	while (1) {
		snakeMove();
		GameDraw();
		keyControl();
		EatFood();
		Sleep(130);
	}

	return 0;
}