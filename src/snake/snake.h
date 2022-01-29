#ifndef SNAKE_H
#define SNAKE_H

#include <ncurses.h>

// Просто квадрат на поле из которых состоит змейка
typedef struct
{
    int x, y;             // Координаты
    unsigned pair_number; // Номер цветовой палитры
    char c;               // Символ квадрата
} rect;

// Очередь rect
typedef struct
{
    rect *_queue;  // Указатель на массив
    int put_index; // Индекс, по которому нужно вставить следующий элемент
    int size;      // Размер очереди
    int max_size;  // максимальный размер очереди
} rect_queue;

// Стороны движения
typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT
} move_side;

// Сама змейка
typedef struct
{
    rect head;
    move_side side;
    WINDOW *wndw;
    rect_queue *tail;
    unsigned short lenght;
} snake;

// ===============
// ФУНКЦИИ ЗМЕЙКИ
// ===============

// Функция создаёт змейку
snake *create_snake(WINDOW *wndw, rect snake_part);

// Обновление змейки
void snake_update(snake *sn, int key);

// Обновляет хвост змейки
void update_snake_tail(snake *sn);

// Если змейка касается какой-то стороны,
//то перемещает на противополеженную сторону
void check_wall_collision(snake *sn);

// Проверяет столкновение головы и хвоста змейки
bool tail_collide(snake sn);

// Отрисовка змейки
void snake_draw(snake *s);

// ===============
// ФУНКЦИИ ОЧЕРЕДИ
// ===============

// Создаёт очередь rect
rect_queue *create_queue(const int max_size);

// Добавляет в очередь элемент
short queue_add(rect_queue *q, rect item);

// Получает элемент из очереди
rect queue_get(rect_queue *q);

// ===============
// ФУНКЦИИ ЯБЛОК
// ===============

// Перемещает яблоко на поле с шириной и высотой width и height
void replace_apple(rect *apple, int width, int height);

// Увеличивает размер змейки при столкновении с яблоком
bool check_apple_collide(snake *s, rect apple);

// ===============
// ОБЩИЕ ФУНКЦИИ
// ===============

// Отрисовка rect в окне
void draw_rect(WINDOW *wndw, rect r);

#endif // SNAKE_H
