#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <QCursor>
#include <vector>
#include <math.h>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>
#undef Bool
#undef CursorShape
#undef Expose
#undef KeyPress
#undef KeyRelease
#undef FocusIn
#undef FocusOut
#undef FontChange
#undef None
#undef Status
#undef Unsorted



struct color
{
    int r;
    int g;
    int b;
};

bool operator==(const color& lhs, const color& rhs);

struct coords
{
    int x;
    int y;
};

struct sentence
{
    std::string name;
    std::string sentences;
};

struct data
{
    std::string code = "";
    coords origin = {0, 625};
    coords display = {1366, 768};

    coords rejoin_cross = {330, 320};
    coords rejoin_box_1 = {680, 650};
    coords rejoin_box_2 = {680, 210};
    coords rejoin_arrow = {890, 210};

    double chat_cooldown = 3.0;
    double enter_cooldown = 0.2;

    bool kill_status = false;

    std::vector<sentence> sentences = {
        sentence{"Skeld", "These are for Skeld"},
        sentence{"Mira", "These are for Mira"},
        sentence{"Polus", "These are for Polus"},
        sentence{"AirShip", "These are for Polus"},
    };

};

data read_data();

color get_pixel(coords pixel);

color get_pixel(coords pixel, coords origin, bool subtract);

coords correct_coords(coords coordinates, coords origin, bool subtract);

bool check_break();
void write_file(data app_data);

void wait_seconds(double seconds);

void set_cursor(int x, int y);

void set_cursor(coords coordinates);

void click(coords coordinates);

void click(coords coordinates, coords origin, bool subtract);

void mouse_button(bool down);

void drag(coords from, coords to);

void drag(coords from, coords to, coords origin, bool subtract);

void drag_and_hold(coords from, coords to, double seconds_to_hold);

void drag_and_hold(coords from, coords to, double seconds_to_hold, coords origin, bool subtract);

void drag_slowly(coords from, coords to, int steps);

void drag_slowly(coords from, coords to, coords origin, bool subtract, int steps);

void join_lobby(data app_data);

void send_text(std::vector<std::string> sentences);

void press_enter();

void write(std::string text);

void send_system_command(std::string command);
#endif // DATA_H
