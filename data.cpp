#include "data.h"


Display *d = XOpenDisplay((char *) NULL);

bool operator==(const color& lhs, const color& rhs)
{
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
}

data read_data()
{
    data new_data = data{};
    std::vector<sentence> sentences;

    return new_data;
};

void write_file(data app_data)
{
};

color get_pixel(coords pixel)
{
    XColor c;
    XImage *image;
    image = XGetImage (d, XRootWindow (d, XDefaultScreen (d)), pixel.x, pixel.y, 1, 1, AllPlanes, XYPixmap);
    c.pixel = XGetPixel (image, 0, 0);
    XFree (image);
    XQueryColor (d, XDefaultColormap(d, XDefaultScreen (d)), &c);
    return color{c.red/256, c.green/256, c.blue/256};
}

color get_pixel(coords pixel, coords origin, bool subtract)
{
    return get_pixel(correct_coords(pixel, origin, subtract));
};

coords correct_coords(coords coordinates, coords origin, bool subtract)
{
    if (subtract) return coords{coordinates.x - origin.x, coordinates.y - origin.y};
    return coords{coordinates.x + origin.x, coordinates.y + origin.y};
}

bool check_break()
{
    return false;
};

void wait_seconds(double seconds)
{
    std::cout << "Waiting " << seconds << " seconds" << std::endl;
    double microseconds = seconds * std::pow(10, 6);
    usleep(microseconds);
};

void set_cursor(int x, int y)
{
    set_cursor(coords{x, y});
};

void set_cursor(coords coordinates)
{
    QCursor::setPos(coordinates.x, coordinates.y);
}

void click(coords coordinates)
{
    std::cout << "Clicking on (" << coordinates.x << ", " << coordinates.y << ")" << std::endl;
    set_cursor(coordinates);
    //system("xdotool click 1");
    XTestFakeButtonEvent(d, 1, True, CurrentTime);
    XTestFakeButtonEvent(d, 1, False, CurrentTime);
    XFlush(d);
    wait_seconds(0.1);
}

void click(coords coordinates, coords origin, bool subtract)
{
    click(correct_coords(coordinates, origin, subtract));
}

void mouse_button(bool down)
{
    XTestFakeButtonEvent(d, 1, down, CurrentTime);
    XFlush(d);
}

void drag(coords from, coords to)
{
    std::cout << "Dragging from (" << from.x << ", " << from.y << ")"
              << " to (" << to.x << ", " << to.y << ")" << std::endl;
    set_cursor(from);
    mouse_button(1);
    wait_seconds(0.1);

    set_cursor(to);
    wait_seconds(0.11);
    mouse_button(0);

}

void drag(coords from, coords to, coords origin, bool subtract)
{
    drag(correct_coords(from, origin, subtract), correct_coords(to, origin, subtract));
}

void drag_and_hold(coords from, coords to, double seconds_to_hold)
{
    set_cursor(from);
    mouse_button(1);
    wait_seconds(0.1);

    set_cursor(to);
    wait_seconds(0.11 + seconds_to_hold);
    mouse_button(0);
};

void drag_and_hold(coords from, coords to, double seconds_to_hold, coords origin, bool subtract)
{
    drag_and_hold(correct_coords(from, origin, subtract), correct_coords(to, origin, subtract), seconds_to_hold);
};

void drag_slowly(coords from, coords to, int steps)
{
    int x_diff = to.x - from.x;
    int y_diff = to.y - from.y;

    set_cursor(from);
    mouse_button(1);

    wait_seconds(0.1);

    for (int i = 0; i < steps; i++) {
        set_cursor(from.x + x_diff / steps * i, from.y + y_diff / steps * i);
        wait_seconds(0.005);
    }
    set_cursor(to);
    mouse_button(0);
}

void drag_slowly(coords from, coords to, coords origin, bool subtract, int steps)
{
    drag_slowly(correct_coords(from, origin, subtract), correct_coords(to, origin, subtract), steps);
}

void join_lobby(data app_data)
{
    std::cout << "Joining lobby " << app_data.code << std::endl;

    click(coords{app_data.origin.x + app_data.rejoin_cross.x, app_data.origin.y + app_data.rejoin_cross.y});
    wait_seconds(0.1);
    click(coords{app_data.origin.x + app_data.rejoin_box_1.x, app_data.origin.y + app_data.rejoin_box_1.y});
    wait_seconds(0.1);
    click(coords{app_data.origin.x + app_data.rejoin_box_2.x, app_data.origin.y + app_data.rejoin_box_2.y});
    wait_seconds(0.1);
    write(app_data.code);
    wait_seconds(1);
    click(coords{app_data.origin.x + app_data.rejoin_arrow.x, app_data.origin.y + app_data.rejoin_arrow.y});
}

void write(std::string text)
{
    std::cout << text << std::endl;
    std::string command = "xdotool type ";
    command += "'" + text + "'";
    send_system_command(command);
}

void press_enter()
{
    system("xdotool key Return");
};

void send_text(std::vector<std::string> sentences)
{
    wait_seconds(3);
    for (std::string sentence : sentences)
    {
        write(sentence);
        wait_seconds(1);
        press_enter();
        wait_seconds(2);

    }
};

void send_system_command(std::string command)
{
    int length = command.size();
    char passable[length+1];
    std::strcpy(passable, command.c_str());
    system(passable);
};
