#ifndef TASKS_H
#define TASKS_H

#include <map>
#include "data.h"

enum wire_color {
    UNDEFINED = 0,
    RED = 1,
    BLUE = 2,
    YELLOW = 3,
    PURPLE = 4

};

enum task {
    ALIGN,
    ASTEROIDS,
    CARD,
    CENTER,
    COURSE,
    DISTRIBUTOR,
    DIVERT,
    DOWNLOAD,
    FILTER,
    FUEL,
    MANIFOLDS,
    REACTOR,
    SAMPLE,
    SCAN,
    SHIELDS,
    STABILIZE,
    TRASH,
    VENT,
    WIRES
};

bool check_break();

bool check_cross(task task_to_check, data app_data);

void start_task(data app_data);

void detect_task(data app_data);

void do_task(data app_data, task task_to_do);

void do_task(data app_data, task task_to_do, bool start);

void do_nothing();

void align(data app_data);

void asteroids(data app_data);

void card(data app_data);

void center_click(data app_data);

void course(data app_data);

void distributor(data app_data);

void divert(data app_data);

void download(data app_data);

void filter(data app_data);

void fuel(data app_data);

int get_manifolds_number(coords location);

void manifolds(data app_data);

void reactor(data app_data);

void sample(data app_data);

void shields(data app_data);

void trash(data app_data);

void vent(data app_data);

wire_color get_wire(color wire);

void wires(data app_data);

void kill();

#endif // TASKS_H
