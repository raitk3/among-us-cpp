#include "tasks.h"

std::map<task, coords> crosses = std::map<task, coords> {
    std::pair<task, coords>(ALIGN, coords{328, 98}), //
    std::pair<task, coords>(ASTEROIDS, coords{323, 93}), //
    std::pair<task, coords>(CARD, coords{225, 167}), //
    std::pair<task, coords>(CENTER, coords{241, 182}), //
    std::pair<task, coords>(COURSE, coords{234, 121}), //
    std::pair<task, coords>(DISTRIBUTOR, coords{330, 95}), //
    std::pair<task, coords>(DIVERT, coords{324, 96}), //
    std::pair<task, coords>(DOWNLOAD, coords{235, 182}), //
    std::pair<task, coords>(FILTER, coords{330, 109}), //
    std::pair<task, coords>(FUEL, coords{426, 95}), //
    std::pair<task, coords>(MANIFOLDS, coords{326, 256}), //
    std::pair<task, coords>(REACTOR, coords{224, 167}), //
    std::pair<task, coords>(SAMPLE, coords{331, 94}), //
    std::pair<task, coords>(SCAN, coords{325, 109}), //
    std::pair<task, coords>(SHIELDS, coords{321, 102}), //
    std::pair<task, coords>(STABILIZE, coords{330, 96}), //
    std::pair<task, coords>(TRASH, coords{328, 95}), //
    std::pair<task, coords>(VENT, coords{323, 92}), //
    std::pair<task, coords>(WIRES, coords{322, 92}) //
};

bool check_cross(task task_to_check, data app_data)
{
    coords pixel = crosses.at(task_to_check);
    color pixel_color = get_pixel(correct_coords(pixel, app_data.origin, false));
    color pixel_color_n = get_pixel(correct_coords(coords{pixel.x - 7, pixel.y}, app_data.origin, false));
    color pixel_color_e = get_pixel(correct_coords(coords{pixel.x, pixel.y + 7}, app_data.origin, false));

    bool check = pixel_color == color{51, 51, 51};
    bool check_n = pixel_color_n == color{238, 238, 238};
    bool check_e = pixel_color_e == color{238, 238, 238};
    return check && check_n && check_e;
};

void detect_task(data app_data)
{
    start_task(app_data);
    for (std::pair<task, coords> cross: crosses)
    {
        if (check_cross(cross.first, app_data))
        {
            std::cout << "Detected " << cross.first << std::endl;
            do_task(app_data, cross.first, false);
            break;
        }
    }
};

void do_task(data app_data, task task_to_do)
{
    do_task(app_data, task_to_do, true);
}

void do_task(data app_data, task task_to_do, bool start)
{
    if (start) start_task(app_data);

    switch (task_to_do)
    {
    case ALIGN:
        align(app_data);
        break;
    case ASTEROIDS:
        asteroids(app_data);
        break;
    case CARD:
        card(app_data);
        break;
    case CENTER:
        center_click(app_data);
        break;
    case COURSE:
        course(app_data);
        break;
    case DISTRIBUTOR:
        distributor(app_data);
        break;
    case DIVERT:
        divert(app_data);
        break;
    case DOWNLOAD:
        download(app_data);
        break;
    case FILTER:
        filter(app_data);
        break;
    case FUEL:
        fuel(app_data);
        break;
    case MANIFOLDS:
        manifolds(app_data);
        break;
    case REACTOR:
        reactor(app_data);
        break;
    case SAMPLE:
        sample(app_data);
        break;
    case SHIELDS:
        shields(app_data);
        break;
    case STABILIZE:
        center_click(app_data);
        break;
    case TRASH:
        trash(app_data);
        break;
    case VENT:
        vent(app_data);
        break;
    case WIRES:
        wires(app_data);
        break;
    default:
        do_nothing();
    }
};

void start_task(data app_data)
{
    click( coords{1260,660}, app_data.origin, false);
    wait_seconds(0.5);
};

void do_nothing()
{
    std::cout << "Doing nothing lol" << std::endl;
};

void align(data app_data)
{
    std::cout << "Doing align" << std::endl;
    coords center = {884, 384};
    double align_parabola_constant = 0.0008;
    for (int y = -277; y < 277; y += 20) {
        int x = floor(align_parabola_constant * std::pow(y, 2));
        coords actual_coords = {center.x + x, center.y + y};
        color current_color = get_pixel(actual_coords, app_data.origin, false);
        if (current_color.r > 70 || current_color.g > 70 || current_color.b > 70)
        {
            drag(actual_coords, center, app_data.origin, false);
            break;
        }
        if (check_break()) break;
    }
};

