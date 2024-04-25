#include "glew.h"
#include "freeglut.h"
#include "game.h"
#include <ctime>
#include <stdlib.h>
#include <iostream>

int gridX, gridY;

//extern int YENILEME;
int yenile = 5;

int yilan_uzunluk = 5; //oyunun bas�nda y�lan�n uzunlugu 5 olacak
int posX[60] = {20,20,20,20,20};
int posY[60] = {20,19,18,17,16};

int yilanKonum = RIGHT;
extern bool oyunBitti;

bool yem = true;
int yemX, yemY;

extern int skor;

void initGrid(int x, int y) {  // oyun alan�n� izgaralara boluyoruz
	gridX = x;
	gridY = y;
}
void unit(int,int);
void timer_cagir1(int);
void cizGrid() {  //�zgaran�n c�z�m�
	for (int x = 0;x < gridX;x++) {           //�zgaradaki kareler izgar�n�n her sat�r ve sutununa cizildi
		for (int y = 0;y < gridY;y++) {
			unit(x, y);
		}
	}
}

void unit(int x,int y) {              // yemlerin ve y�lan�n hareket edecegi izgaran�n karelerinin olusumu
	if (x == 0 || y == 0 || x == gridX - 1 || y == gridY - 1) {
		glLineWidth(10.0);                 // oyun alan�n�n s�n�rlar�n� k�rm�z� yapt�k
		glColor3f(1.0, 0.0,0.0);
		//glClearColor(1.0, 0.0, 0.0,0.0);
	}
	else {
		glLineWidth(1.0);
		glColor4f(0.0, 1.0, 0.4,0.0);
	}
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x + 1, y);
	glVertex2f(x + 1, y + 1);
	glVertex2f(x, y + 1);

	glEnd();
}

void yemCiz() {
	if (yem)
		random(yemX, yemY);
	yem = false;
	glColor3f(1.0, 0.0, 0.0);
	glRectf(yemX, yemY, yemX + 1, yemY + 1);
}

void yilanCiz() {
	for (int i = yilan_uzunluk - 1;i > 0;i--) {
		posX[i] = posX[i - 1];
		posY[i] = posY[i - 1];
	}
	if (yilanKonum == UP)
		posY[0]++;
	else if (yilanKonum == DOWN)
		posY[0]--;
	else if (yilanKonum == RIGHT)
		posX[0]++;
	else if (yilanKonum == LEFT)
		posX[0]--;

	for (int j = 0; j < yilan_uzunluk; j++){
		if (j == 0)
			glColor4f(1.0, 1.0, 0.5,1.0);   //y�lan�n ba��n� sar� yapt�k
		else
			glColor3f(0.0, 0.0, 1.0);
		glRectd(posX[j], posY[j], posX[j] + 1, posY[j] + 1);
	}

	if (posX[0] == 0 || posX[0] == gridX - 1 || posY[0] == 0 || posY[0] == gridY - 1) { // oyun s�n�rlar�na gel�nce oyun bitti uyar�s� ver�lmes�n� saglar
		oyunBitti = true;
		if (oyunBitti) {
			//MessageBoxA(NULL,"Skorunuz:","OYUN B�TT�!", 0);
			std::cout << "*******************************\n";
			std::cout << "OYUN BITTI!!---------SKORUNUZ:" << skor;
			std::cout << "\n*******************************";
			//exit(0);
		}
	}
	if (posX[0] == yemX && posY[0] == yemY) {   // yem ile y�lan�n ba�� ayn� yere gel�nce yemin yenmesini saglar ve yem random olarak tekrardan olusur
		skor++;
		yilan_uzunluk++;     // yem yend�kce y�lan buyur
		yenile = yenile + 1;  //yem yedikce y�lan h�zln�r
		timer_cagir1(yenile);
		if (yilan_uzunluk == MAX)
			yilan_uzunluk = MAX;
		yem = true;
	}
}

void random(int& x, int& y) {    // yem lokasyonu �c�n random konum olusturma islemi
	int maxX = gridX - 2;
	int maxY = gridY - 2;
	int minX_ = 1;
	int minY_ = 1;
	srand(time(NULL));
	x = minX_ + rand() % (maxX - minX_);
	y = minY_ + rand() % (maxY - minY_);
}

void timer_cagir1(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / yenile, timer_cagir1, 0);      //g�runtu 1 saniyede 10 kez cagr�ld�
}
