#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// ==============
// APP COMPONENTS
// ==============

app *init_app(int _halfdelay, char *title, border_style s, int margin)
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, true);
    halfdelay(_halfdelay);

    app *_app = malloc(sizeof(app));

    // Инициализация палитр
    if (has_colors() == false)
    {
        destroy_app(_app);
        printf("Your terminal does not support colors\n");
        exit(1);
    }
    start_color();

    // Инициализация палитр. Все цвета на чёрном фоне (кроме чёрного)
    /*
        1 - Красный     5 - фиолетовый
        2 - Зелёный     6 - Бирюзовый
        3 - Жёлтый      7 - белый
        4 - Синий

    */
    for (int color = 1; color <= COLOR_WHITE; color++)
    {
        init_pair(color, color, COLOR_BLACK);
    }

    _app->border = s;

    // Расчитываем положение окна и его размеры
    int max_x, max_y;
    int x, y;          // Положение основного окна
    int width, height; // Размер основного окна
    getmaxyx(stdscr, max_y, max_x);
    x = margin;
    y = margin + 2; // Отступ вверху
    width = max_x - (margin * 2);
    height = max_y - (margin * 2) - 2; // 2 строки под вывод сообщений

    // расчитываем всё необходимое для заголовка
    int title_lenght = strlen(title);

    int title_render_start;
    title_render_start = (width - title_lenght) / 2;
    app_title head = {title, title_render_start};
    _app->ttl = head;

    refresh();
    // -1 потому, что граница занимает один символ
    _app->width = width - 1;
    _app->height = height - 1;
    _app->wndw = newwin(height, width, y, x);
    wmove(_app->wndw, y, x);

    return _app;
}

void render_app(app *_app)
{
    border_style s = _app->border;
    wborder(_app->wndw, s.v, s.v, s.h, s.h,
            s.a, s.a, s.a, s.a);
    // Рендер заголовка
    // _app->ttl.render_start - 2 т.к 2 символа отводятся под декор
    wmove(_app->wndw, 0, _app->ttl.render_start - 2);
    wprintw(_app->wndw, "%c%s%c", _app->border.open_title,
            _app->ttl.title, _app->border.close_title);

    wrefresh(_app->wndw);
    refresh();
}

void destroy_app(app *_app)
{
    delwin(_app->wndw);
    free(_app);
    endwin();
}

void app_clear(app *_app)
{
    for (int x = 1; x < _app->width; x++)
    {
        for (int y = 1; y < _app->height; y++)
        {
            mvwprintw(_app->wndw, y, x, " ");
        }
    }
}

void app_print(int x, int y, unsigned short pair, char *message)
{
    static char *last_message = "";
    // Сохраняем старое положение курсора
    int old_cur_x, old_cur_y;
    getyx(stdscr, old_cur_y, old_cur_x);

    // Очищаем верхнюю строкчу
    for (int i = 1; i < strlen(last_message) + 2; i++)
        mvprintw(y, i, " ");

    attron(COLOR_PAIR(pair));
    mvprintw(y, x, "<%s>", message);
    last_message = message;
    attroff(COLOR_PAIR(pair));

    move(old_cur_y, old_cur_x);
}