// ToDo
void asteroids(data app_data)
{
    std::cout << "Doing asteroids" << std::endl;

    coords origin = coords{400, 100};
    int size = 500;
    int steps = 15;
    while (check_cross(ASTEROIDS, app_data))
    {
        for (int x = 0; x < steps; x++)
        {
            for (int y = 0; y < steps; y++)
            {
                coords coords_to_check =
                        correct_coords(coords{origin.x + (size / steps * x), origin.y +(size / steps * y)}, app_data.origin, false);

                if (check_break()) return;
                if (get_pixel(coords_to_check).g < 65) click(coords_to_check);
            }
        }
    }

};

void card(data app_data)
{
    std::cout << "Doing card swipe" << std::endl;
    click(coords{580, 580}, app_data.origin, false);
    wait_seconds(0.5);
    drag_slowly(coords{370, 300}, coords{1130, 300}, app_data.origin, false, 100);
};

void center_click(data app_data)
{
    std::cout << "Clicking the center of the screen" << std::endl;
    coords center = coords{app_data.display.x / 2, app_data.display.y / 2};
    click(center, app_data.origin, false);

};

// ToDo
void course(data app_data)
{
    std::cout << "Diverting course" << std::endl;
};

// ToDo
void distributor(data app_data)
{
    std::cout << "Calibrating distributor" << std::endl;

    bool done[] = {false, false, false};
    coords lights[] = {
        coords{875, 170},
        coords{875, 350},
        coords{875, 540}
    };

    coords buttons[] = {
        coords{875, 220},
        coords{875, 420},
        coords{875, 600}
    };

    while (check_cross(DISTRIBUTOR, app_data)) {
        for (int i = 0; i < 3; i++) {
            if (get_pixel(lights[i], app_data.origin, false) == color{0, 0, 0})
            {
                done[i] = false;
            }
        }
        if (done[2]) return;
        for (int i = 0; i < 3; i++)
        {
            if (!(get_pixel(lights[i], app_data.origin, false) == color{0, 0, 0} || done[i]))
            {
                click(buttons[i], app_data.origin, false);
                done[i] = true;
            }
        }
        wait_seconds(0.05);
    }
};

void divert(data app_data)
{
    std::cout << "Diverting power" << std::endl;
    int switches_x[] = {443, 510, 578, 648, 717, 784, 854, 923};
    int switches_y = 560;
    for (int x : switches_x)
    {
        if (get_pixel(coords{x, switches_y}, app_data.origin, false).r > 100)
        {
            drag(coords{x, switches_y}, coords{x, 440}, app_data.origin, false);
            break;
        }
    }
};

void download(data app_data)
{
    std::cout << "Dying on download again" << std::endl;
    click(coords{680, 470}, app_data.origin, false);
};

// ToDo
void filter(data app_data)
{
    std::cout << "Cleaning filter" << std::endl;
    int steps = 50;
    coords finish = coords{380, 380};

    while (check_cross(FILTER, app_data))
    {
        std::cout << "Cleaning" << std::endl;
        if (check_break()) break;
        for (int x = 496; x <= 996; x += steps)
        {
            if (check_break() || !check_cross(FILTER, app_data)) break;
            for (int y = 70; y <= 697; y += steps)
            {
                if (check_break() || !check_cross(FILTER, app_data)) break;
                if (get_pixel(correct_coords(coords{x, y}, app_data.origin, false)).b < 150)
                {
                    drag(coords{x, y}, finish, app_data.origin, false);
                }
            }
        }
    }
};

void fuel(data app_data)
{
    std::cout << "Fuelling" << std::endl;
    set_cursor(correct_coords(coords{1040, 620}, app_data.origin, false));
    mouse_button(1);
    while (!check_break() && get_pixel(correct_coords(coords{1075, 530}, app_data.origin, false)).g != 255) {
        continue;
    }
    mouse_button(0);

};

