#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// ==============
// APP COMPONENTS
// ==============

app *init_app(int _halfdelay, char *title, border_style s, int indent)
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, true);
    halfdelay(_halfdelay);

    app *_app = malloc(sizeof(app));

    if (has_colors() == false)
    {
        destroy_app(_app);
        printf("Your terminal does not support colors\n");
        exit(1);
    }
    start_color();

    // Initialized colors: (thet are all on a black bg, without black color)
    /*
        1 - Red         5 - Magenta
        2 - Green       6 - Сyan
        3 - Yellow      7 - White
        4 - Blue

    */
    for (int color = 1; color <= COLOR_WHITE; color++)
    {
        init_pair(color, color, COLOR_BLACK);
    }

    _app->border = s;

    // Calculating the window size and position
    int max_x, max_y;
    int x, y;
    int width, height;
    getmaxyx(stdscr, max_y, max_x);
    x = indent;
    y = indent + 2; // Upper indentation
    width = max_x - (indent * 2);
    height = max_y - (indent * 2) - 2; // 2 lines for messages

    // Creating a window title
    int title_lenght = strlen(title);

    int title_render_start;
    title_render_start = (width - title_lenght) / 2;
    app_title head = {title, title_render_start};
    _app->ttl = head;

    refresh();
    // -1 because the border char
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
    // Title rendering
    // _app->ttl.render_start - 2 because 2 char for opening-closing chars
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
    int old_cur_x, old_cur_y;
    getyx(stdscr, old_cur_y, old_cur_x);

    for (int i = 1; i < strlen(last_message) + 2; i++)
        mvprintw(y, i, " ");

    attron(COLOR_PAIR(pair));
    mvprintw(y, x, "<%s>", message);
    last_message = message; // Saves message for correct cleaning in the future
    attroff(COLOR_PAIR(pair));

    move(old_cur_y, old_cur_x);
}
