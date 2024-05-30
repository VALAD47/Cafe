//Made by VALAD47
#pragma once

#ifdef _WIN32

#include <ncursesw/ncurses.h>

#else

#include <ncurses.h>

#endif

struct Text{
    const char* str;
    int y = 0, x = 0;
};

#define wprint(win, text) (mvwprintw(win, text.y, text.x, text.str))

class Window
{
private:
    WINDOW* win;
    Text selectables[32];
    int opt = 0, selected = 0;
    void highlight(short color_pair, Text text);
public:
    Window(int heigh, int width);
    ~Window();
    void refresh();
    void add_opt(Text text);
    void add_opt(Text text[], int a);
    void clear_opt();
    void print(Text text);
    void select(int option);
    int get_selected();
    WINDOW* get_window();
};