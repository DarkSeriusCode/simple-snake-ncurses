#ifndef INTERFACE_H
#define INTERFACE_H

#include <ncurses.h>

// =====================
// КОМПОНЕНТЫ ПРИЛОЖЕНИЯ
// =====================

// Стиль границы окна
typedef struct
{
    char v, h, a;     // Символы по вертикали, горизонтали, в углах
    char open_title;  // Открывающий символ названия окна
    char close_title; // Закрывающий символ названия окна
} border_style;

// Заголовок окна
typedef struct
{
    char *title;      // Текст заголовка
    int render_start; // Точка начала рендера текста
} app_title;

// Приложение (ncurses окно)
typedef struct
{
    WINDOW *wndw;        // Основное окно программы
    int x, y;            // Положение окна
    int width, height;   // Рамеры окна
    app_title ttl;       // Название окна
    border_style border; // Стиль границы окна
} app;

// Инициализирует app, добовляет обводку и заголовок
app *init_app(int _halfdelay, char *title, border_style s, int margin);

// Рендерит приложение
void render_app(app *_app);

// Уничтожает ncurses приложение
void destroy_app(app *_app);

// Очищает область отображения окна
void app_clear(app *_app);

// Выводит сообщение в левый верхний угол
void app_print(int x, int y, unsigned short pair, char *message);

#endif // INTERFACE_H