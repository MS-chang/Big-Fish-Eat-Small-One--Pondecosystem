#include <iostream>
#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<mmsystem.h>//windows�ṩ�Ķ�ý���豸�ӿ�
#pragma comment(lib,"winmm.lib")//���ؿ��ļ���ע�ⲻҪд�ֺ�
using namespace std;

/*==����=======��������=========*/
#define WIN_WIDTH 1174
#define WIN_HIGHT 730
#define Ofishnum 0
DWORD t1, t2, t3 = 0, t4 = 0, deltat;

IMAGE backGround;//�趨IMAGE����
IMAGE textbk;
IMAGE player[4];//��С52
IMAGE player2[4];//90
IMAGE player3[4];//120
IMAGE player4[4];//200
IMAGE weed[2];
//������
IMAGE eyu[4];      IMAGE hetun[4];     IMAGE meirenyu[4];
IMAGE moguiyu[4];  IMAGE pipixia[4];   IMAGE zhangyu[4];

struct Playerfish {
	int placex;
	int placey;
	int growth;
	bool live;
	int larege;
	bool direc;
};
struct Otherfish {
	int placex;
	int placey;
	bool live;
	int large;
};
struct Weed {
	int placex;
	int placey;
	bool live;
};

int deadline = 3;//��̬����
int weedn=4;//����seaweed�е�λ��
int fishn = 0;//����fishes�е�λ��
bool direc[1000];//��ķ���,��Ϊ����
int Gamend=2;//�����  0 ʧ�� 1 ʤ�� 2 ��û���
int weednum=4;//�ݵ�����
int fishnum = 1;//�������
int stage=1;//��������׶�
bool Cgame = true;//��Ϸ�Ƿ����
Playerfish Myfish = {WIN_WIDTH/2,WIN_HIGHT/2,0,true,52,false};//������λ������
Weed seaweed[1000] = {1500,1500, false};
Otherfish fishes[1000] = {1500,1500,false,0};

/*==����=======ҳ�潨������=========*/
//��������
void BGM() {
	mciSendString("open ./musics/����ˮ��ս��.mp3 alias BGM", NULL, 0, NULL);//���ý���豸�ӿڷ����ַ���media device interface
	mciSendString("play BGM repeat", NULL, 0, NULL);//��������
}


