#include"system.h"
#include"game.h"

void gameTab(WINDOW *win, int tabuleiro[][10]){
    
    const char *messages[] = {
        "movimento invalido",                                       // 0
        "tecle espaço para salvar o ponto atual ou remover o mesmo" // 1
    };

    attron(A_BOLD);
        mvprintw(4,8, messages[1]);
        refresh();
    attroff(A_BOLD);

    int x, y, i, j, stop = 0;
    Point *p = NULL;

    p = init(p);
    
    i = j = 0;
    x = 55;
    y = 0;

    PrintTab(win, tabuleiro);

    while(1){

        p->x = i;
        p->y = j;

        wattron(win, COLOR_PAIR(3));
        
        if(verifyPoint(p)){
            wattron(win, COLOR_PAIR(1));
            mvwprintw(win, y+2, x+2, " 0");
            wrefresh(win);
            wattroff(win, COLOR_PAIR(1));
        }
        else{
            wattron(win, COLOR_PAIR(4));
            mvwprintw(win, y+2, x+2, " 0");
            wrefresh(win);
            wattroff(win, COLOR_PAIR(4));
        }

        int key;
        if((key = wgetch(win))){
            mvwprintw(win, 2,2, "\t\t\t");
        }

        switch(key){
            case 65: // UP
                if(y == 0 || tabuleiro[i-1][j] == -1){
                    mvwprintw(win, 2,2, messages[0]);
                    refresh();
                    wrefresh(win);
                }
                else{
                    --y;
                    --i;
                }

                break;
            case 67: // RIGHT
                if(x == 91 || tabuleiro[i][j+1] == -1){
                    mvwprintw(win, 2,2, messages[0]);
                    refresh();
                    wrefresh(win);
                }
                else{
                    x+=4;
                    j++;
                }

                break;

            case 66: // DOWN
                if(y == 9 || tabuleiro[i+1][j] == -1){
                    mvwprintw(win, 2,2, messages[0]);
                    refresh();
                    wrefresh(win);
                }
                else{
                    ++y;
                    ++i;
                }

                break;
            
            case 68: // LEFT
                if(x == 55 || tabuleiro[i][j-1] == -1){
                    mvwprintw(win, 2,2, messages[0]);
                    refresh();
                    wrefresh(win);
                }
                else{
                    x-=4;
                    j--;
                }

                break;

            case 32:
                mvwprintw(win, 2,2, "salvo");
                wrefresh(win);
                if(verifyPoint(p))
                    *p = loadPoint();
                else
                    savePoint(p);
                if(i == 9 && j == 9)
                    stop = 1;
                Print(win, ps);
                wrefresh(win);

                break;

        }
        if(stop)
            break;
    }
}