#define BULLET_MAX 64
#define MARGIN_TOP 6
#define MARGIN_RIGHT 68
#define MARGIN_BOTTON 24

#include <conio.h>		//getch, kbhit
#include <pthread.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <windows.h>    //Beep, Sleep

#include "Serial.cpp"	// Library described above

typedef struct{
    int time;
} ARG;

typedef struct {
	char status;
	char x;
	char y;
} BUL;

ARG my_args;
BUL bullet[BULLET_MAX];

char cursor(short, short);
void gotoxy(short, short);
void draw_bullet(int, int);
void draw_star(int, int);
void draw_ship(int, int);
void erase_ship(int, int);
void erase_space(int, int);
void shoot(int);
void rand_star();
void scoref();
void countf();
void bulletf(int);
void draw_main();

time_t time_start = time(NULL);
int timechk = (int)time_start;
int score = 0;

pthread_t tid;
pthread_attr_t attr;
pthread_mutex_t lock;
pthread_mutexattr_t muattr;

void setcursor(bool visible);
void setcolor(int fg, int bg);

void *threadBeep(void *arg)
{
	ARG *my_args = (ARG*)arg;
    Beep(my_args->time, 25);
	pthread_exit(NULL);
}

void pthBeep(int time){
    my_args.time = time;
    /*if(time==1000){
        pthread_mutex_lock(&lock);
        Sleep(50);
        pthread_mutex_unlock(&lock);
    }*/
    if(pthread_create(&tid, &attr, threadBeep, &my_args)){
        exit(-1);
    }
    /*if(pthread_join(tid, &lock)){
        //exit(-1);
    }*/
}

int _tmain(int argc, _TCHAR* argv[]) {
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);    //PTHREAD_CREATE_JOINABLE

    pthread_mutex_init(&lock, &muattr);

	srand(time(NULL));

    Serial* SP = new Serial("\\\\.\\COM3");

	if (!(SP->IsConnected()))  printf("not connected.\n");

	char incomingData[256] = "";
	int dataLength = 255;
	int readResult = 0;

	scoref();
	setcursor(0);

	for (int i=0; i<BULLET_MAX; i++) bullet[i].status = 0;
	char left = 0, right = 0;
	char status = 0;
	char ch = 0;
	char x = 34;
	char y = 10;

	for (int i=0; i<20; i++) rand_star();
    draw_main();
	draw_ship(x, y);
    bulletf(status);

	do {
        ch = '\0';
        countf();
        readResult = SP->ReadData(incomingData,dataLength);
        incomingData[readResult] = 0;

		int axis_x = incomingData[0]-48;
		int axis_y = incomingData[2]-48;
        int axis_z = incomingData[4]-48;

        if(axis_z == 9) ch = 'b';

        if(ch == '\0')  {

            switch(axis_x){
                case 2: ch = 'd'; break;
                case 1: ch = '\0'; break;
                case 0: ch = 'a'; break;
            }
        }

        if(ch == '\0')  {

            switch(axis_y){
                case 2: ch = 'w'; break;
                case 1: ch = '\0'; break;
                case 0: ch = 's'; break;
            }
        }

		if (ch) {
			//ch = getch();

			if (ch == 'a') {
                if (x == 0) continue;
				//left = 1;
				//right = 0;
				erase_ship(x, y);
				draw_ship(--x, y);
			}

			if (ch == 'd') {
                if (x == MARGIN_RIGHT) continue;
				//left = 0;
				//right = 1;
				erase_ship(x, y);
				draw_ship(++x, y);
			}

			if (ch == 'w') {
				if (y == MARGIN_TOP) continue;
				erase_ship(x, y);
				draw_ship(x, --y);
			}

			if (ch == 's') {
				if (left || right) {
					left = 0;
					right = 0;
					continue;
				}
				if (y == MARGIN_BOTTON) continue;

				erase_ship(x, y);
				draw_ship(x, ++y);
			}

			if (ch == 'b') {
				bullet[status].status = 1;
				bullet[status].x = x+2;
				bullet[status].y = y;
				draw_bullet(bullet[status].x, --bullet[status].y);
				status++;
                bulletf(status);
			}
			//fflush(stdin);
		}

		/*if (left) {
			if (x == 0) {
				left = 0;
				continue;
			}
			erase_ship(x, y);
			draw_ship(--x, y);
		}

		if (right) {
			if (x == MARGIN_RIGHT) {
				right = 0;
				continue;
			}
			erase_ship(x, y);
			draw_ship(++x, y);
		}*/

		for (int i = 0; i<status; i++) {
			shoot(i);
		}

		if(status==BULLET_MAX){
			return 0;
		}

	Sleep(100);
	} while (SP->IsConnected());

    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&lock);
    pthread_exit(NULL);

	return 0;
}

void setcursor(bool visible) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void setcolor(int fg, int bg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

char cursor(short x, short y){
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2];
	COORD c = {x, y};
	DWORD num_read;
	if( !ReadConsoleOutputCharacter(hStd,(LPTSTR)buf,1,c,(LPDWORD)&num_read) ) {
		return '\0';
	} else {
		return buf[0];
	}
}

void gotoxy(short x, short y) {
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_bullet(int x, int y) {
	setcolor(4, 4);
	gotoxy(x, y);
	printf("^");
}

void draw_star(int x, int y) {
	setcolor(3, 0);
	gotoxy(x, y);
	printf("*");
}

void draw_ship(int x, int y) {
	setcolor(2, 0);
	gotoxy(x, y);
	printf("<-0->");
}

void erase_ship(int x, int y) {
	setcolor(2, 0);
	gotoxy(x, y);
	printf("     ");
}

void erase_space(int x, int y) {
	setcolor(2, 0);
	gotoxy(x, y);
	printf(" ");
}

void shoot(int i) {
	if (bullet[i].status == 1) {
		static char c;
		c = cursor(bullet[i].x, bullet[i].y-1);

		pthBeep(500);
		erase_space(bullet[i].x, bullet[i].y);

		if (bullet[i].y == 0 || c == '*') {
			bullet[i].status = 0;

			if(c == '*'){
				erase_space(bullet[i].x, bullet[i].y-1);
				pthBeep(1000);
				rand_star();
				scoref();
			}

		} else {
			draw_bullet(bullet[i].x, --bullet[i].y);
		}
	}
}

void rand_star(){
	int x = rand()%60+10;
	int y = rand()%3+2;

	if(cursor(x, y) != '*')
		draw_star(x, y);
}

void scoref(){
	gotoxy(76, 1);
	setcolor(2, 0);
	printf("%3d", score++);
}

void countf(){
    gotoxy(76, 3);
    setcolor(2, 0);
    printf("%3d\n", (int)time(NULL) - timechk);
}

void bulletf(int bullet){
	gotoxy(76, 5);
	setcolor(2, 0);
	printf("%3d", BULLET_MAX-bullet);
}

void draw_main(){
    for(int y=0; y<=24; y++){
        gotoxy(73, y);
        printf("|");
        gotoxy(79, y);
        printf("|");
    }
    for(int x=0; x<=79; x++){
        gotoxy(x, 25);
        printf("-");
    }
    for(int x=74; x<=78; x++){
        gotoxy(x, 2);
        printf("-");
        gotoxy(x, 4);
        printf("-");
        gotoxy(x, 6);
        printf("-");
    }
    gotoxy(74, 1); printf("s:");
    gotoxy(74, 3); printf("t:");
    gotoxy(74, 5); printf("b:");
}
