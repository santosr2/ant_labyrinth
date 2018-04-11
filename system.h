#ifndef __SYSTEM_H
#define __SYSTEM_H

// #include<stdio.h>
#include<curses.h>
#include<stdlib.h>
#include<unistd.h>
#include<locale.h>

typedef struct point{
    int x,y;
    struct point *prox;
}Point;

void welcome(int, int);
int menu(WINDOW *, char **);
int verifyPoint(Point *);
void Print(WINDOW *, Point *);
Point *init(Point *);
void savePoint(Point *p);
Point loadPoint(void);

Point *ps; // vetor points

#endif
