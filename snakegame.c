#include <stdbool.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>
#include <windows.h>

const int X=20;
const int Y=20;
char Map[Y+2][X+2];

int counterdirection[81];


typedef struct snakebody
{
    int x;
    int y;
    snakebody* behind;
}snakebody;

typedef struct 
{
    snakebody* snakehead;
    int size;
    int direction;

}snake;

typedef struct
{
    int x;
    int y;
}apple;



void HideCursor()
{
	HANDLE fd = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cinfo;
	cinfo.bVisible = 0;
	cinfo.dwSize = 1;
	SetConsoleCursorInfo(fd, &cinfo);
}

void setdirection(int direction,snake* snake)
{
    snake->direction=direction;
}

void addtohead(int x,int y,snake* snake)
{
    snakebody* newbody = (snakebody*)malloc(sizeof(snakebody));

    newbody->x=x;
    newbody->y=y;
    newbody->behind=snake->snakehead;

    snake->size++;

    snake->snakehead=newbody;

}

void deletetail(snake* snake)
{   
    snakebody* current=snake->snakehead;
    snakebody* prev=NULL;

    while(current->behind!=NULL)
    {
        prev=current;
        current=current->behind;
    }

    free(current);
    prev->behind=NULL;

    snake->size--;


}

bool eatapple(apple* apple,snake* snake)
{
    if(snake->snakehead->x==apple->x&&snake->snakehead->y==apple->y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void controldirection(snake* snake,int lastdirection)
{   
    int ch1=0;
    int ch2=0;
    if(_kbhit())
    {   
        ch1=_getch();
        ch2=_getch();

        if(ch1==224&&ch2!=counterdirection[lastdirection])
        {
            snake->direction=ch2;
        }

    }
}

int generateRandomNumber(int min, int max) 
{
    return min + rand() % (max - min + 1);
}


void gamerun(snake* snake ,apple* apple)
{   
    bool death=false;
    int lastdirection=72;

    while(1)
    {   
        Sleep(150);
        controldirection(snake,lastdirection);
        

        system("cls");

        lastdirection=snake->direction;
        switch(snake->direction)
            {
                case 72:
                {
                    addtohead(snake->snakehead->x,snake->snakehead->y-1,snake);
                    break;
                }
                case 80:
                {
                    addtohead(snake->snakehead->x,snake->snakehead->y+1,snake);
                    break;
                }
                case 75:
                {
                    addtohead(snake->snakehead->x-1,snake->snakehead->y,snake);
                    break;
                }
                case 77:
                {
                    addtohead(snake->snakehead->x+1,snake->snakehead->y,snake);
                    break;
                }
            }

            if(!eatapple(apple,snake))
            {
                deletetail(snake);
            }
            else
            {
                apple->x=generateRandomNumber(1,X);
                apple->y=generateRandomNumber(1,Y);
            }

            snakebody* tmp=snake->snakehead->behind;

            while(tmp!=NULL)
            {
                if((snake->snakehead->x==tmp->x&&snake->snakehead->y==tmp->y)||(snake->snakehead->x==0||snake->snakehead->y==0||snake->snakehead->x==X+1||snake->snakehead->y==Y+1))
                {
                    death=true;
                    break;
                }
                tmp=tmp->behind;
            }

            

            for(int i=0;i<=Y+1;i++)
            {
                for(int j=0;j<=X+1;j++)
                {   
                    if(i==0||j==0||i==Y+1||j==X+1)
                        Map[i][j]='@';
                    else
                        Map[i][j]=' ';
                }
            }

            tmp=snake->snakehead;

            Map[tmp->y][tmp->x]='$';
            tmp=tmp->behind;

            while(tmp!=NULL)
            {
                Map[tmp->y][tmp->x]='#';
                tmp=tmp->behind;
            }

            Map[apple->y][apple->x]='*';

            char buffer[100000];
            int cnt=0;

            for(int i=0;i<Y+2;i++)
            {
                for(int j=0;j<X+2;j++)
                {
                    buffer[cnt++]=Map[i][j];
                }
                buffer[cnt++]='\n';
            }
            buffer[cnt]='\0';
            printf("%s",buffer);
            printf("长度:%d\n",snake->size);

            if(death) 
                break;
    }


}

void init(snake* snake,apple* apple)
{   
    counterdirection[72]=80;
    counterdirection[80]=72;
    counterdirection[75]=77;
    counterdirection[77]=75;

    snake->direction=72;
    snake->size=3;

    snakebody* tmp=(snakebody*)malloc(sizeof(snakebody));
    tmp->behind=(snakebody*)malloc(sizeof(snakebody));
    tmp->behind->behind=(snakebody*)malloc(sizeof(snakebody));
    tmp->x=6;
    tmp->y=6;
    tmp->behind->x=6;
    tmp->behind->y=7;
    tmp->behind->behind->x=6;
    tmp->behind->behind->y=8;
    tmp->behind->behind->behind=NULL;

    snake->snakehead=tmp;

    apple->x=11;
    apple->y=7;

}

int main()
{
    snake* s1=(snake*)malloc(sizeof(snake));
    apple* apple1=(apple*)malloc(sizeof(apple));

    srand(time(NULL));

    HideCursor();
    init(s1,apple1);

    printf("方向键控制,按回车开始");

    getchar();

    gamerun(s1,apple1);

    printf("死了\n");

    system("pause");


}
