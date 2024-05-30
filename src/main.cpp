#include <ncurses.h>

#define wprint(win, text) (mvwprintw(win, text.y, text.x, text.str))

struct Text{
    const char* str;
    int y = 0, x = 0;
    bool selectable = false;
};

class Window
{
private:
    WINDOW* win;
    Text selectables[32];
    int opt = 0;
public:
    Window(int heigh, int width){
        int x, y;
        getmaxyx(stdscr, y, x);
        win = newwin(heigh, width, (y/2)-(heigh/2), (x/2)-(width/2));
        box(win, 0, 0);
    }
    ~Window(){

    }

    void refresh(){
        wrefresh(win);
    }

    void add_opt(Text text){
        selectables[opt] = text;
        opt++;
        print(text);
    }

    void print(Text text){
        wprint(win, text);
    }

    void select(Text text){
        wattron(win, COLOR_PAIR(1));
        print(text);
        wattroff(win, COLOR_PAIR(1));
    }
};

int main(int argc,char** argv){
    initscr();
    start_color();

    init_pair(1, COLOR_WHITE, COLOR_CYAN);
    Window main(26, 36);
    Text text1 = {"My first text!", 2, 3};
    refresh();
    main.add_opt(text1);
    main.refresh();
    getch();

    main.select(text1);
    main.refresh();
    getch();

    endwin();
}