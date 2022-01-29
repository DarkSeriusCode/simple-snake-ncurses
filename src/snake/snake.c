#include <stdlib.h>
#include <time.h>
#include "snake.h"

// ===============
// ФУНКЦИИ ЗМЕЙКИ
// ===============

snake *create_snake(WINDOW *wndw, rect snake_part)
{
    snake *sn = malloc(sizeof(snake));
    int x, y;
    getmaxyx(wndw, y, x);

    sn->wndw = wndw;
    sn->head = snake_part;
    sn->side = RIGHT;
    sn->tail = create_queue(x * y);
    sn->lenght = 4;
    return sn;
}

void snake_update(snake *sn, int key)
{
    update_snake_tail(sn);

    switch (key)
    {
    case KEY_UP:
        if (sn->side == LEFT || sn->side == RIGHT)
            sn->side = UP;
        break;

    case KEY_DOWN:
        if (sn->side == LEFT || sn->side == RIGHT)
            sn->side = DOWN;
        break;

    case KEY_LEFT:
        if (sn->side == UP || sn->side == DOWN)
            sn->side = LEFT;
        break;

    case KEY_RIGHT:
        if (sn->side == UP || sn->side == DOWN)
            sn->side = RIGHT;
        break;
    }

    switch (sn->side)
    {
    case RIGHT:
        sn->head.x++;
        break;

    case LEFT:
        sn->head.x--;
        break;

    case UP:
        sn->head.y--;
        break;

    case DOWN:
        sn->head.y++;
        break;
    }
}

void update_snake_tail(snake *sn)
{
    while (sn->tail->put_index < sn->lenght)
    {
        queue_add(sn->tail, sn->head);
    }

    if (sn->tail->put_index >= sn->lenght)
        queue_get(sn->tail);
}

void check_wall_collision(snake *sn)
{
    int width, height;
    getmaxyx(sn->wndw, height, width);
    width--;
    height--;

    if (sn->head.x >= width)
    {
        sn->head.x = 0;
        sn->side = RIGHT;
    }
    else if (sn->head.x <= 0)
    {
        sn->head.x = width;
        sn->side = LEFT;
    }
    else if (sn->head.y >= height)
    {
        sn->head.y = 0;
        sn->side = DOWN;
    }
    else if (sn->head.y <= 0)
    {
        sn->head.y = height;
        sn->side = UP;
    }
}

bool tail_collide(snake sn)
{
    for (int i = 0; i < sn.tail->size; i++)
    {
        if (sn.head.x == sn.tail->_queue[i].x &&
            sn.head.y == sn.tail->_queue[i].y)
            return true;
    }
    return false;
}

void snake_draw(snake *s)
{
    draw_rect(s->wndw, s->head);
    for (int i = 0; i < s->lenght; i++)
    {
        draw_rect(s->wndw, s->tail->_queue[i]);
    }
}

// ===============
// ФУНКЦИИ ОЧЕРЕДИ
// ===============

rect_queue *create_queue(const int max_size)
{
    rect_queue *q = malloc(sizeof(rect_queue));
    q->_queue = malloc(sizeof(rect) * max_size);
    q->max_size = max_size;
    q->put_index = 0;
    q->size = 0;
    return q;
}

short queue_add(rect_queue *q, rect item)
{
    if (q->put_index > q->max_size)
        return -1;
    else
    {
        q->_queue[q->put_index++] = item;
        q->size++;
    }
}

rect queue_get(rect_queue *q)
{
    rect item = {-1, -1, -1, -1};

    // ПОЖАЛУЙСТА, НЕ МЕНЯЙТЕ УСЛОВИЕ! ОНО ВООБЩЕ НЕ ДОЛЖНО РАБОТАТЬ
    if (q->put_index <= 0)
        return item;

    item = q->_queue[0];

    // *Смещение элементов очереди
    for (int i = 0; i < q->put_index; ++i)
    {
        q->_queue[i] = q->_queue[i + 1];
    }
    q->put_index--;
    q->size--;
    return item;
}

// ===============
// ФУНКЦИИ ЯБЛОК
// ===============

void replace_apple(rect *apple, int width, int height)
{
    apple->x = 1 + rand() % (width - 2);
    apple->y = 1 + rand() % (height - 2);
}

bool check_apple_collide(snake *s, rect apple)
{
    if (s->head.x == apple.x && s->head.y == apple.y)
    {
        s->lenght += 2;
        return true;
    }
    return false;
}

// ===============
// ОБЩИЕ ФУНКЦИИ
// ===============

void draw_rect(WINDOW *wndw, rect r)
{
    wmove(wndw, r.y, r.x);
    wattron(wndw, COLOR_PAIR(r.pair_number));
    wprintw(wndw, "%c", r.c);
    wattroff(wndw, COLOR_PAIR(r.pair_number));
}
