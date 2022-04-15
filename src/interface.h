#ifndef INTERFACE_H
#define INTERFACE_H

#include <ncurses.h>

// =====================
// APPLICATON COMPONENTS
// =====================

// Style of a window border
typedef struct
{
    char v, h, a;     // Vertical chars, horizontal chars and chars in corners
    char open_title;  // Opening char of the window title
    char close_title; // Closing char of the window title
} border_style;

// The window title
typedef struct
{
    char *title;      // Title text
    int render_start; // The starting point of text rendering
} app_title;

// App (ncurses window)
typedef struct
{
    WINDOW *wndw;        // Main program's window
    int x, y;            // The position of the window
    int width, height;   // The size of the window
    app_title ttl;       // The title of the window
    border_style border; // Style of the window border
} app;

// Initializes app with input delay, title, border etc.
app *init_app(int _halfdelay, char *title, border_style s, int indent);

// Renders the app
void render_app(app *_app);

// Destroys the app
void destroy_app(app *_app);

// Cleans the app
void app_clear(app *_app);

// Prints a message in the upper-left corner
void app_print(int x, int y, unsigned short pair, char *message);

#endif // INTERFACE_H