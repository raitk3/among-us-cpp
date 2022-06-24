#ifndef TASKS_H
#define TASKS_H

#include <map>
#include "include/data.h"

enum wireColor {
  UNDEFINED,
  RED,
  BLUE,
  YELLOW,
  PURPLE
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

const std::map<task, std::string> taskStrings {
  {ALIGN, "align"},
  {ASTEROIDS, "asteroids"},
  {CARD, "card"},
  {CENTER, "center"},
  {COURSE, "course"},
  {DISTRIBUTOR, "distributor"},
  {DIVERT, "divert"},
  {DOWNLOAD, "download"},
  {FILTER, "filter"},
  {FUEL, "fuel"},
  {MANIFOLDS, "manifolds"},
  {REACTOR, "reactor"},
  {SAMPLE, "sample"},
  {SCAN, "scan"},
  {SHIELDS, "shields"},
  {STABILIZE, "stabilize"},
  {TRASH, "trash"},
  {VENT, "vent"},
  {WIRES, "wires"}
};

bool checkBreak();

bool checkCross(task taskToCheck, data appData);

void startTask(data appData);

void detectTask(data appData);

void doTask(data appData, task taskToDo, bool start = true);

void doNothing();

void align(data appData);

void asteroids(data appData);

void card(data appData);

void centerClick(data appData);

void course(data appData);

void distributor(data appData);

void divert(data appData);

void download(data appData);

void filter(data appData);

void fuel(data appData);

int getManifoldsNumber(coords location);

void manifolds(data appData);

void reactor(data appData);

void sample(data appData);

void shields(data appData);

void trash(data appData);

void vent(data appData);

wireColor getWire(color wire);

void wires(data appData);

void kill();

#endif // TASKS_H
