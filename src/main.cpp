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
    int opt = 0, selected = 0;

    void highlight(short color_pair, Text text){
        wattron(win, COLOR_PAIR(color_pair));
        wprint(win, text);
        wattroff(win, COLOR_PAIR(color_pair));
    }

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
        if(opt-1==0) highlight(1, text);
    }

    void print(Text text){
        wprint(win, text);
    }

    void select(int option){
        switch (option){
        case 1:
            if(selected==0) return;
            selected--;
            highlight(1, selectables[selected]);
            print(selectables[selected+1]);

            break;
        case 0:
            if(opt-1==selected) return;
            selected++;
            highlight(1, selectables[selected]);
            print(selectables[selected-1]);

            break;
        default:
            break;
        }
        mvprintw(0,0,"Options: %d\tSelected: %d", opt, selected);
        refresh();
    }
};

int main(int argc,char** argv){
    initscr();
    start_color();

    init_pair(1, COLOR_WHITE, COLOR_CYAN);
    Window main(26, 36);
    refresh();
    main.add_opt({"My first text!", 2, 3});
    main.add_opt({"My second text!", 3, 3});
    main.add_opt({"My second text!", 4, 3});
    main.refresh();
    keypad(stdscr, true);
    while (true)
    {
        int i = getch();
        switch (i)
        {
        case KEY_DOWN:
            main.select(0);
            break;
        case KEY_UP:
            main.select(1);
            break;
        default:
            endwin();
            return 0;
            break;
        }
    }
}