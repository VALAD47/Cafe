//Made by VALAD47
#include "window.h"
void Window::highlight(short color_pair, Text text)
{
    wattron(win, COLOR_PAIR(color_pair));
    wprint(win, text);
    wattroff(win, COLOR_PAIR(color_pair));
}

Window::Window(int heigh, int width)
{
    int x, y;
    getmaxyx(stdscr, y, x);
    win = newwin(heigh, width, (y / 2) - (heigh / 2), (x / 2) - (width / 2));
    box(win, 0, 0);
}
Window::~Window()
{
    delwin(win);
}

void Window::refresh()
{
    wrefresh(win);
}

void Window::add_opt(Text text)
{
    selectables[opt] = text;
    opt++;
    if (opt - 1 == 0)
        highlight(1, text);
    else
        print(text);
}

void Window::add_opt(Text text[], int a)
{
    for (int i = 0; i < a; i++)
    {
        add_opt(text[i]);
    }
}

void Window::clear_opt()
{
    for (int i = 0; i < 32; i++)
    {
        selectables[i] = {};
    }
    opt = 0;
    selected = 0;
    wclear(win);
    box(win, 0, 0);
}

void Window::print(Text text)
{
    wprint(win, text);
}

void Window::select(int option)
{
    switch (option)
    {
    case 1:
        if (selected == 0)
            return;
        selected--;
        print(selectables[selected + 1]);

        break;
    case 0:
        if (opt - 1 == selected)
            return;
        selected++;
        print(selectables[selected - 1]);

        break;
    default:
        break;
    }
    highlight(1, selectables[selected]);
    // mvprintw(0,0,"Options: %d\tSelected: %d", opt, selected);
}

int Window::get_selected()
{
    return selected;
}

WINDOW* Window::get_window(){
    return win;
}