//���س�ʼ����
void Gameinit() {
	//�ƶ�����ʱ�����
	t1 = t2  = GetTickCount();
	
	//�������ʼ�ƶ�����ֵ
	bool b = true;
	//�������㸳ֵ��С
	for (int i = 0; i < 1000; i++) {
		direc[i] = b;
		b = !b;
		switch (i % 6) {
		case 0:
			fishes[i].large = 50;
			break;
		case 1:
			fishes[i].large = 70;
			break;
		case 2:
			fishes[i].large = 100;
			break;
		case 3:
			fishes[i].large = 150;
			break;
		case 4:
			fishes[i].large = 60;
			break;
		case 5:
			fishes[i].large = 100;
			break;
		}
	}
	//���ֱ���
	loadimage(&textbk,"./images/���ֱ���.png",150,768);
    //���ر���
	loadimage(&backGround,"./images/����2.jpg");//�ѱ���ͼƬ���ز�����
	//���ز�
	loadimage(&weed[0], "./images/ˮ��2�׺�.png",40,60);
	loadimage(&weed[1], "./images/ˮ��2�ڲ�.png",40,60);
	//���������
	loadimage(&player[0], "./images/player1.png",52,30);
	loadimage(&player[1], "./images/player2.png",52,30);
	loadimage(&player[2], "./images/player1����.png",52,30);
	loadimage(&player[3], "./images/player2����.png",52,30);
	loadimage(&player2[0], "./images/player1.png",121,70);
	loadimage(&player2[1], "./images/player2.png",121,70);
	loadimage(&player2[2], "./images/player1����.png", 121, 70);
	loadimage(&player2[3], "./images/player2����.png", 121, 70);
	loadimage(&player3[0], "./images/player1.png",207,120);
	loadimage(&player3[1], "./images/player2.png",207,120);
	loadimage(&player3[2], "./images/player1����.png", 207, 120);
	loadimage(&player3[3], "./images/player2����.png", 207, 120);
	loadimage(&player4[0], "./images/player1.png",346,200);
	loadimage(&player4[1], "./images/player2.png",346,200);
	loadimage(&player4[2], "./images/player1����.png", 346, 200);
	loadimage(&player4[3], "./images/player2����.png", 346, 200);
	//����������  0 1Ϊ������ 2 3Ϊ���ҷ���
	loadimage(&eyu[0], "./images/����׺�.png", 100, 30);//��С��60
	loadimage(&eyu[1], "./images/����ڲ�.png", 100, 30);

	loadimage(&eyu[2], "./images/����׺�����.png", 100, 30);//��С��60
	loadimage(&eyu[3], "./images/����ڲ�����.png", 100, 30);

	loadimage(&hetun[0], "./images/����׺�.png", 70, 70);//��С��70
	loadimage(&hetun[1], "./images/����ڲ�.png", 70, 70);

	loadimage(&hetun[2], "./images/����׺�����.png", 70, 70);//��С��70
	loadimage(&hetun[3], "./images/����ڲ�����.png", 70, 70);

	loadimage(&meirenyu[2], "./images/������׺�.png", 150, 100);//��С��100
	loadimage(&meirenyu[3], "./images/������ڲ�.png", 150, 100);

	loadimage(&meirenyu[0], "./images/������׺�����.png", 150, 100);//��С��100
	loadimage(&meirenyu[1], "./images/������ڲ�����.png", 150, 100);

	loadimage(&moguiyu[0], "./images/ħ����׺�.png", 150, 150);//��С��150
	loadimage(&moguiyu[1], "./images/ħ����ڲ�.png", 150, 150);

	loadimage(&moguiyu[2], "./images/ħ����׺�����.png", 150, 150);//��С��150
	loadimage(&moguiyu[3], "./images/ħ����ڲ�����.png", 150, 150);

	loadimage(&pipixia[0], "./images/ƤƤϺ�׺�.png", 60, 50);//��С��60
	loadimage(&pipixia[1], "./images/ƤƤϺ�ڲ�.png", 60, 50);

	loadimage(&pipixia[2], "./images/ƤƤϺ�׺�����.png", 60, 50);//��С��60
	loadimage(&pipixia[3], "./images/ƤƤϺ�ڲ�����.png", 60, 50);

	loadimage(&zhangyu[0], "./images/����׺�.png", 200, 200);//��С��200
	loadimage(&zhangyu[1], "./images/����ڲ�.png", 200, 200);

	loadimage(&zhangyu[2], "./images/����׺�����.png", 200, 200);//��С��200
	loadimage(&zhangyu[3], "./images/����ڲ�����.png", 200, 200);
	//���ز�
	for (int i = 0; i < 4; i++) {
		seaweed[i].live = true;
	}
	seaweed[0].placex = 600;
	seaweed[0].placey = 500;
	seaweed[1].placex = 600;
	seaweed[1].placey = 550;
	seaweed[2].placex = 300;
	seaweed[2].placey = 400;
	seaweed[3].placex = 200;
	seaweed[3].placey = 500;

}


/*==����=======��Ϸ������=====*/

void countline() {
	if ((fishnum / weednum) > 5) {
		if (t3 == 0) {
			t3 = GetTickCount();
		}
		t4 = GetTickCount();
		deltat = t4 - t3;
		if (deltat > 15000) {
			deadline -= 1;
			t3 = 0;
			t4 = 0;
		}
	}
}

void GameRule() {
	if (Myfish.growth >= 10000) {
		Gamend = 1;
	}
	else if ((fishnum / weednum) > 25 || !Myfish.live || deadline == 0) {
		Gamend = 0;
	}
	
	if (Myfish.growth > 3000&&Myfish.growth<=6000) {
		stage = 2;
		Myfish.larege = 90;
	}
	else if (Myfish.growth > 6000 && Myfish.growth <= 7500) {
		stage = 3;
		Myfish.larege = 120;
	}
	else if (Myfish.growth > 7500 && Myfish.growth <= 9000) {
		stage = 4;
		Myfish.larege = 200;
	}
}



