#include <iostream>
#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<mmsystem.h>//windows提供的多媒体设备接口
#pragma comment(lib,"winmm.lib")//加载库文件，注意不要写分号
using namespace std;

/*==以下=======给出定义=========*/
#define WIN_WIDTH 1174
#define WIN_HIGHT 730
#define Ofishnum 0
DWORD t1, t2, t3 = 0, t4 = 0, deltat;

IMAGE backGround;//设定IMAGE类型
IMAGE textbk;
IMAGE player[4];//大小52
IMAGE player2[4];//90
IMAGE player3[4];//120
IMAGE player4[4];//200
IMAGE weed[2];
//其他鱼
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

int deadline = 3;//生态红线
int weedn=4;//草在seaweed中的位置
int fishn = 0;//鱼在fishes中的位置
bool direc[1000];//鱼的方向,真为向右
int Gamend=2;//最后结果  0 失败 1 胜利 2 还没结果
int weednum=4;//草的数量
int fishnum = 1;//鱼的数量
int stage=1;//玩家所处阶段
bool Cgame = true;//游戏是否继续
Playerfish Myfish = {WIN_WIDTH/2,WIN_HIGHT/2,0,true,52,false};//存放玩家位置数据
Weed seaweed[1000] = {1500,1500, false};
Otherfish fishes[1000] = {1500,1500,false,0};

/*==以下=======页面建立函数=========*/
//播放音乐
void BGM() {
	mciSendString("open ./musics/仙侠水下战斗.mp3 alias BGM", NULL, 0, NULL);//向多媒体设备接口发送字符串media device interface
	mciSendString("play BGM repeat", NULL, 0, NULL);//播放音乐
}


