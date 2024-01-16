#include <stdbool.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>
#include <windows.h>

const int X=15;
const int Y=15;
char Map[Y+2][X+2];

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
    snakebody* tmp=snake->snakehead;

    while(tmp->behind->behind!=NULL)
    {
        tmp=tmp->behind;
    }

    free(tmp->behind);
    tmp->behind=NULL;

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

void controldirection(snake* snake)
{
    if(_kbhit())
    {
        int ch=_getch();

        if(ch!=snake->direction)
        {
            snake->direction=ch;
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

    while(1)
    {   
        system("cls");
        
        controldirection(snake);

        Sleep(1000);

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
                if((snake->snakehead->x==tmp->x&&snake->snakehead->y==tmp->y)||(tmp->x==0||tmp->y==0||tmp->x==Y+1||tmp->y==X+1))
                {
                    death=true;
                }
                tmp=tmp->behind;
            }

            if(death) 
                break;

            for(int i=0;i<=Y+1;i++)
            {
                for(int j=0;j<=X+1;j++)
                {
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

            for(int i=0;i<Y+2;i++)
            {
                for(int j=0;j<X+2;j++)
                {
                    printf("%c",Map[i][j]);
                }
                printf("\n");
            }
    }


}

void init(snake* snake,apple* apple)
{
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

    init(s1,apple1);
    gamerun(s1,apple1);

}