//��ʾ����
void Gamedraw() {
	//---------------------�������---------------------
	putimage(0, 0, &backGround);
	putimage(1024, 0, &textbk);
	//---------------------�����������------------------
	setbkmode(TRANSPARENT);
	settextcolor(RGB(0, 0, 160));
	outtextxy(1030, 30, "ˮ��������");
	outtextxy(1030, 70, "���������");
	outtextxy(1030, 110, "�����Ϣ��");
	char shuicaonum[10], yudenum[10],chengshudu[10],shengtai[10],jiedaun[3];
	//�������ˮ������
    sprintf_s(shuicaonum, "%d",weednum );
	outtextxy(1030, 50, shuicaonum);
	//��������������
	sprintf_s(yudenum, "%d",fishnum);
	outtextxy(1030, 90, yudenum);
	//��������Ϣ
	outtextxy(1050, 130, "����ȣ�");
	sprintf_s(chengshudu, "%d", Myfish.growth);
	outtextxy(1130, 130, chengshudu);
	outtextxy(1050, 150, "�ɳ��׶Σ�");
	sprintf_s(jiedaun, "%d", stage);
	outtextxy(1130, 150, jiedaun);
	//�����Ϸ��ʾ
	settextcolor(RED);
	outtextxy(1030,10,"��̬���ߣ�");
	sprintf_s(shengtai, "%d", deadline);
	outtextxy(1130, 10, shengtai);
	outtextxy(1030, 200, "������ʾ��");
	outtextxy(1030, 220, "�׶�1��2���ܳ���");
	outtextxy(1030, 240, "�׶�3�ɳ�");
	outtextxy(1030, 260, "���㡢���ࡢ������");
	outtextxy(1030, 280, "��ƤƤϺ");
	outtextxy(1030, 300, "�׶�4�ɳ�������");

	//--------------------��������ͼ��-------------------------
	if (Myfish.live) {
		switch (stage) {
		case 1:
			if(Myfish.direc){
				putimage(Myfish.placex, Myfish.placey, &player[3], SRCAND);
				putimage(Myfish.placex, Myfish.placey, &player[2], SRCPAINT);
			}
			else {
				putimage(Myfish.placex, Myfish.placey, &player[1], SRCAND);
				putimage(Myfish.placex, Myfish.placey, &player[0], SRCPAINT);
			}
			break;
		case 2:
			if(Myfish.direc){
				putimage(Myfish.placex, Myfish.placey, &player2[3], SRCAND);
				putimage(Myfish.placex, Myfish.placey, &player2[2], SRCPAINT);
			}
			else {
				putimage(Myfish.placex, Myfish.placey, &player2[1], SRCAND);
				putimage(Myfish.placex, Myfish.placey, &player2[0], SRCPAINT);
			}
			break;
		case 3:
			if(Myfish.direc){
				putimage(Myfish.placex, Myfish.placey, &player3[3], SRCAND);
				putimage(Myfish.placex, Myfish.placey, &player3[2], SRCPAINT);
			}
			else {
				putimage(Myfish.placex, Myfish.placey, &player3[1], SRCAND);
				putimage(Myfish.placex, Myfish.placey, &player3[0], SRCPAINT);
			}
			break;
		case 4:
			if (Myfish.direc) {
				putimage(Myfish.placex, Myfish.placey, &player4[3], SRCAND);
				putimage(Myfish.placex, Myfish.placey, &player4[2], SRCPAINT);
			}
			else {
				putimage(Myfish.placex, Myfish.placey, &player4[1], SRCAND);
				putimage(Myfish.placex, Myfish.placey, &player4[0], SRCPAINT);
			}
			break;
		}
	}
	//----����ˮ��-------------------------------------
	for (int i = 0; i < 1000; i++) {
		if (seaweed[i].live) {
			putimage(seaweed[i].placex, seaweed[i].placey, &weed[0], SRCAND);
			putimage(seaweed[i].placex, seaweed[i].placey, &weed[1], SRCPAINT);
		}
	}
	//----����������------------------------------------
	for (int i = 0; i < 1000; i++) {
		if (fishes[i].live) {
			switch (i%6) {
			case 0:
				if (direc[i]) {
					putimage(fishes[i].placex, fishes[i].placey, &eyu[2], SRCAND);
					putimage(fishes[i].placex, fishes[i].placey, &eyu[3], SRCPAINT);
				}
				else {
					putimage(fishes[i].placex, fishes[i].placey, &eyu[0], SRCAND);
					putimage(fishes[i].placex, fishes[i].placey, &eyu[1], SRCPAINT);
				}
				break;
			case 1:
				if(direc[i]){
					putimage(fishes[i].placex, fishes[i].placey, &hetun[2], SRCAND);
					putimage(fishes[i].placex, fishes[i].placey, &hetun[3], SRCPAINT);
				}
				else
				{
					putimage(fishes[i].placex, fishes[i].placey, &hetun[0], SRCAND);
					putimage(fishes[i].placex, fishes[i].placey, &hetun[1], SRCPAINT);
				}
				break;
			case 2:
				if(direc[i]){
					putimage(fishes[i].placex, fishes[i].placey, &meirenyu[2], SRCAND);
					putimage(fishes[i].placex, fishes[i].placey, &meirenyu[3], SRCPAINT);
				}
				else {
					putimage(fishes[i].placex, fishes[i].placey, &meirenyu[0], SRCAND);
					putimage(fishes[i].placex, fishes[i].placey, &meirenyu[1], SRCPAINT);
				}
				break;
			case 3:
				if(direc[i]){
					putimage(fishes[i].placex, fishes[i].placey, &moguiyu[2], SRCAND);
					putimage(fishes[i].placex, fishes[i].placey, &moguiyu[3], SRCPAINT);
				}
				else {
					putimage(fishes[i].placex, fishes[i].placey, &moguiyu[0], SRCAND);
					putimage(fishes[i].placex, fishes[i].placey, &moguiyu[1], SRCPAINT);
				}
				break;
			case 4:
				if (direc[i]) {
					putimage(fishes[i].placex, fishes[i].placey, &pipixia[2], SRCAND);
					putimage(fishes[i].placex, fishes[i].placey, &pipixia[3], SRCPAINT);
				}
				else {
					putimage(fishes[i].placex, fishes[i].placey, &pipixia[0], SRCAND);
					putimage(fishes[i].placex, fishes[i].placey, &pipixia[1], SRCPAINT);
				}
				break;
			case 5:
				if(direc[i]){
					putimage(fishes[i].placex, fishes[i].placey, &zhangyu[2], SRCAND);
					putimage(fishes[i].placex, fishes[i].placey, &zhangyu[3], SRCPAINT);
				}
				else {
					putimage(fishes[i].placex, fishes[i].placey, &zhangyu[0], SRCAND);
					putimage(fishes[i].placex, fishes[i].placey, &zhangyu[1], SRCPAINT);
				}
				break;
			}
		}
	}
	//------------------------------------------������----------------
	if (Gamend==1) {
		settextcolor(GREEN);
		outtextxy(1030, 400, "��Ϸʤ��");
	}
	else if(Gamend==0){
		settextcolor(RED);
		outtextxy(1030, 400, "��Ϸʧ��");
	}
}

