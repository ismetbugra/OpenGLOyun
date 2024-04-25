#include "glew.h"
#include "freeglut.h"
#include "game.h"
#include <iostream>
#include <stdlib.h>

#define SATIR 40
#define SUTUN 40
//#define YENILEME 10

int YENILEME= 5;
extern int yilanKonum;
bool oyunBitti = false;
int skor = 0;

void oyun_cagir(int,char**);
void timer_cagir(int);
void display_cagir();
void reshape_cagir(int,int);
void keyboard_cagir(int, int, int);
void cokboyutlu_cagir(int, char**);
void kupHareket();
void mouse(int, int, int, int);
void kupReshape(int,int);
void kupDisplay();
void kupRengi();
void polygon(int,int,int,int);

void init() {

	glClearColor(0.0, 1.0, 0.4, 0.0); // arkaplan rengi ayari
	initGrid(SUTUN, SATIR);
}

int main(int argc, char** argv) {
	int mod;
	while (true) {
		std::cout << "******************************************************\n";
		std::cout << "HAZIRLAYANLAR:\nIsmet Bugra Topyurt - 210401053\nMehmet Emin Tok - 210401072\nSezer Ozcan - 210401133\nRecep Can Akdemir - 200401028\nEge Kilicaslan Salk - 200401021\n ";
		std::cout << "******************************************************\n";
		std::cout << "OYUN MODLARI:\n1-YILAN OYUNU\n2- 3 BOYUTLU NESNE\n";
		std::cout << "OYUNUN KURALLARI:YON TUSLARI ILE YILAN HAREKET ETTIRILIR VE YEMLER TOPLANMAYA CALISILIR\nDIKKAT! HER YEM YIYISTE YILAN HIZLANIR\n*****************\n";
		std::cout << "3 BOYUTLU NESNE KURALLARI: MOUSE SOL TUSUNA TIKLANDIGINDA X EKSENINDE-MOUSE ORTA TUSUNA TIKLANDIGINDA Y EKSENINDE\n-MOUSE SAG TUSUNA TIKLANDIGINDA Z EKSENINDE DONER\nNOT:KUP ILK BASTA Z EKSENINDE DONMEKTEDIR\n***************\n";
		std::cout << "MOD SECIN:";
		std::cin >> mod;
		switch (mod) {
		case 1:oyun_cagir(argc, argv);
			break;
		case 2:cokboyutlu_cagir(argc, argv);
			break;
		default:  std::cout << "GECERLI SECENEK GIRINIZ!!\n"; break;
			break;
		}

	}
	

	
	
	return 0;

}

// görüntü cagirma fonku
void display_cagir() {
	glClear(GL_COLOR_BUFFER_BIT);
	cizGrid();
	yilanCiz();
	yemCiz();
	glutSwapBuffers();
	if (oyunBitti) {
		//MessageBoxA(NULL,"Skorunuz:","OYUN BÝTTÝ!", 0);
		std::cout << "*******************************\n";
		std::cout << "OYUN BITTI!!---------SKORUNUZ:" << skor;
		std::cout << "\n*******************************";
		exit(0);
	}
}

void reshape_cagir(int w,int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);                  //koordinat sistemlerinin ayarý
	glLoadIdentity();
	glOrtho(0.0, SUTUN, 0.0, SATIR, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void timer_cagir(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / YENILEME, timer_cagir,0);      //göruntu 1 saniyede 10 kez cagrýldý
}

void keyboard_cagir(int key, int, int) {
	switch (key) {
	case GLUT_KEY_UP:
		if (yilanKonum != DOWN)
			yilanKonum = UP;
		break;
	case GLUT_KEY_DOWN:
		if (yilanKonum!=UP)
		{
			yilanKonum = DOWN;
		}
		break;
	case GLUT_KEY_RIGHT:
		if (yilanKonum!=LEFT)
		{
			yilanKonum = RIGHT;
		}
		break;
	case GLUT_KEY_LEFT:
		if (yilanKonum!=RIGHT)
		{
			yilanKonum = LEFT;
		}
		break;
	}
}

void oyun_cagir(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Yýlan Oyun");
	glutDisplayFunc(display_cagir);
	glutReshapeFunc(reshape_cagir);
	glutTimerFunc(0, timer_cagir, 0);
	glutSpecialFunc(keyboard_cagir);
	init();
	glutMainLoop();
}

static GLfloat hareket[] = { 0.0,0.0,0.0 };
static GLint axis = 2;  // x y z ekseni

void cokboyutlu_cagir(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("3 BOYUTLU KUP HAREKET");
	glutReshapeFunc(kupReshape);
	glutDisplayFunc(kupDisplay);
	glutIdleFunc(kupHareket);
	glutMouseFunc(mouse);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}

void kupHareket() {
	hareket[axis] += 1;
	if (hareket[axis] > 360.0)
		hareket[axis] -= 360;   //360 derece dondukten sonra sýfýrlar
	glutPostRedisplay();
}

void mouse(int buton,int durum,int x,int y) {
	if (buton == GLUT_LEFT_BUTTON && durum == GLUT_DOWN)
		axis = 0;                                           // x eksenýnde donus
	if (buton == GLUT_RIGHT_BUTTON && durum == GLUT_DOWN)
		axis = 2;											// z eksenýnde donus
	if (buton == GLUT_MIDDLE_BUTTON && durum == GLUT_DOWN)
		axis = 1;											// y eksenýnde donus
}

void kupReshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0 * (GLfloat)w, 2.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-2.0 * (GLfloat)w / (GLfloat)h, 2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}



void kupDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(hareket[0], 1.0, 0.0, 0.0); // x eksenýnde donus
	glRotatef(hareket[1], 0.0, 1.0, 0.0); // y eksenýnde donus
	glRotatef(hareket[2], 0.0, 0.0, 1.0); // z eksenýnde donus
	kupRengi();
	glFlush();
	glutSwapBuffers();
}

void kupRengi() {
	polygon(0, 3, 2, 1);
	polygon(2, 3, 7, 6);
	polygon(0, 4, 7, 3);
	polygon(1, 2, 6, 5);
	polygon(4, 5, 6, 7);
	polygon(0, 1, 5, 4);
}

GLfloat duzlem[8][3] = { {-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},{1.0,1.0,-1.0},{-1.0,1.0,-1.0},
	{-1.0,-1.0,1.0},{1.0,-1.0,1.0},{1.0,1.0,1.0},{-1.0,1.0,1.0}};

GLfloat renkler[8][3] = { {0.0,0.0,0.0},{1.0,0.0,0.0},{1.0,1.0,0.0},{0.0,1.0,0.0},
	{0.0,0.0,1.0},{1.0,0.0,1.0},{1.0,1.0,1.0},{0.0,1.0,1.0} };

void polygon(int a, int b, int c, int d) {
	glBegin(GL_POLYGON);
	glColor3fv(renkler[a]);
	glVertex3fv(duzlem[a]);
	glColor3fv(renkler[b]);
	glVertex3fv(duzlem[b]);
	glColor3fv(renkler[c]);
	glVertex3fv(duzlem[c]);
	glColor3fv(renkler[d]);
	glVertex3fv(duzlem[d]);
	glEnd();

}