#ifndef SNAKE_H
#define SNAKE_H

#include <ncurses.h>

// Just a point in the window
typedef struct
{
    int x, y;             // A point's position
    unsigned pair_number; // Color palette number
    char c;               // A char of the point
} point;

// Point queue
typedef struct
{
    point *_queue;
    int put_index;
    int size;
    int max_size;
} point_queue;

// Movement sides
typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT
} move_side;

// Snake
typedef struct
{
    point head;
    move_side side;
    WINDOW *wndw;
    point_queue *tail;
    unsigned short lenght;
} snake;

// ===============
// SNAKE FUNCTIONS
// ===============

// Creates a new snake
snake *create_snake(WINDOW *wndw, point snake_part);

// Snake update
void snake_update(snake *sn, int key);

// Обновляет хвост змейки
void update_snake_tail(snake *sn);

// If the snake collide with some side, then it will be move to opposite side
void check_wall_collision(snake *sn);

// Checks if the snake has collided with its tail
bool check_tail_collide(snake sn);

// Snake render
void snake_draw(snake *s);

// ===============
// QUEUE FUNCTIONS
// ===============

// Creates a new point queue
point_queue *create_queue(const int max_size);

// Adds a new item to the end of the queue
short queue_add(point_queue *q, point item);

// Returns item from the queue
point queue_get(point_queue *q);

// ===============
// APPLE FUNCTIONS
// ===============

// Moves apple to a random position in an area with size (width, height)
void replace_apple(point *apple, int width, int height);

// Increases the snake size when it collide with an apple
bool check_apple_collide(snake *s, point apple);

// ===============
// OTHER FUNCTIONS
// ===============

// Draws a point in the window
void draw_point(WINDOW *wndw, point r);

#endif // SNAKE_H