//加载初始环境
void Gameinit() {
	//移动函数时间参数
	t1 = t2  = GetTickCount();
	
	//其他鱼初始移动方向赋值
	bool b = true;
	//给其他鱼赋值大小
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
	//文字背景
	loadimage(&textbk,"./images/文字背景.png",150,768);
    //加载背景
	loadimage(&backGround,"./images/背景2.jpg");//把背景图片加载并保存
	//加载草
	loadimage(&weed[0], "./images/水草2白黑.png",40,60);
	loadimage(&weed[1], "./images/水草2黑彩.png",40,60);
	//加载玩家鱼
	loadimage(&player[0], "./images/player1.png",52,30);
	loadimage(&player[1], "./images/player2.png",52,30);
	loadimage(&player[2], "./images/player1向右.png",52,30);
	loadimage(&player[3], "./images/player2向右.png",52,30);
	loadimage(&player2[0], "./images/player1.png",121,70);
	loadimage(&player2[1], "./images/player2.png",121,70);
	loadimage(&player2[2], "./images/player1向右.png", 121, 70);
	loadimage(&player2[3], "./images/player2向右.png", 121, 70);
	loadimage(&player3[0], "./images/player1.png",207,120);
	loadimage(&player3[1], "./images/player2.png",207,120);
	loadimage(&player3[2], "./images/player1向右.png", 207, 120);
	loadimage(&player3[3], "./images/player2向右.png", 207, 120);
	loadimage(&player4[0], "./images/player1.png",346,200);
	loadimage(&player4[1], "./images/player2.png",346,200);
	loadimage(&player4[2], "./images/player1向右.png", 346, 200);
	loadimage(&player4[3], "./images/player2向右.png", 346, 200);
	//加载其他鱼  0 1为向左方向， 2 3为向右方向
	loadimage(&eyu[0], "./images/鳄鱼白黑.png", 100, 30);//大小：60
	loadimage(&eyu[1], "./images/鳄鱼黑彩.png", 100, 30);

	loadimage(&eyu[2], "./images/鳄鱼白黑向右.png", 100, 30);//大小：60
	loadimage(&eyu[3], "./images/鳄鱼黑彩向右.png", 100, 30);

	loadimage(&hetun[0], "./images/河豚白黑.png", 70, 70);//大小：70
	loadimage(&hetun[1], "./images/河豚黑彩.png", 70, 70);

	loadimage(&hetun[2], "./images/河豚白黑向右.png", 70, 70);//大小：70
	loadimage(&hetun[3], "./images/河豚黑彩向右.png", 70, 70);

	loadimage(&meirenyu[2], "./images/美人鱼白黑.png", 150, 100);//大小：100
	loadimage(&meirenyu[3], "./images/美人鱼黑彩.png", 150, 100);

	loadimage(&meirenyu[0], "./images/美人鱼白黑向左.png", 150, 100);//大小：100
	loadimage(&meirenyu[1], "./images/美人鱼黑彩向左.png", 150, 100);

	loadimage(&moguiyu[0], "./images/魔鬼鱼白黑.png", 150, 150);//大小：150
	loadimage(&moguiyu[1], "./images/魔鬼鱼黑彩.png", 150, 150);

	loadimage(&moguiyu[2], "./images/魔鬼鱼白黑向右.png", 150, 150);//大小：150
	loadimage(&moguiyu[3], "./images/魔鬼鱼黑彩向右.png", 150, 150);

	loadimage(&pipixia[0], "./images/皮皮虾白黑.png", 60, 50);//大小：60
	loadimage(&pipixia[1], "./images/皮皮虾黑彩.png", 60, 50);

	loadimage(&pipixia[2], "./images/皮皮虾白黑向右.png", 60, 50);//大小：60
	loadimage(&pipixia[3], "./images/皮皮虾黑彩向右.png", 60, 50);

	loadimage(&zhangyu[0], "./images/章鱼白黑.png", 200, 200);//大小：200
	loadimage(&zhangyu[1], "./images/章鱼黑彩.png", 200, 200);

	loadimage(&zhangyu[2], "./images/章鱼白黑向右.png", 200, 200);//大小：200
	loadimage(&zhangyu[3], "./images/章鱼黑彩向右.png", 200, 200);
	//加载草
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


/*==以下=======游戏规则函数=====*/

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



//显示内容
void Gamedraw() {
	//---------------------输出背景---------------------
	putimage(0, 0, &backGround);
	putimage(1024, 0, &textbk);
	//---------------------输出文字内容------------------
	setbkmode(TRANSPARENT);
	settextcolor(RGB(0, 0, 160));
	outtextxy(1030, 30, "水草数量：");
	outtextxy(1030, 70, "鱼的数量：");
	outtextxy(1030, 110, "玩家信息：");
	char shuicaonum[10], yudenum[10],chengshudu[10],shengtai[10],jiedaun[3];
	//输出整型水草数量
    sprintf_s(shuicaonum, "%d",weednum );
	outtextxy(1030, 50, shuicaonum);
	//输出整型鱼的数量
	sprintf_s(yudenum, "%d",fishnum);
	outtextxy(1030, 90, yudenum);
	//输出玩家信息
	outtextxy(1050, 130, "成熟度：");
	sprintf_s(chengshudu, "%d", Myfish.growth);
	outtextxy(1130, 130, chengshudu);
	outtextxy(1050, 150, "成长阶段：");
	sprintf_s(jiedaun, "%d", stage);
	outtextxy(1130, 150, jiedaun);
	//输出游戏提示
	settextcolor(RED);
	outtextxy(1030,10,"生态红线：");
	sprintf_s(shengtai, "%d", deadline);
	outtextxy(1130, 10, shengtai);
	outtextxy(1030, 200, "吃鱼提示：");
	outtextxy(1030, 220, "阶段1、2不能吃鱼");
	outtextxy(1030, 240, "阶段3可吃");
	outtextxy(1030, 260, "鳄鱼、河豚、美人鱼");
	outtextxy(1030, 280, "、皮皮虾");
	outtextxy(1030, 300, "阶段4可吃所有鱼");

	//--------------------输出玩家鱼图像-------------------------
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
	//----以下水草-------------------------------------
	for (int i = 0; i < 1000; i++) {
		if (seaweed[i].live) {
			putimage(seaweed[i].placex, seaweed[i].placey, &weed[0], SRCAND);
			putimage(seaweed[i].placex, seaweed[i].placey, &weed[1], SRCPAINT);
		}
	}
	//----以下其他鱼------------------------------------
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
	//------------------------------------------输出结果----------------
	if (Gamend==1) {
		settextcolor(GREEN);
		outtextxy(1030, 400, "游戏胜利");
	}
	else if(Gamend==0){
		settextcolor(RED);
		outtextxy(1030, 400, "游戏失败");
	}
}

void Creaplant() {
	seaweed[weedn].live = true;//“变活”一根草
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


/*==以下=======移动函数=========*/
void GameControl(int speed) {
	//使用windows函数获取键盘输入
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')) {
		//若检测字母按键，必须用大写，这样大小写都可以检测到，如果用小写，都检测不到
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
	//种草
	if (GetAsyncKeyState('1')&&((t2-t1)>200)) {
		Creaplant();
		t1 = t2;
	}
	//添加其他鱼
	if (GetAsyncKeyState('2')&&((t2-t1)>200)) {
		Creafish();
		t1 = t2;
	}
	//实现空格暂停和继续
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

	//其他鱼移动
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
//----------------------------------------------------------------------------------------------------------------未实现其他鱼吃草
void eat() {
	for (int i = 0; i < 1000; i++) {
		//玩家吃草
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
		//玩家吃鱼或被吃
		bool c = (Myfish.placex - fishes[i].placex) < fishes[i].large && (Myfish.placex - fishes[i].placex) > -Myfish.larege && (Myfish.placey - fishes[i].placey) > -Myfish.larege / 2 && (Myfish.placey - fishes[i].placey) < Myfish.larege / 2;
		if (c && Myfish.larege > fishes[i].large  &&  fishes[i].live  &&  Myfish.growth>6000) {
			fishes[i].live = false;
			Myfish.growth += 500;
			fishnum--;
		}
		else if (c && (Myfish.larege < fishes[i].large||Myfish.growth<6000)  &&  fishes[i].live) {
			Myfish.live = false;
		}
		//其他鱼吃草
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


/*==以下=======main函数=========*/
int main(){
	initgraph(WIN_WIDTH, WIN_HIGHT/*, SHOWCONSOLE*/);
	BGM();
	Gameinit();
	BeginBatchDraw();//开启双缓冲试图，先在内存里画好，再显示给你看
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
	EndBatchDraw();//结束
	return 0;
}