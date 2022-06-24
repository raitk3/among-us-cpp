#include "include/data.h"

#ifdef __linux__
Display *d = XOpenDisplay((char *) NULL);
#elif _WIN32
#include <winuser.h>
#endif

bool operator==(const color& lhs, const color& rhs) {
  return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
}

data readData() {
  data new_data = data{};
  std::vector<sentence> sentences;
  return new_data;
};

void writeFile(data appData) {
};

color getPixel(coords pixel) {
  #ifdef __linux__
  XColor c;
  XImage *image;
  image = XGetImage (d, XRootWindow (d, XDefaultScreen (d)), pixel.x, pixel.y, 1, 1, AllPlanes, XYPixmap);
  c.pixel = XGetPixel (image, 0, 0);
  XFree (image);
  XQueryColor (d, XDefaultColormap(d, XDefaultScreen (d)), &c);
  return color{c.red/256, c.green/256, c.blue/256};

  #elif _WIN32
  HDC dc = GetDC(NULL);
  COLORREF col = GetPixel(dc, pixel.x, pixel.y);
  return color{GetRValue(col), GetGValue(col), GetBValue(col)};

  #endif
  return color{0, 0, 0};
}

color getPixel(coords pixel, coords origin, bool subtract) {
  return getPixel(correctCoords(pixel, origin, subtract));
};

coords correctCoords(coords coordinates, coords origin, bool subtract) {
  if (subtract) {
    return coords{coordinates.x - origin.x, coordinates.y - origin.y};
  }
  return coords{coordinates.x + origin.x, coordinates.y + origin.y};
}

bool checkBreak() {
  #ifdef _WIN32
  if (GetKeyState(VK_SHIFT) & 0x8000) {
    std::cout << "BREEEAAAKKK!!!" << std::endl;
    return true;
  };
  #endif
  return false;
};

void waitSeconds(double seconds) {
  std::cout << "Waiting " << seconds << " seconds" << std::endl;
  double microseconds = seconds * std::pow(10, 6);
  usleep(microseconds);
};

void setCursor(int x, int y) {
  setCursor(coords{x, y});
};

void setCursor(coords coordinates) {
  QCursor::setPos(coordinates.x, coordinates.y);
}

void click(coords coordinates) {
  std::cout << "Clicking on " << coordinates.toString() << std::endl;
  setCursor(coordinates);
  mouseButton(true);
  mouseButton(false);
  waitSeconds(0.1);
}

void click(coords coordinates, coords origin, bool subtract) {
  click(correctCoords(coordinates, origin, subtract));
}

void mouseButton(bool down) {
  #ifdef __linux__
  XTestFakeButtonEvent(d, 1, down, CurrentTime);
  XFlush(d);
  #elif _WIN32
  INPUT Inputs[1];
  Inputs[0].type = INPUT_MOUSE;
  Inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;
  if (down) Inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
  SendInput(1, Inputs, sizeof(INPUT));
  ZeroMemory(Inputs,sizeof(Inputs));
  #endif
}

void drag(coords from, coords to) {
  std::cout << "Dragging from "
            << from.toString()
            << " to "
            << to.toString()
            << std::endl;
  setCursor(from);
  mouseButton(1);
  waitSeconds(0.1);

  setCursor(to);
  waitSeconds(0.11);
  mouseButton(0);

}

void drag(coords from, coords to, coords origin, bool subtract) {
  drag(correctCoords(from, origin, subtract), correctCoords(to, origin, subtract));
}

void dragAndHold(coords from, coords to, double secondsToHold) {
  setCursor(from);
  mouseButton(1);
  waitSeconds(0.1);

  setCursor(to);
  waitSeconds(0.11 + secondsToHold);
  mouseButton(0);
};

void dragAndHold(coords from, coords to, double secondsToHold, coords origin, bool subtract) {
  dragAndHold(correctCoords(from, origin, subtract), correctCoords(to, origin, subtract), secondsToHold);
};

void dragSlowly(coords from, coords to, int steps) {
  int xDiff = to.x - from.x;
  int yDiff = to.y - from.y;

  setCursor(from);
  mouseButton(1);

  waitSeconds(0.1);

  for (int i = 0; i < steps; i++) {
    setCursor(from.x + xDiff / steps * i, from.y + yDiff / steps * i);
    waitSeconds(0.005);
  }
  setCursor(to);
  mouseButton(0);
}

void dragSlowly(coords from, coords to, coords origin, int steps, bool subtract) {
  dragSlowly(correctCoords(from, origin, subtract), correctCoords(to, origin, subtract), steps);
}

void joinLobby(data appData) {
  std::cout << "Joining lobby " << appData.code << std::endl;

  click(coords{appData.origin.x + appData.rejoinCross.x, appData.origin.y + appData.rejoinCross.y});
  waitSeconds(0.1);
  click(coords{appData.origin.x + appData.rejoinBox1.x, appData.origin.y + appData.rejoinBox1.y});
  waitSeconds(0.1);
  click(coords{appData.origin.x + appData.rejoinBox2.x, appData.origin.y + appData.rejoinBox2.y});
  waitSeconds(0.1);
  write(appData.code);
  waitSeconds(1);
  click(coords{appData.origin.x + appData.rejoinArrow.x, appData.origin.y + appData.rejoinArrow.y});
}

void write(std::string text) {
  std::cout << text << std::endl;
  #ifdef __linux__
  std::string command = "xdotool type ";
  command += "'" + text + "'";
  send_system_command(command);
  #elif _WIN32
  #endif
}

void pressEnter() {
  #ifdef __linux__
  system("xdotool key Return");
  #elif _WIN32
  std::cout << "Press enter" << std::endl;
  #endif
};

void sendText(std::vector<std::string> sentences) {
  waitSeconds(3);
  for (std::string sentence : sentences) {
    write(sentence);
    waitSeconds(1);
    pressEnter();
    waitSeconds(2);

  }
};

void sendSystemCommand(std::string command) {
  std::cout << "Sending command: " << command << std::endl;
  #ifdef __linux__
  int length = command.size();
  char passable[length+1];
  std::strcpy(passable, command.c_str());
  system(passable);
  #endif
};