void Creaplant() {
	seaweed[weedn].live = true;//����һ����
	seaweed[weedn].placex += 90 + (int)(900.0 * rand() / (RAND_MAX + 1.0));
	seaweed[weedn].placey += 301 + (int)(330.0* rand() / (RAND_MAX + 1.0));
	weedn++;
	weednum++;
}

void Creafish() {
	fishes[fishn].live = true;
	fishes[fishn].placex = 1 + (int)(824.0 * rand() / (RAND_MAX + 1.0));
	fishes[fishn].placey = 1 + (int)(400.0 * rand() / (RAND_MAX + 1.0));
	fishn++;
	fishnum++;
}


/*==����=======�ƶ�����=========*/
void GameControl(int speed) {
	//ʹ��windows������ȡ��������
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')) {
		//�������ĸ�����������ô�д��������Сд�����Լ�⵽�������Сд������ⲻ��
		if (Myfish.placey > 0)
			Myfish.placey -= speed;
	}
	if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) {
		if (Myfish.placey < WIN_HIGHT - 30)
			Myfish.placey += speed;
	}
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) {
		if (Myfish.placex > -30)
			Myfish.placex -= speed;
		Myfish.direc = false;
	}
	if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')) {
		if (Myfish.placex < WIN_WIDTH - 190)
			Myfish.placex += speed;
		Myfish.direc = true;
	}
	//�ֲ�
	if (GetAsyncKeyState('1')&&((t2-t1)>200)) {
		Creaplant();
		t1 = t2;
	}
	//���������
	if (GetAsyncKeyState('2')&&((t2-t1)>200)) {
		Creafish();
		t1 = t2;
	}
	//ʵ�ֿո���ͣ�ͼ���
	if (GetAsyncKeyState(VK_SPACE) && ((t2 - t1) > 200)) {
		while (1) {
			Sleep(1000);
			if (GetAsyncKeyState(VK_SPACE)) {
				break;
			}
		}
		t1 = t2;
	}
	t2 = GetTickCount();

	//�������ƶ�
	for (int i = 0; i < 1000; i++) {
		if (direc[i]) {
			fishes[i].placex += speed - 1;
		}
		else {
			fishes[i].placex -= speed - 1;
		}

		if (!(fishes[i].placex >= 0 && fishes[i].placex <= 824)) {
			direc[i] = !direc[i];
	   }
	}
}
//----------------------------------------------------------------------------------------------------------------δʵ��������Բ�
void eat() {
	for (int i = 0; i < 1000; i++) {
		//��ҳԲ�
		bool b = (Myfish.placex - seaweed[i].placex) < 40 - Myfish.larege / 2 && (Myfish.placex - seaweed[i].placex) > -Myfish.larege / 2 && (Myfish.placey - seaweed[i].placey) < Myfish.larege / 2 && (Myfish.placey - seaweed[i].placey) > -Myfish.larege / 2;
		if (b&&Myfish.growth<=6000&&seaweed[i].live) {
			seaweed[i].live = false;
			Myfish.growth += 200;
			weednum--;
		}
		else if (b && Myfish.growth > 6000&& seaweed[i].live) {
			seaweed[i].live = false;
			Myfish.growth += 50;
			weednum--;
		}
		//��ҳ���򱻳�
		bool c = (Myfish.placex - fishes[i].placex) < fishes[i].large && (Myfish.placex - fishes[i].placex) > -Myfish.larege && (Myfish.placey - fishes[i].placey) > -Myfish.larege / 2 && (Myfish.placey - fishes[i].placey) < Myfish.larege / 2;
		if (c && Myfish.larege > fishes[i].large  &&  fishes[i].live  &&  Myfish.growth>6000) {
			fishes[i].live = false;
			Myfish.growth += 500;
			fishnum--;
		}
		else if (c && (Myfish.larege < fishes[i].large||Myfish.growth<6000)  &&  fishes[i].live) {
			Myfish.live = false;
		}
		//������Բ�
		if (fishes[i].live) {
			for (int j = 0; j < 1000; j++) {
				bool n = (fishes[i].placex - seaweed[j].placex) < 40 && (fishes[i].placex - seaweed[j].placex) > -fishes[i].large && (fishes[i].placey - seaweed[j].placey) < fishes[i].large / 2 && (fishes[i].placey - seaweed[j].placey) > -fishes[i].large / 2;
				if (seaweed[i].live&&n) {
					seaweed[j].live = false;
				}
			}
		}

	}
}


/*==����=======main����=========*/
int main(){
	initgraph(WIN_WIDTH, WIN_HIGHT/*, SHOWCONSOLE*/);
	BGM();
	Gameinit();
	BeginBatchDraw();//����˫������ͼ�������ڴ��ﻭ�ã�����ʾ���㿴
	while (1) {
		GameRule();
		Gamedraw();
		FlushBatchDraw();
		GameControl(2);
		eat();
		countline();
		if (Gamend == 0 || Gamend == 1)
			break;
	}
	while (1) {
		Gamedraw();
	}
	EndBatchDraw();//����
	return 0;
}