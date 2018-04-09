#include"system.h"
#include"verbose.h"

void searchPathVerbose(WINDOW *win, int tabuleiro[][10], int row, int col){
    if(tabuleiro != NULL){

        PrintTab(win, tabuleiro);

        Point *p = NULL;
        p = init(p);

        int x, y;

        for(y = 0; p->x < row; p->x++, y++){
            for(x = 55; p->y+1 < col; p->y++, x+=4){
                if(tabuleiro[p->x][p->y] == 0){
                    savePoint(p);
                    wattron(win, COLOR_PAIR(1));
                    mvwprintw(win, y+2, x+2, " 0");
                    wattroff(win, COLOR_PAIR(1));
                    usleep(TEMPO);
                }
                else{
                    p->y--;
                    y--;
                    if(verifyPoint(p)){
                        if(tabuleiro[p->x+1][p->y] == -1){
                            *p = loadPoint();
                            wattron(win, COLOR_PAIR(3));
                            mvwprintw(win, y+2, x+2, " 0");
                            wattroff(win, COLOR_PAIR(3));
                            usleep(TEMPO);
                        }
                    }
                    break;
                }
            }
            if(p->y == col - 1 && tabuleiro[p->x][p->y] == 0){
                if(tabuleiro[p->x+1][p->y] == 0){
                    savePoint(p);
                    wattron(win, COLOR_PAIR(1));
                    mvwprintw(win, y+2, x+2, " 0");
                    wattroff(win, COLOR_PAIR(1));
                    usleep(TEMPO);
                }
                else if(tabuleiro[p->x+1][p->y] == -1){
                    *p = loadPoint();
                    wattron(win, COLOR_PAIR(3));
                    mvwprintw(win, y+2, x+2, " 0");
                    wattroff(win, COLOR_PAIR(3));
                    usleep(TEMPO);
                }
            }
            else if(p->y == col -1 && tabuleiro[p->x][p->y] == -1){
                p->x--;
                x-=4;
                if(tabuleiro[p->x+1][p->y] == -1){
                    *p = loadPoint();
                    wattron(win, COLOR_PAIR(3));
                    mvwprintw(win, y+2, x+2, " 0");
                    wattroff(win, COLOR_PAIR(3));
                    usleep(TEMPO);
                }
            }
        }
        if(p->y < col){
            p->x--;
            x-=4;
            while(p->y < col){
                if(tabuleiro[p->x][p->y] == 0)
                    if(!verifyPoint(p)){
                        savePoint(p);
                        wattron(win, COLOR_PAIR(1));
                        mvwprintw(win, y+2, x+2, " 0");
                        wattroff(win, COLOR_PAIR(1));
                        usleep(TEMPO);
                    }

                p->y++;
            }
        }
    }
}