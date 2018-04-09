#include"system.h"
#include"interactive.h"

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