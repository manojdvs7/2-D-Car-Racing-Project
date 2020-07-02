/*						MINI PROJECT: Car Racing 
  										By: Harish 	    1602-17-737-075
  	  									Manoj	            1602-17-737-115
  	  									KumarSwami          1602-17-737-079			
  	  					************* -> START RACING NOW <- **************										 */
#include <GL/glut.h>
#include<iostream>
using namespace std;
int dv = 0,  carx = 700, cary = 50;//variables for user cars
int coinX=600,coinY=1600,Ccol=0,coins=0;//variables for coins
int car1=700, car2 = 300, Ecary1 = 0, Ecary2 = 300,col = 0;//variables for enemies
int display=0,ScAd=0,pause = 0, pas = 0, sc = 0;//variables for different display functions
float speed = 1, score = 0,highs,c1=1,c2=05,c3=0;//variables for calculating score and changing speed
char sscore[20],cs[20],s[20],hs[20];
void initGL()//gl funtion to perform all the one-time initialization operations
{
	glClearColor(0.0f, 1.0f, 0.0f, 0.0f); 
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 1100, 0, 600);
	glMatrixMode(GL_MODELVIEW);
}
void DisplayString(float x, float y, void *font, char*string)//funtion that prints strings on the opengl window screen
{
	char *c;
	glRasterPos3f(x, y, 0);
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}
void drawRoad()//function to display the road
{
	glBegin(GL_QUADS);
        glColor3f(0.5,0.5,0.5);
        glVertex2f(200, 0);
        glVertex2f(200 , 800);
        glVertex2f(800 , 800);
        glVertex2f(800, 0);
    glEnd();
}
void drawDividers()//functoin to display road dividers and footpath
{
	int i;
	glTranslatef(0,dv, 0);
	for(i=-1;i<11;i++)
	{
			glColor3f(1.0,1.0,1.0);
			glRectf(396,i*100,404,i*100+80);
		
			glColor3f(1.0,1.0,1.0);
			glRectf(596,i*100,604,i*100+80);

			glColor3f(1.0,1.0,1.0);
			glRectf(190,i*100-100,210,i*100-50);
			glRectf(790,i*100-100,810,i*100-50);

			glColor3f(0.0,0.0,0.0);
			glRectf(190,i*100-50,210,i*100);
			glRectf(790,i*100-50,810,i*100);
	}
	glLoadIdentity();
}
void drawCar()//function to display user car
{	
	glPointSize(8.0);
    glBegin(GL_POINTS);
        glColor3f(1.0,1.0,0.0);
        glVertex2f(carx-33, cary+39);
        glVertex2f(carx+33, cary+39);
    glPointSize(10.0);
        glColor3f(0.0,0.0,0.0);
        glVertex2f(carx-38,cary+27);
        glVertex2f(carx+38,cary+27);
        glVertex2f(carx-38,cary-30);
        glVertex2f(carx+38,cary-30);
    glEnd();

	glColor3f(0.8,0.0,0.0);
		glRectf(carx-40,cary-40,carx+40,cary+40);

	glColor3f(1.0,0.0,0.0);
		glRectf(carx-30,cary-25,carx+30,cary+10);

	glColor3f(0.0,0.0,0.0);
	glBegin(GL_QUADS);
		glVertex2f(carx+30,cary+10);
		glVertex2f(carx-30,cary+10);
		glVertex2f(carx-35,cary+21);
		glVertex2f(carx+35,cary+21);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2f(carx+31,cary);
		glVertex2f(carx+35,cary);
		glVertex2f(carx+35,cary+19);
		glVertex2f(carx+31,cary+9);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2f(carx-31,cary);
		glVertex2f(carx-35,cary);
		glVertex2f(carx-35,cary+19);
		glVertex2f(carx-31,cary+9);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2f(carx-31,cary-1);
		glVertex2f(carx-35,cary-1);
		glVertex2f(carx-35,cary-29);
		glVertex2f(carx-31,cary-24);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2f(carx+31,cary-1);
		glVertex2f(carx+35,cary-1);
		glVertex2f(carx+35,cary-29);
		glVertex2f(carx+31,cary-24);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2f(carx-36,cary-31);
		glVertex2f(carx+36,cary-31);
		glVertex2f(carx+30,cary-25);
		glVertex2f(carx-30,cary-25);
	glEnd();
}
void CoinPos()//function to give random positions for coins
{
	Ccol=0;ScAd=0;
	coinX=(rand()%550+200);
}
void PutCoin()//function to display coins
{
	if(!Ccol)
	{
		glColor3f(1.0,1.0,0);
		glRectf(coinX-20,coinY+3,coinX+20,coinY-3);
	}
	coinY-=speed;
	if(coinY<=0)
	{
		coinY=1200;
		CoinPos();
	}
}
void EnemiePos()//function to give random positions for enemie cars
{
	int a=rand(),b=rand(),t1=car1,t2=car2;
	if(a%3==0)
	{
		car1=300;
		car2=500;
	}
	else if(a%3==1)
	{
		car1=500;
		car2=700;
	}
	else 
	{
		car1=700;
		car2=300;
	}
	if(Ecary1>0)
		car1=t1;
	if(Ecary2>0)
		car2=t2;
}
void drawEnemies()//funtion to draw enemie cars
{
	glBegin(GL_POINTS);
	   glPointSize(8.0);
	   glColor3f(1.0, 1.0, 0.0);
		glVertex2f(car1 - 35, Ecary1 + 39);
		glVertex2f(car1 + 35, Ecary1 + 39);
	   glColor3f(0.0, 0.0, 0.0);
	   glPointSize(10.0);
        glVertex2f(car1-38,Ecary1+27);
        glVertex2f(car1+38,Ecary1+27);
        glVertex2f(car1-38,Ecary1-30);
        glVertex2f(car1+38,Ecary1-30);
	glEnd();

	glColor3f(0.4, 0.2, 0.5);
	glRectf(car1 - 40, Ecary1 - 40,car1 + 40, Ecary1 + 40);

	glColor3f(0.0, 0.0, 0.0);
	glRectf(car1 + 30, Ecary1 + 10,car1 - 35, Ecary1 + 21);

	glBegin(GL_QUADS);
		glVertex2f(car1 + 31, Ecary1);
		glVertex2f(car1 + 35, Ecary1);
		glVertex2f(car1 + 35, Ecary1 + 19);
		glVertex2f(car1 + 31, Ecary1 + 9);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2f(car1 - 31, Ecary1);
		glVertex2f(car1 - 35, Ecary1);
		glVertex2f(car1 - 35, Ecary1 + 19);
		glVertex2f(car1 - 31, Ecary1 + 9);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2f(car1 - 31, Ecary1 - 1);
		glVertex2f(car1 - 35, Ecary1 - 1);
		glVertex2f(car1 - 35, Ecary1- 29);
		glVertex2f(car1 - 31, Ecary1 - 24);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2f(car1 + 31, Ecary1 - 1);
		glVertex2f(car1 + 35, Ecary1 - 1);
		glVertex2f(car1 + 35, Ecary1 - 29);
		glVertex2f(car1 + 31, Ecary1 - 24);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2f(car1 - 36, Ecary1 - 31);
		glVertex2f(car1 + 36, Ecary1 - 31);
		glVertex2f(car1+ 30, Ecary1 - 25);
		glVertex2f(car1 - 30, Ecary1 - 25);
	glEnd();

	//ENEMIE CAR2
	glBegin(GL_POINTS);
	   glPointSize(8.0);
	   glColor3f(1.0, 1.0, 0.0);
		glVertex2f(car2 - 35, Ecary2 + 39);
		glVertex2f(car2 + 35, Ecary2 + 39);
	   glColor3f(0.0, 0.0, 0.0);
	   glPointSize(10.0);
        glVertex2f(car2-38,Ecary2+27);
        glVertex2f(car2+38,Ecary2+27);
        glVertex2f(car2-38,Ecary2-30);
        glVertex2f(car2+38,Ecary2-30);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.8, 0.2, 0.5);
		glVertex2f(car2 - 40, Ecary2 - 40);
		glVertex2f(car2 + 40, Ecary2 - 40);
		glVertex2f(car2 + 40, Ecary2 + 40);
		glVertex2f(car2 - 40, Ecary2 + 40);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
		glVertex2f(car2 + 30, Ecary2 + 10);
		glVertex2f(car2 - 30, Ecary2 + 10);
		glVertex2f(car2 - 35, Ecary2 + 21);
		glVertex2f(car2 + 35, Ecary2 + 21);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2f(car2 + 31, Ecary2);
		glVertex2f(car2 + 35, Ecary2);
		glVertex2f(car2 + 35, Ecary2 + 19);
		glVertex2f(car2 + 31, Ecary2 + 9);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2f(car2 - 31, Ecary2);
		glVertex2f(car2 - 35, Ecary2);
		glVertex2f(car2 - 35, Ecary2 + 19);
		glVertex2f(car2 - 31, Ecary2 + 9);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2f(car2 - 31, Ecary2 - 1);
		glVertex2f(car2 - 35, Ecary2 - 1);
		glVertex2f(car2 - 35, Ecary2 - 29);
		glVertex2f(car2 - 31, Ecary2 - 24);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2f(car2 + 31, Ecary2 - 1);
		glVertex2f(car2 + 35, Ecary2 - 1);
		glVertex2f(car2 + 35, Ecary2 - 29);
		glVertex2f(car2 + 31, Ecary2 - 24);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2f(car2 - 36, Ecary2 - 31);
		glVertex2f(car2 + 36, Ecary2 - 31);
		glVertex2f(car2 + 30, Ecary2 - 25);
		glVertex2f(car2 - 30, Ecary2 - 25);
	glEnd();

	Ecary1 -= speed;
	if (Ecary1 < -50)
	{
		EnemiePos();
		Ecary1 = 750;
	}
	Ecary2 -= speed;
	if (Ecary2 < -50)
	{
		EnemiePos();
		Ecary2 = 750;
	}
}
void EnemieCol()//function to check enemie car collide condition
{
	if (((carx - 40 <= car1 + 40 && carx - 40 >= car1 - 40) || (carx + 40 <= car1 + 40 && carx+40 >= car1 - 40)) && ((cary - 40 < Ecary1 + 40 && cary - 40 > Ecary1 - 40) || (cary + 40 < Ecary1 + 40 && cary + 40 > Ecary1 - 40)))
		col = 1;
	else if (((carx - 40 <= car2 + 40 && carx - 40 >= car2 - 40) || (carx + 40 <= car2 + 40 && carx+40 >= car2 - 40)) && ((cary - 40 < Ecary2 + 40 && cary - 40 > Ecary2 - 40) || (cary + 40 < Ecary2 + 40 && cary + 40 > Ecary2 - 40)))
		col = 1;
}
void CoinCol()//function to ckeck car touching the coins
{
	if (((carx - 40 <= coinX + 20 && carx - 40 >= coinX - 20)||(coinX+20 > carx-40 && coinX-20 < carx+40) || (carx + 40 <= coinX + 20 && carx+40 >= coinX - 20)) && ((cary - 40 < coinY + 3 && cary - 40 > coinY - 3) || (cary + 40 < coinY + 3 && cary + 40 > coinY - 3)))	
	{   Ccol=1; 
		if(!ScAd)
			coins++;
	}
}
void DisplayInstructions()//function to display instructions
{
	glutSwapBuffers();
	glColor3f(0.0,0.4,0.8);
	glRectf(0,800,1100,0);
	glColor3f(1.0, 1.0, 1.0);
	char s1[] = " CAR RACING GAME";
	char s2[] = "-> This is   a car racing game where you need to cross the opponent vechiles without crashing them.";
	glColor3f(1.0, 0.5, 0.0);
	DisplayString(0, 575, GLUT_BITMAP_TIMES_ROMAN_24, s1);
	glColor3f(1.0, 1.0, 1.0);
	DisplayString(0, 545, GLUT_BITMAP_TIMES_ROMAN_24, s2);
	
	char s4[] = "ARROW TO MOVE UP";
	DisplayString(50, 515, GLUT_BITMAP_TIMES_ROMAN_24, s4);
	glBegin(GL_TRIANGLES);
		glVertex2i(20,515);
		glVertex2i(40,515);
		glVertex2i(30,535);
	glEnd();
		
	char s5[] = "ARROW TO MOVE DOWN";
	DisplayString(50, 485, GLUT_BITMAP_TIMES_ROMAN_24, s5);
	glBegin(GL_TRIANGLES);
		glVertex2i(20, 505);
		glVertex2i(40, 505);
		glVertex2i(30, 485);
	glEnd();

	char s6[] = "ARROW TO MOVE RIGHT";
	DisplayString(50, 455, GLUT_BITMAP_TIMES_ROMAN_24, s6);
	glBegin(GL_TRIANGLES);
		glVertex2i(20,475 );
		glVertex2i(20,455 );
		glVertex2i(40,465);
	glEnd();

	char s8[] = "ARROW TO MOVE LEFT";
	DisplayString(50, 425, GLUT_BITMAP_TIMES_ROMAN_24, s8);
	glBegin(GL_TRIANGLES);
		glVertex2i(40,445);
		glVertex2i(40, 425);
		glVertex2i(20,435 );
	glEnd();

	char s7[]="-> Collect the coins to increase score by 10 ";
	char s9[]="-> Press F5 to pause and resume the game";
	DisplayString(50, 395, GLUT_BITMAP_TIMES_ROMAN_24, s7);
	DisplayString(50, 365, GLUT_BITMAP_TIMES_ROMAN_24, s9);
glutSwapBuffers();
}
void DisplayScreen()//function to display home screen of game
{
	glColor3f(0.2,0.2,0.2);
	glRectf(0,800,1100,0);
	char s1[] = "CAR RACING GAME ";
	char s2[] = "START";
	char s3[] = "NEW GAME";
	char s4[] = "INSTRUCTIONS";
	char s5[] = "HIGH SCORE";
	char s6[] = "EXIT";
	char s7[] = "Please press RIGHT CLICK to see options";
	glColor3f(1.0,0.0,0.0);
		DisplayString(400, 550, GLUT_BITMAP_TIMES_ROMAN_24, s1);
	glColor3f(1,1,1);
		DisplayString(100, 450, GLUT_BITMAP_TIMES_ROMAN_24, s2);
		DisplayString(100, 420, GLUT_BITMAP_TIMES_ROMAN_24, s3);
		DisplayString(100, 390, GLUT_BITMAP_TIMES_ROMAN_24, s4);
		DisplayString(100, 360, GLUT_BITMAP_TIMES_ROMAN_24, s5);
		DisplayString(100, 320, GLUT_BITMAP_TIMES_ROMAN_24, s6);
	glColor3f(1,1,0);
		DisplayString(100, 200, GLUT_BITMAP_TIMES_ROMAN_24, s7);
		drawCar();
		cary+=10;
		if(cary>=800)
			cary=-10;
	glutSwapBuffers();
	glutPostRedisplay();
}
void GetHighScore()//function to read high score from file
{
	FILE *fp;
	fp = fopen("HIGHSCORE.txt", "r");
	fscanf(fp, "%f", &highs);
	fclose(fp);
}
void ChangeHighscore()//function to change high score in the file
{
	FILE *fp;
	fp = fopen("HIGHSCORE.txt", "w");
	fprintf(fp, "%.0f", score);
	fclose(fp);
}
void DisplayScore()//function to display score when the car collides
{
	glutSwapBuffers();
	glColor3f(0.2,0.2,0.2);
	glRectf(0,800,1100,0);
	glColor3f(1,1,1);
	sprintf(s, "YOUR SCORE: %.0f", score);
	DisplayString(400, 450, GLUT_BITMAP_TIMES_ROMAN_24, s);
	if (score > highs)
	{
		ChangeHighscore();
		char s2[]="Congratulations :),New HighScore ";
		DisplayString(400,400,GLUT_BITMAP_TIMES_ROMAN_24,s2);
	}
		else
	{
		char s1[]="BETTERLUCK NEXT TIME :(";
		DisplayString(400,400,GLUT_BITMAP_TIMES_ROMAN_24,s1);
	}
	GetHighScore();
	sprintf(hs, "HIGHEST SCORE:%.0f", highs);
	glColor3f(1,1,1);
	DisplayString(400,425,GLUT_BITMAP_TIMES_ROMAN_24,hs);
	glutSwapBuffers();
}
void DisplayHighscore()//function to display high score 
{
	glutSwapBuffers();
	glColor3f(0.2,0.2,0.2);
	glRectf(0,800,1100,0);
	glColor3f(1,1,1);
	GetHighScore();
	sprintf(hs, "HIGHEST SCORE:%.0f", highs);
	DisplayString(400, 425, GLUT_BITMAP_TIMES_ROMAN_24, hs);
	glutSwapBuffers();
}
void Display()//this is the main display funtion from where other displays are called based on user choice
{
    glClear(GL_COLOR_BUFFER_BIT);
    if(display==1 && pause==0)
    {
    drawRoad();
    drawDividers();
    drawCar();
    drawEnemies();
    PutCoin();
    EnemieCol();
    CoinCol();
    glColor3f(1,1,1);
	sprintf(sscore, "Score: %.0f", score);
	DisplayString(870, 500, GLUT_BITMAP_TIMES_ROMAN_24, sscore);
	if(score>highs)
		highs = score;
	sprintf(hs, "HighScore: %.0f", highs);
	sprintf(cs,"Coins: %d",coins);
	DisplayString(870, 475, GLUT_BITMAP_TIMES_ROMAN_24, hs);
	DisplayString(870, 525, GLUT_BITMAP_TIMES_ROMAN_24, cs);
	dv-=15;
	if(dv<=-90)
		dv=0;
	if(col)
		display=4;
	if(Ccol && !ScAd)
		{
			ScAd=1;
			score+=10;
		}
		score+=speed/100;
		sc=score;
		speed=1+score/1000;

		glutSwapBuffers();
		glutPostRedisplay();
	}
	else if(display==0)
		DisplayScreen();
	else if(display==2)
		DisplayHighscore();
	else if(display==3)
		DisplayInstructions();
	else if(display==4)
		DisplayScore();
	if(pause==1)
	{
		glutSwapBuffers();
		glutPostRedisplay();
	}
}
void Specialkey(int key, int x, int y)//function to access keyboard keys
{
	switch(key)
	{
		case GLUT_KEY_UP:if(cary<550)
							cary+=20;
						break;
		case GLUT_KEY_DOWN:if(cary>50)
							cary-=20;
						break;

		case GLUT_KEY_LEFT:if(carx>260)
							carx-=40;
	             		break;
		case GLUT_KEY_RIGHT:if(carx<740)
							carx+=40;
	             		break;
	    case GLUT_KEY_F5:if(pause==0)
	    					{
	    						pause=1;display=0;
	    					}
	    					else if(pause==1)
	    					{
	    						cout<<"enter";pause=0;display=1;
	    					}break;
	}
}
void options(int c)//function to access menu bar
{
	switch (c)
	{
	case 1:
	case 2:col=Ecary1=0;Ecary2=300;car1=300;car2=700;ScAd=0;Ccol=0,coins=0;//newgame
			speed=1;score=0;carx=500;cary=50;display=1;coinX=600;coinY=1600;
			break;
	case 3:display=2;break;
	case 4:display=3;break;
	case 5:display=0;carx=800;cary=10;break;
	case 6:exit(1);
	}
	glutPostRedisplay();
}
int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1100,800);
    glutCreateWindow("2D Car Racing game");
    initGL();
    glutDisplayFunc(Display);
    glutCreateMenu(options);
	glutAddMenuEntry("Start", 1);
	glutAddMenuEntry("NewGame", 2);
	glutAddMenuEntry("HighScore",3);
	glutAddMenuEntry("Instructions",4);
	glutAddMenuEntry("Back",5);
	glutAddMenuEntry("Exit",6);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	GetHighScore();
    glutSpecialFunc(Specialkey);
    glutMainLoop();
}