//ToDo: 2, 8
int get_manifolds_number(coords location)
{
    std::array<coords[7], 10> definitions
    {
        {{coords{14, 5}, coords{15, 15}, coords{16, 29}, coords{16, 38}, coords{6, 44}, coords{18, 44}, coords{30, 44}}, // 1
        {coords{7, 9}, coords{17, 3}, coords{25, 12}, coords{19, 30}, coords{11, 39}, coords{7, 45}, coords{25, 45}}, // 2
        {coords{10, 3}, coords{24, 9}, coords{19, 18}, coords{28, 22}, coords{29, 41}, coords{15, 46}, coords{3, 39}}, // 3
        {coords{3, 3}, coords{4, 26}, coords{19, 3}, coords{19, 23}, coords{20, 35}, coords{20, 46}, coords{29, 24}}, // 4
        {coords{10, 3}, coords{29, 2}, coords{19, 18}, coords{28, 22}, coords{29, 41}, coords{15, 46}, coords{3, 39}}, // 5
        {coords{19, 2}, coords{9, 11}, coords{3, 28}, coords{10, 44}, coords{28, 42}, coords{29, 26}, coords{14, 22}}, // 6
        {coords{5, 3}, coords{17, 5}, coords{30, 4}, coords{24, 15}, coords{16, 37}, coords{25, 11}, coords{17, 44}}, // 7
        {coords{17, 2}, coords{6, 10}, coords{27, 8}, coords{17, 21}, coords{3, 35}, coords{32, 36}, coords{16, 45}}, // 8
        {coords{19, 3}, coords{6, 13}, coords{17, 22}, coords{29, 9}, coords{29, 17}, coords{29, 32}, coords{29, 46}}, // 9
        {coords{9, 6}, coords{6, 44}, coords{16, 45}, coords{26, 2}, coords{20, 24}, coords{28, 46}, coords{33, 24}} // 10
        }
    };

    for (int i = 0; i < 10; i++)
    {
        bool success = true;
        for (int j = 0; j < 7; j++)
        {
            coords offset = definitions[i][j];
            coords pixel = coords{location.x + offset.x, location.y + offset.y};
            if (get_pixel(pixel).r > 70)
            {
                success = false;
                break;
            }
        }
        if (success) return i+1;
    }


    /*
     if image[(coords[0] + 12, coords[1] + 41)][0] < 70:
            return 1
        if image[(coords[0] + 13, coords[1] + 35)][0] < 70:
            return 2
        if image[(coords[0] + 19, coords[1] + 40)][0] < 70:
            return 4
        if image[(coords[0] + 7, coords[1] + 20)][0] < 70:
            return 5
        if image[(coords[0] + 26, coords[1] + 24)][0] < 70:
            return 6
        if image[(coords[0] + 15, coords[1] + 36)][0] < 70:
            return 7
        if image[(coords[0] + 23, coords[1] + 26)][0] < 70:
            return 8
        if image[(coords[0] + 26, coords[1] + 15)][0] < 70:
            return 9
        if image[(coords[0] + 10, coords[1] + 13)][0] < 70:
            return 10
        return 3
     */
    return 0;
};

void manifolds(data app_data)
{
    std::cout << "Unlocking manifolds" << std::endl;

    coords buttons[10];
    int values[10];
    int x_origin = 447;
    int y_origin = 304;

    int x_diff = 109;
    int y_diff = 111;

    if (!check_cross(MANIFOLDS, app_data)) return;

    for (int row = 0; row < 2; row++)
    {
        for (int column = 0; column < 5; column ++)
        {
            int cell = 5 * row + column % 5;
            coords current_coords = correct_coords(coords{x_origin + column*x_diff, y_origin + row*y_diff},
                                                   app_data.origin, false);
            buttons[cell] = current_coords;
            values[cell] = get_manifolds_number(current_coords);
        }
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            int value = values[5*i + j%5];
            std::string separator = (value==10) ? "|" : "| ";
            std::cout << separator << value;
        }
        std::cout << "|" << std::endl;

    }


    for (int i = 1; i < 11; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (values[j] == i)
            {
                click(buttons[j]);
                break;
            }
            if (values[j] == 0)
            {
                click(crosses.at(MANIFOLDS));
                wait_seconds(0.5);
                start_task(app_data);
                manifolds(app_data);
                return;
            }
        }
    }
    /*
     * x_diff = 109
     * y_diff = 111
     * image = self.get_screenshot()
     * squares = []
     * for y in range(2):
     *     y_coord = 304 + y*y_diff
     *     for x in range(5):
     *         x_coord = 447 + x*x_diff
     *         squares.append(self.get_square_value(
     *             (x_coord, y_coord, image)))
     * # print(squares)
     * for i in range(1, 11):
     *     square_to_press = squares.index(i)
     *     self.click((447+(square_to_press % 5)*x_diff,
     *                 304+(square_to_press // 5)*y_diff))
     */
};

