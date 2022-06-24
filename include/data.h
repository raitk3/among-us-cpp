#pragma once
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

#ifdef __linux__
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

#elif _WIN32
#include <windows.h>
#include <wingdi.h>

#endif


struct color
{
  int r;
  int g;
  int b;

  std::string toString() {
    return "r: " + std::to_string(r)
        + ", g: " + std::to_string(g)
        + ", b: " + std::to_string(b);
  }
};

bool operator==(const color& lhs, const color& rhs);

struct coords {
  int x;
  int y;

  std::string toString() {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
  }
};

struct sentence {
  std::string name;
  std::string sentences;
};

struct data {
  bool kill_status = false;

  coords origin = {0, 0};
  coords display = {1366, 768};

  coords rejoinCross = {330, 320};
  coords rejoinBox1 = {680, 650};
  coords rejoinBox2 = {680, 210};
  coords rejoinArrow = {890, 210};

  double chatCooldown = 3.0;
  double enterCooldown = 0.2;

  std::string code = "";

  std::vector<sentence> sentences = {
    {"Skeld", "These are for Skeld"},
    {"Mira", "These are for Mira"},
    {"Polus", "These are for Polus"},
    {"AirShip", "These are for Polus"},
  };

};

data readData();

color getPixel(coords pixel);

color getPixel(coords pixel, coords origin, bool subtract = false);

coords correctCoords(coords coordinates, coords origin, bool subtract = false);

bool checkBreak();

void writeFile(data appData);

void waitSeconds(double seconds);

void setCursor(int x, int y);

void setCursor(coords coordinates);

void click(coords coordinates);

void click(coords coordinates, coords origin, bool subtract = false);

void mouseButton(bool down);

void drag(coords from, coords to);

void drag(coords from, coords to, coords origin, bool subtract = false);

void dragAndHold(coords from, coords to, double secondsToHold);

void dragAndHold(coords from, coords to, double secondsToHold, coords origin, bool subtract = false);

void dragSlowly(coords from, coords to, int steps);

void dragSlowly(coords from, coords to, coords origin, int steps, bool subtract = false);

void joinLobby(data appData);

void sendText(std::vector<std::string> sentences);

void pressEnter();

void write(std::string text);

void sendSystemCommand(std::string command);
#endif // DATA_H
