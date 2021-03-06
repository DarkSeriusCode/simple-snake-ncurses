#include <stdlib.h>
#include <time.h>
#include "snake.h"

// ===============
// SNAKE FUNCTIONS
// ===============

snake *create_snake(WINDOW *wndw, point snake_part)
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

bool check_tail_collide(snake sn)
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
    draw_point(s->wndw, s->head);
    for (int i = 0; i < s->lenght; i++)
    {
        draw_point(s->wndw, s->tail->_queue[i]);
    }
}

// ===============
// QUEUE FUNCTIONS
// ===============

point_queue *create_queue(const int max_size)
{
    point_queue *q = malloc(sizeof(point_queue));
    q->_queue = malloc(sizeof(point) * max_size);
    q->max_size = max_size;
    q->put_index = 0;
    q->size = 0;
    return q;
}

short queue_add(point_queue *q, point item)
{
    if (q->put_index > q->max_size)
        return -1;
    else
    {
        q->_queue[q->put_index++] = item;
        q->size++;
    }
}

point queue_get(point_queue *q)
{
    point item = {-1, -1, -1, -1};

    if (q->put_index <= 0)
        return item;

    item = q->_queue[0];

    // Shifting queue elements
    for (int i = 0; i < q->put_index; ++i)
    {
        q->_queue[i] = q->_queue[i + 1];
    }
    q->put_index--;
    q->size--;
    return item;
}

// ===============
// APPLE FUNCTIONS
// ===============

void replace_apple(point *apple, int width, int height)
{
    apple->x = 1 + rand() % (width - 2);
    apple->y = 1 + rand() % (height - 2);
}

bool check_apple_collide(snake *s, point apple)
{
    if (s->head.x == apple.x && s->head.y == apple.y)
    {
        s->lenght += 2;
        return true;
    }
    return false;
}

// ===============
// OTHER FUNCTIONS
// ===============

void draw_point(WINDOW *wndw, point r)
{
    wmove(wndw, r.y, r.x);
    wattron(wndw, COLOR_PAIR(r.pair_number));
    wprintw(wndw, "%c", r.c);
    wattroff(wndw, COLOR_PAIR(r.pair_number));
}
