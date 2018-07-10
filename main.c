#include"system.h"
#include"interactive.h"
#include"verbose.h"
#include"game.h"

int main(void){ // ajustar responsividade
    extern Point *ps;

    setlocale(LC_ALL, "portuguese");

    //start lib ncurses
    initscr();

    noecho(); // nao exibe o valor da tecla apertada
    cbreak(); // encerrar com ctrl+c

    if(!has_colors()){
        endwin();
        printf("Error: Terminal nao suporta cores\n");
        return 1;
    }

    start_color();

    /*
    * COLOR_PAIR(N)
    * COLOR_BLACK   0
    * COLOR_RED     1
    * COLOR_GREEN   2
    * COLOR_YELLOW  3
    * COLOR_BLUE    4
    * COLOR_MAGENTA 5
    * COLOR_CYAN    6
    * COLOR_WHITE   7
    */

    // paleta
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);

    ps = NULL;
    int height, width, start_x, start_y, xmax, ymax;

    // int x, y, xbeg, ybeg, xmax, ymax;
    // getyx(stdscr, y, x);
    // getbegyx(stdscr, ybeg, xbeg);
    getmaxyx(stdscr, ymax, xmax);

    if(ymax <= 100 && xmax <= 100){
        endwin();
        printf("terminal muito pequeno, máxime seu terminal\n");
        return 1;
    }

    height = 20;
    width = 150;
    start_x = 6;
    start_y = 8;
    
    WINDOW *win_menu       = newwin(6, xmax-12, ymax-8, 5);
    WINDOW *win_content    = newwin(height, width, start_y, start_x);

    int tabuleiro[][10] = {
        //0  1  2  3  4  5  6  7  8  9
        { 0, 0,-1,-1, 0, 0, 0, 0, 0, 0}, // 0
        { 0,-1, 0, 0, 0,-1, 0,-1,-1,-1}, // 1
        { 0, 0, 0,-1, 0, 0, 0,-1, 0,-1}, // 2
        {-1,-1, 0,-1, 0,-1, 0, 0, 0, 0}, // 3
        {-1, 0, 0, 0,-1, 0, 0, 0,-1, 0}, // 4
        { 0, 0, 0,-1,-1,-1,-1, 0, 0,-1}, // 5
        {-1, 0, 0, 0, 0, 0, 0, 0,-1,-1}, // 6
        { 0, 0,-1, 0, 0,-1, 0, 0, 0, 0}, // 7
        { 0, 0, 0,-1,-1,-1, 0, 0,-1, 0}, // 8
        {-1,-1, 0, 0, 0, 0,-1, 0, 0, 0}  // 9
    };

    char *choices[] = {"1 - Interativo", "2 - Verboso", "3 - Game (beta)"};

    keypad(win_menu, 1);

    /*
    * A_NORMAL
    * A_STANDOUT
    * A_REVERSE
    * A_BLINK
    * A_DIM
    * A_BOLD
    * A_PROTECT
    * A_INVIS
    * A_ALTCHARSET
    * A_CHARTEXT
    */

    refresh();

    attron(A_REVERSE);
    printw(" ctrl+c para sair ");
    attroff(A_REVERSE); 

    attron(COLOR_PAIR(2));
    welcome(xmax/2 - 45, ymax/2 - 10);
    attroff(COLOR_PAIR(2));

    // MENU
    box(win_menu, 0, 0);
    refresh();
    wrefresh(win_menu);
    
    int op = menu(win_menu, choices);

    // END MENU

    switch(op){
        case 0 : // MODO INTERATIVO
            mvprintw(ymax/2 - 20, xmax/2 - 10, "Modo Interativo");
            refresh();
            
            box(win_content, 0, 0);
            wrefresh(win_content);

            searchPath(win_content, tabuleiro, 10, 10);
            wprintw(win_content, "\n");

            Print(win_content, ps);
            wrefresh(win_content);
            break;
        
        case 1: // MODO VERBOSO
            mvprintw(ymax/2 - 20, xmax/2 - 10, "Modo Verboso");
            refresh();

            box(win_content, 0, 0);
            wrefresh(win_content);

            searchPathVerbose(win_content, tabuleiro, 10, 10);
            wprintw(win_content, "\n");

            Print(win_content,ps);
            wrefresh(win_content);
            break;
        
        case 2: // MODO GAME
            mvprintw(ymax/2 - 20, xmax/2 - 10, "Modo Game");
            refresh();
            
            box(win_content, 0, 0);
            wrefresh(win_content);

            gameTab(win_content, tabuleiro);
            
            break;
        
        default:
            mvprintw(ymax/2 - 5, xmax/2 - 5, "Valor Incorreto");
    }

    attron(A_BLINK);
    attron(A_BOLD);
    mvprintw(ymax-3, xmax-45, " Created by: Rubens Santos <z1ron> ");
    refresh();
    attroff(A_BOLD);
    attroff(A_BLINK);

    getch();
    endwin(); // finish lib ncurses
    return 0;
}
