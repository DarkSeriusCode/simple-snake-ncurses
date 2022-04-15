#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "src/interface.h"
#include "src/snake.h"

const border_style DEFAULT_BORDER = {0, 0, 0, 91, 93};

int main(int argc, char **argv)
{
    // Setting seed
    int seed = time(NULL);
    if (argc >= 2)
    {
        seed = atoi(argv[1]);
    }

    app *application = init_app(1, "Snake", DEFAULT_BORDER, 1);
    point snake_head = {1, 1, COLOR_GREEN, '#'};
    point apple = {0, 0, COLOR_RED, '@'};
    snake *s = create_snake(application->wndw, snake_head);
    srand(seed);

    int key;
    unsigned score = 0;
    bool pause = false;
    bool gameover = false;

    // Seed displaying
    char buffer[18];
    sprintf(buffer, "Seed: %d", seed);
    int x_pos = getmaxx(stdscr) - (strlen(buffer) + 5); // margin from border 5
    app_print(x_pos, 0, COLOR_MAGENTA, buffer);

    app_print(0, 0, COLOR_GREEN, "Q - quit, P - pause");
    replace_apple(&apple, application->width, application->height);

    while (true)
    {
        key = getch();

        // Exit condition
        if (key == 'q')
            break;

        // Pause
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

        // GameOver
        if (gameover)
        {
            pause = true;
            app_print(0, 0, COLOR_RED, "Game Over ;-; [Press Q to quit]");
        }

        // Snake update
        if (!pause)
            snake_update(s, key);

        // Apple eating
        if (check_apple_collide(s, apple))
        {
            replace_apple(&apple, application->width, application->height);
            char buffer[13];
            score += 2;
            sprintf(buffer, "Score: %d", score);
            app_print(0, 1, COLOR_BLUE, buffer);
        }

        check_wall_collision(s);
        if (check_tail_collide(*s))
            gameover = true;

        // Render
        app_clear(application);
        draw_point(application->wndw, apple); // Apple render
        snake_draw(s);
        render_app(application);
    }
    destroy_app(application);

    return 0;
}