void reactor(data app_data)
{
    std::cout << "Doing Simon says" << std::endl;

    int order[5] = {-1, -1, -1, -1, -1};
    coords lights[9];
    coords buttons[9];
    int j = 0;

    int previous_light = -1;
    int found_light = -1;

    for (int i = 0; i < 9; i++) {
        int y = 340 + floor(i / 3) * 90;
        int x1 = 370 + i%3 * 90;
        int x2 = 810 + i%3 * 90;
        lights[i] = coords{x1, y};
        buttons[i] = coords{x2, y};
    }

    while (check_cross(REACTOR, app_data))
    {
        while (check_cross(REACTOR, app_data)
               && (!
                   (get_pixel(buttons[0], app_data.origin, false) == color{189, 189, 189}
                    || get_pixel(buttons[0], app_data.origin, false) == color{214, 119, 119})
                   )
               )
        {
            found_light = -1;

            for (int i = 0; i < 9; i++) {
                if (!(get_pixel(lights[i], app_data.origin, false) == color{0, 0, 0}
                      || get_pixel(lights[i], app_data.origin, false) == color{95, 0, 0})) {
                    found_light = i;
                    if (found_light != previous_light) {
                        order[j] = i;
                        j++;
                    }
                    break;
                }
            }
            previous_light = found_light;
        }

        for(int num : order) {
            if (num != -1) {
                click(buttons[num], app_data.origin, false);
            }
        }

        for (int i = 0; i < 5; i++) order[i] = -1;
        j = 0;
    }


};

// ToDo
void sample(data app_data)
{
    std::cout << "Inspecting sample" << std::endl;
    wait_seconds(0.25);
    click(coords{900, 670}, app_data.origin, false);
    wait_seconds(61);
    for (int i = 0; i < 5; i++)
    {
        int x = 520 + 80 * i;
        int button_y = 600;
        int liquid_y = 420;
        if (get_pixel(correct_coords(coords{x, liquid_y}, app_data.origin, false))
                == color{246, 134, 134})
        {
            click(correct_coords(coords{x, button_y}, app_data.origin, false));
            break;
        }
    }
};

void shields(data app_data)
{
    std::cout << "Shiieelds" << std::endl;
    coords coordinates[] = {
        coords{682, 288},  // 241, 21, 25
        coords{602, 329},  //242, 21, 26
        coords{602, 450},  // 241, 22, 27
        coords{671, 482},  // 240, 22, 27
        coords{762, 450},  // 236, 30, 37
        coords{758, 319},  // 244, 17, 20
        coords{740, 318}  // 241, 21, 26
    };
    for (coords coord : coordinates)
    {
        if (get_pixel(coord, app_data.origin, false).g < 50)
        {
            click(coord, app_data.origin, false);
            wait_seconds(0.07);
        }
    }
};

void trash(data app_data)
{
    std::cout << "Doing trash" << std::endl;
    drag_and_hold(coords{900, 300}, coords{900, 500}, 1.5, app_data.origin, false);
};

// ToDo
void vent(data app_data)
{
    std::cout << "Cleaning vents" << std::endl;
    coords origin = correct_coords(coords{383, 116}, app_data.origin, false);
    coords size = {600, 530};
    int step = 50;
    for (int x = origin.x; x < (origin.x + size.x + 1); x += step)
    {
        for (int y = origin.y; y < (origin.y + size.y + 1); y += step)
        {
            if (check_cross(VENT, app_data) and not check_break()) click(coords{x, y});
            else return;
        }
    }
};

wire_color get_wire(color wire)
{
    if (wire.r > 250 && wire.g < 10 && wire.b < 1) return RED;
    else if (wire.r < 40 && wire.g < 40 && wire.b == 255) return BLUE;
    else if (wire.r > 250 && wire.g > 200 && wire.b < 10) return YELLOW;
    else if (wire.r > 250 && wire.b > 250 && wire.g < 10) return PURPLE;
    return UNDEFINED;
};

void wires(data app_data)
{
    std::cout << "Doing wires" << std::endl;

    for (int i = 0; i < 4; i++)
    {
        coords current = coords{400, 194+132 * i};
        wire_color current_wire = get_wire(get_pixel(current, app_data.origin, false));
        for (int j = 0; j < 4; j++) {
            coords pair = coords{940, 194+132*j};
            wire_color pair_wire = get_wire(get_pixel(pair, app_data.origin, false));
            if (current_wire == pair_wire) {
                drag(current, pair, app_data.origin, false);
                wait_seconds(0.1);
                break;
            }
        }
    }
};

void kill()
{
    write("q");
};
