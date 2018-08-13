#include <ncurses.h>


int main()
{   initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    int row, col;
    getmaxyx(stdscr, row, col);
    

    endwin();
}