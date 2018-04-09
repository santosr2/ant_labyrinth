#include"system.h"

void welcome(int x, int y){
    mvprintw(y, x, "  ____  ____   ______      _       ____  ____   __ __  ____   ____  ____   ______  __ __ ");
    mvprintw(++y, x, " /    ||    \\ |      |    | |     /    ||    \\ |  |  ||    \\ |    ||    \\ |      ||  |  |");
    mvprintw(++y, x, "|  o  ||  _  ||      |    | |    |  o  ||  o  )|  |  ||  D  ) |  | |  _  ||      ||  |  |");
    mvprintw(++y, x, "|     ||  |  ||_|  |_|    | |___ |     ||     ||  ~  ||    /  |  | |  |  ||_|  |_||  _  |");
    mvprintw(++y, x, "|  _  ||  |  |  |  |      |     ||  _  ||  O  ||___, ||    \\  |  | |  |  |  |  |  |  |  |");
    mvprintw(++y, x, "|  |  ||  |  |  |  |      |     ||  |  ||     ||     ||  .  \\ |  | |  |  |  |  |  |  |  |");
    mvprintw(++y, x, "|__|__||__|__|  |__|      |_____||__|__||_____||____/ |__|\\_||____||__|__|  |__|  |__|__|");
    mvprintw(++y, 0, "\n");
    mvprintw(++y, 0, "\n");
    for(int k=++y; k <= 101; k++){
        attron(COLOR_PAIR(3));
        mvprintw(y, k, "  |");
        mvprintw(y+1, k, "  |.===.");
        mvprintw(y+2, k, "  {}o o{}");
        mvprintw(y+3, k, " O--(_)--O");
        attroff(COLOR_PAIR(3));
        refresh();
        usleep(15000);
    }
    attron(COLOR_PAIR(2));
    mvprintw(y+3, 113, "z1ron@2018");
    attroff(COLOR_PAIR(2));

}

int menu(WINDOW *win, char **choiches){
    int highlight = 0, choice;

    while(1){
        for(int i=0; i < 3; i++){
            if(i == highlight)
                wattron(win, A_REVERSE);
            mvwprintw(win, i+1, 1, choiches[i]);
            wattroff(win, A_REVERSE);
        }
        
        choice = wgetch(win);

        switch(choice){
            case KEY_UP:
                highlight--;

                if(highlight < 0)
                    highlight = 2;

                break;
            case KEY_DOWN:
                highlight++;
                
                if(highlight > 2)
                    highlight = 0;

                break;
            
            default:
                break;
        }

        if(choice == 10)
            break;
    }

    return highlight;
}

int verifyPoint(Point *p){ // verifica se o ponto esta na pilha
    Point *temp = ps;
    int b = 0; // bool
    while(temp != NULL){
        if(temp->x == p->x && temp->y == p->y){
            b = 1;
            break;
        }
        temp = temp->prox;
    }

    return b;
}

void Print(WINDOW *win, Point *p){
    int k = 0;

    mvwprintw(win, 14, 2,"Caminho:\n\t");
    while(p != NULL){
        k += 7;
        mvwprintw(win, 16, k,"(%d,%d) ",p->x,p->y);
        p = p->prox;
    }
    
    wprintw(win, "\n");
}

void PrintTab(WINDOW *win, int tabuleiro[][10]){
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

Point *init(Point *p){
    p = (Point *) malloc(sizeof(Point));
    p->x = p->y = 0;
    p->prox = NULL;

    return p;
}

void savePoint(Point *p){ // push
    Point *aux = (Point *) malloc(sizeof(Point));
    aux->prox = ps;
    aux->x = p->x;
    aux->y = p->y;
    ps = aux;
}

Point loadPoint(){

    //remove point
    Point *aux = ps;
    ps = ps->prox;
    free(aux);

    return *ps;
}