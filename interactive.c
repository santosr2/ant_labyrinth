#include"system.h"
#include"interactive.h"

static void PrintTab(WINDOW *win, int tabuleiro[][10]){
    if(ps == NULL){
        for(int i=0, x=55; i < 10; i++, x+=4){
            for(int j=0, y=0; j < 10; j++, y++)
                mvwprintw(win, y+2, x+2,(tabuleiro[j][i] == 0) ? " %d   " : "%d   ",tabuleiro[j][i]);
            
            wprintw(win, "\n");
        }
    }
    else{
        Point *p = (Point *) malloc(sizeof(Point));
        for(int i=0, x=55; i < 10; i++, x+=4){
            for(int j=0, y=0; j < 10; j++, y++){
                p->x = j;
                p->y = i;
                if(verifyPoint(p)){
                    wattron(win, COLOR_PAIR(1));
                    mvwprintw(win, y+2, x+2, " %d   ",tabuleiro[j][i]);
                    wattroff(win,COLOR_PAIR(1));
                }
                else
                    mvwprintw(win, y+2, x+2,(tabuleiro[j][i] == 0) ? " %d   " : "%d   ",tabuleiro[j][i]);

                usleep(50000);
                wrefresh(win);
            }

            wprintw(win, "\n");
        }
    }
}

void searchPath(WINDOW *win, int tabuleiro[][10], int row, int col){
    if(tabuleiro != NULL){
        Point *p = NULL;
        p = init(p);

        for(; p->x < row; p->x++){
            for(; p->y+1 < col; p->y++){
                if(tabuleiro[p->x][p->y] == 0)
                    savePoint(p);
                else{
                    p->y--;
                    if(verifyPoint(p)){
                        if(tabuleiro[p->x+1][p->y] == -1)
                            *p = loadPoint();
                    }
                    break;
                }
            }
            if(p->y == col - 1 && tabuleiro[p->x][p->y] == 0){
                if(tabuleiro[p->x+1][p->y] == 0)
                    savePoint(p);
                else if(tabuleiro[p->x+1][p->y] == -1)
                    *p = loadPoint();
            }
            else if(p->y == col -1 && tabuleiro[p->x][p->y] == -1){
                p->x--;
                if(tabuleiro[p->x+1][p->y] == -1)
                    *p = loadPoint();
            }
        }
        if(p->y < col){
            p->x--;
            while(p->y < col){
                if(tabuleiro[p->x][p->y] == 0)
                    if(!verifyPoint(p))
                        savePoint(p);

                p->y++;
            }
        }
    }

    wrefresh(win);
    PrintTab(win, tabuleiro);

}