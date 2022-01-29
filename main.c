#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "src/interface/interface.h"
#include "src/snake/snake.h"

const border_style DEFAULT_BORDER = {0, 0, 0, 91, 93};

int main(int argc, char **argv)
{
    // Установка сида
    int seed = time(NULL);
    if (argc >= 2)
    {
        seed = atoi(argv[1]);
    }

    app *application = init_app(1, "Snake", DEFAULT_BORDER, 1);
    rect snake_head = {1, 1, COLOR_GREEN, '#'};
    rect apple = {0, 0, COLOR_RED, '@'};
    snake *s = create_snake(application->wndw, snake_head);
    srand(seed);
    int key;
    unsigned score = 0;
    bool pause = false;
    bool gameover = false;

    // Вывод сида
    char buffer[18];
    sprintf(buffer, "Seed: %lld", seed);
    int x_pos = getmaxx(stdscr) - (strlen(buffer) + 5); // отступ от границы 5
    app_print(x_pos, 0, COLOR_MAGENTA, buffer);

    app_print(0, 0, COLOR_GREEN, "Q - quit, P - pause");
    replace_apple(&apple, application->width, application->height);

    while (true)
    {
        key = getch();

        // Условие выхода
        if (key == 'q')
            break;

        // Пауза
        if (key == 'p' && !gameover)
        {
            if (pause)
            {
                app_print(0, 0, COLOR_GREEN, "Q - quit, P - pause");
                pause = false;
            }
            else
            {
                app_print(0, 0, COLOR_YELLOW, "Paused! [Press P to continue]");
                pause = true;
            }
        }

        // Конец игры
        if (gameover)
        {
            pause = true;
            app_print(0, 0, COLOR_RED, "Game Over ;-; [Press Q to quit]");
        }

        // Обновление змейки
        if (!pause)
            snake_update(s, key);

        // Подбор яблок
        if (check_apple_collide(s, apple))
        {
            replace_apple(&apple, application->width, application->height);
            char buffer[13];
            score += 2;
            sprintf(buffer, "Score: %d", score);
            app_print(0, 1, COLOR_BLUE, buffer);
        }

        check_wall_collision(s);
        if (tail_collide(*s))
            gameover = true;

        // Рендер
        app_clear(application);
        draw_rect(application->wndw, apple); // Рендер яблока
        snake_draw(s);
        render_app(application);
    }
    destroy_app(application);

    return 0;
}
