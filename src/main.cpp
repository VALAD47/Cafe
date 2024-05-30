//Made by VALAD47
#include "window.h"
#include <locale>

int main(int argc, char** argv){
    setlocale(LC_ALL, "");

    initscr();
    start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    Window main(26, 40);
    refresh();

    Text categories[][4] = {
        {   //Категорії
            {"1. Сніданок", 2, 3},
            {"2. Обід", 3, 3},
            {"3. Вечеря", 4, 3},
            {"4. Напої", 5, 3}
        },
        
        {   //Сніданок
            {"1. Смажені яйця", 2, 3},
            {"2. Бутерброди з ковбасою та сиром", 3, 3},
            {"3. Панкейки", 4, 3},
        },
        
        {   //Обід
            {"1. Борщ",2,3},
            {"2. Суп гороховий",3,3},
            {"3. Солянка",4,3}
        },

        {   //Вечеря
            {"1. Топчена картопля",2,3},
            {"2. Смажена картопля",3,3},
            {"3. Тушена картопля",4,3}
        },

        {   //Напої
            {"1. Кола",2,3},
            {"2. Вода",3,3},
            {"3. Горілка",4,3}
        }    
    };

    main.add_opt(categories[0], 4);
    main.refresh();
    noecho();
    keypad(stdscr, true);

    bool selected = false,
         reset    = false;
    int category  = -1,
        choice    = -1,
        count     = -1;

    while (true)
    {
        move(0,0);
        int i = getch();
        switch (i)
        {
        case KEY_DOWN:
        case KEY_RIGHT:
            main.select(0);
            break;

        case KEY_UP:
        case KEY_LEFT:
            main.select(1);
            break;

        case KEY_ENTER:
        case 10:{       //KEY_ENTER
            int i = main.get_selected();
            main.clear_opt();

            if(reset){
                if(i == 0){
                    category = -1;
                    choice = -1;
                    count = -1;
                    selected = false;
                    reset = false;
                    main.add_opt(categories[0], 4);
                    main.refresh();
                    break;
                }
                endwin();
                return 0;
            }

            if(!selected){
                selected = true;
                category = i;
                main.add_opt(categories[i+1], 3);
                break;
            }
            
            choice = i;

            echo();
            while(count<=0){
                main.clear_opt();
                main.print({"Введіть кількість порцій: ", 2, 3});
                main.refresh();
                mvwscanw(main.get_window(), 4, 3, "%d", &count);
            }
            noecho();
            main.clear_opt();
            main.print({"Ваш вибір:",2,3});
            mvwprintw(main.get_window(), 4, 3, "Категорія: %s", categories[0][category].str);
            mvwprintw(main.get_window(), 5, 3, "Страва: %s", categories[category+1][choice].str);
            mvwprintw(main.get_window(), 6, 3, "Кількість порцій: %d", count);

            Text yn[] = {{"Так", 12, 5}, {"Ні", 12, 15}};
            main.print({"Бажаєте зробити ще одне замовлення?", 10, 3});
            main.add_opt(yn, 2);
            reset = true;
            break;
        }

        case 'q':
        case 27:        //KEY_ESC
            endwin();
            return 0;
            break;

        default:
            break;
        }

        main.refresh();
    }
}