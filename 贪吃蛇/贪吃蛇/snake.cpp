#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>

/*
	�γ����ݣ�̰����
	֪ʶ�㣺�ṹ�壬ѭ����������easyx������
*/

//������
//1.����һ�����ڣ�ͼ�δ���

//�ߵĽṹ
#define SNAKE_NUM 500	//�ߵ�������

enum DIR {//��ʾ�ߵķ���
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

struct Snake{
	int size;	//�ߵĽ���
	int dir;	//�ߵķ���
	int speed;	//�ƶ��ٶ�
	POINT coor[SNAKE_NUM];	//����
}snake;

//ʳ��ṹ
struct Food {
	int x;
	int y;
	int r;			//ʳ���С
	bool flag;		//ʳ���Ƿ񱻳���
	DWORD color;	//ʳ����ɫ
}food;


//���ݵĳ�ʼ��
void GameInit() {
	//init ��ʼ�� graph ͼ�δ���	SHOWCONSOLE��ʾ����̨
	initgraph(640, 480/*, SHOWCONSOLE*/);

	//�������������
	//GetTickCount();��ȡϵͳ�������������������ĺ�����
	srand(GetTickCount());

	//��ʼ���ߣ�һ��ʼ������
	snake.size = 3;
	snake.speed = 10;
	snake.dir = RIGHT;

	for (int i = 0; i < snake.size; i++) {
		snake.coor[i].x = 40 - 10 * i;
		snake.coor[i].y = 10;
	}

	//��ʼ��ʳ�� rand()�������һ�����������û�������������ӣ�ÿ�β����Ķ��ǹ̶�������
	//����������Ҫͷ�ļ�stdlib.h
	//һ���ʱ������Ϊ���ӣ���Ϊʱ���ǲ��ϱ仯��
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.r = rand() % 5 + 5;
	food.flag = true;
}


void GameDraw() {
	//˫�����ͼ
	BeginBatchDraw();

	//���ñ�����ɫ
	setbkcolor(RGB(28, 115, 119));
	cleardevice();//��ջ�ͼ�豸

	//������
	setfillcolor(RED);
	for (int i = 0; i < snake.size; i++) {
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}

	//����ʳ��
	if (food.flag) {
		solidcircle(food.x, food.y, food.r);
	}

	EndBatchDraw();//˫�������
}

//�ƶ���
void snakeMove() {
	for (int i = snake.size - 1; i > 0; i--) {
		snake.coor[i] = snake.coor[i - 1];
	}

	switch (snake.dir) {
	case UP:
		snake.coor[0].y -= snake.speed;
		if (snake.coor[0].y + 10 <= 0) { //����������ı߽�
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

//ͨ�����������ߵ��ƶ�����
void keyControl() {//��������

	//�ж���û�а���
	if (_kbhit()) {	//����а�������Ϊ�棬���򷵻�Ϊ��
		//72 80 75 77 �������Ҽ�ֵ
		switch (_getch()) {
		case 'W':
		case 'w':
		case 72://��
			if (snake.dir != DOWN) {
				snake.dir = UP;
			}
			break;
		case 'S':
		case 's':
		case 80://��
			if (snake.dir != UP) {
				snake.dir = DOWN;
			}
			break;
		case 'A':
		case 'a':
		case 75://��
			if (snake.dir != RIGHT) {
				snake.dir = LEFT;
			}
			break;
		case 'D':
		case 'd':
		case 77://��
			if (snake.dir != LEFT) {
				snake.dir = RIGHT;
			}
			break;
		case ' '://��Ϸ��ͣ�߼�
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

	//���ʳ����ʧ������������һ��ʳ��
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