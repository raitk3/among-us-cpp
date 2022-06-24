#include "include/tasks.h"

auto crosses = std::map<task, coords> {
  {ALIGN, {328, 98}},
  {ASTEROIDS, {323, 93}},
  {CARD, {330, 103}},
  {CENTER, {241, 182}},
  {COURSE, {234, 121}}, // ????
  {DISTRIBUTOR, {330, 95}},
  {DIVERT, {324, 96}},
  {DOWNLOAD, {235, 182}},
  {FILTER, {330, 109}},
  {FUEL, {426, 95}},
  {MANIFOLDS, {326, 256}},
  {REACTOR, {224, 167}},
  {SAMPLE, {331, 94}},
  {SCAN, {325, 109}},
  {SHIELDS, {321, 102}},
  {STABILIZE, {330, 96}},
  {TRASH, {328, 95}},
  {VENT, {323, 92}},
  {WIRES, {322, 92}}
};

bool checkCross(task taskToCheck, data appData) {
  coords pixel = crosses.at(taskToCheck);
  color pixelColor = getPixel(correctCoords(pixel, appData.origin));
  color pixelColorN = getPixel(correctCoords({pixel.x - 7, pixel.y}, appData.origin));
  color pixelColorE = getPixel(correctCoords({pixel.x, pixel.y + 7}, appData.origin));

  bool check = pixelColor == color{51, 51, 51};
  bool checkN = pixelColorN == color{238, 238, 238};
  bool checkE = pixelColorE == color{238, 238, 238};
  return check && checkN && checkE;
};

void detectTask(data appData) {
  startTask(appData);
  for (auto cross: crosses) {
    if (checkCross(cross.first, appData)) {
      std::cout << "Detected " << taskStrings.at(cross.first) << std::endl;
      doTask(appData, cross.first, false);
      break;
    }
  }
};


void doTask(data appData, task taskToDo, bool start) {

  if (start) {
    startTask(appData);
  }

  switch (taskToDo) {
  case ALIGN:
    align(appData);
    break;
  case ASTEROIDS:
    if (getWire(getPixel({400, 194}, appData.origin)) != wireColor::UNDEFINED) {
      wires(appData);
      break;
    }
    asteroids(appData);
    break;
  case CARD:
    card(appData);
    break;
  case CENTER:
    centerClick(appData);
    break;
  case COURSE:
    course(appData);
    break;
  case DISTRIBUTOR:
    distributor(appData);
    break;
  case DIVERT:
    divert(appData);
    break;
  case DOWNLOAD:
    download(appData);
    break;
  case FILTER:
    filter(appData);
    break;
  case FUEL:
    fuel(appData);
    break;
  case MANIFOLDS:
    manifolds(appData);
    break;
  case REACTOR:
    if (getPixel({481, 331}, appData.origin) == color{241, 212, 161}) {
      download(appData);
      break;
    }
    reactor(appData);
    break;
  case SAMPLE:
    sample(appData);
    break;
  case SHIELDS:
    if (getPixel({905, 370}, appData.origin) == color{145, 175, 186}) {
      trash(appData);
      break;
    }
    shields(appData);
    break;
  case STABILIZE:
    centerClick(appData);
    break;
  case TRASH:
    trash(appData);
    break;
  case VENT:
    vent(appData);
    break;
  case WIRES:
    wires(appData);
    break;
  default:
    doNothing();
  }
};

void startTask(data appData) {
  #ifdef _WIN32
  click(coords{10, 10});
  #endif
  click(coords{1260,660}, appData.origin);
  waitSeconds(0.3);
};

void doNothing() {
  std::cout << "Doing nothing lol" << std::endl;
};

void align(data appData) {
  std::cout << "Doing align" << std::endl;
  coords center = {884, 384};
  double alignParabolaConstant = 0.0008;
  for (int y = -277; y < 277; y += 20) {
    int x = floor(alignParabolaConstant * std::pow(y, 2));
    coords actualCoords = {center.x + x, center.y + y};
    color currentColor = getPixel(actualCoords, appData.origin);
    if (currentColor.r > 70 || currentColor.g > 70 || currentColor.b > 70) {
        drag(actualCoords, center, appData.origin);
        break;
    }
    if (checkBreak()) { break; }
  }
};

// ToDo
void asteroids(data appData)
{
  std::cout << "Doing asteroids" << std::endl;

  coords origin = coords{400, 100};
  int size = 500;
  int steps = 15;
  while (checkCross(ASTEROIDS, appData)) {
    for (int x = 0; x < steps; x++) {
      for (int y = 0; y < steps; y++) {
        coords coordsToCheck = correctCoords(
              {origin.x + (size / steps * x), origin.y +(size / steps * y)}, appData.origin);
        if (checkBreak()) { return; }
        if (getPixel(coordsToCheck).g < 65) { click(coordsToCheck); }
      }
    }
  }
};

void card(data appData) {
  std::cout << "Doing card swipe" << std::endl;
  click(coords{580, 580}, appData.origin);
  waitSeconds(0.5);
  dragSlowly({370, 300}, {1130, 300}, appData.origin, 100);
};

void centerClick(data appData) {
  std::cout << "Clicking the center of the screen" << std::endl;
  coords center = {appData.display.x / 2, appData.display.y / 2};
  click(center, appData.origin);
};

// ToDo
void course(data appData) {
  std::cout << "Diverting course" << std::endl;
  const int firstX = 403;
  std::vector<coords> points{};
  color approvedColours[] = {
    {132, 160, 176},
    {31, 111, 160},
    {36, 112, 161},
    {135, 161, 176},
    {100, 60, 0},
    {255, 255, 255}
  };

  for (int i = 0; i < 5; i++) {
    int x = firstX + i * 140;
    for (int y = 200; y < 550; y++){
      coords point{x, y-3};
      if (std::find(std::begin(approvedColours),
                    std::end(approvedColours),
                    getPixel(point, appData.origin)) != std::end(approvedColours)) {
          points.push_back(point);
      }
    }
    for (auto point: points) {
      setCursor(point);
      mouseButton(true);
      waitSeconds(0.2);
    }
    mouseButton(false);
  }
};

// ToDo
void distributor(data appData) {
  std::cout << "Calibrating distributor" << std::endl;

  bool done[] = {false, false, false};
  coords lights[] = {
      {875, 170},
      {875, 350},
      {875, 540}
  };

  coords buttons[] = {
      {875, 220},
      {875, 420},
      {875, 600}
  };

  while (checkCross(DISTRIBUTOR, appData)) {
    for (int i = 0; i < 3; i++) {
      if (getPixel(lights[i], appData.origin) == color{0, 0, 0}) {
        done[i] = false;
      }
    }
    if (done[2]) { return; }
    for (int i = 0; i < 3; i++) {
      if (!(getPixel(lights[i], appData.origin) == color{0, 0, 0} || done[i])) {
        click(buttons[i], appData.origin);
        done[i] = true;
      }
    }
    waitSeconds(0.05);
  }
};

void divert(data appData) {
  std::cout << "Diverting power" << std::endl;
  int switchesX[] = {443, 510, 578, 648, 717, 784, 854, 923};
  int switchesY = 560;
  for (int x : switchesX) {
    if (getPixel(coords{x, switchesY}, appData.origin).r > 100) {
      drag({x, switchesY}, {x, 440}, appData.origin);
      break;
    }
  }
};

void download(data appData) {
  std::cout << "Dying on download again" << std::endl;
  click({680, 470}, appData.origin);
};

// ToDo
void filter(data appData) {
  std::cout << "Cleaning filter" << std::endl;
  int steps = 50;
  coords finish{380, 380};

  while (checkCross(FILTER, appData))
  {
    std::cout << "Cleaning" << std::endl;
    if (checkBreak()) { break; }
    for (int x = 496; x <= 996; x += steps) {
      if (checkBreak() || !checkCross(FILTER, appData)) { break; }
      for (int y = 70; y <= 697; y += steps)
      {
        if (checkBreak() || !checkCross(FILTER, appData)) { break; }
        if (getPixel(correctCoords({x, y}, appData.origin)).b < 150) {
          drag({x, y}, finish, appData.origin);
        }
      }
    }
  }
};

void fuel(data appData) {
    std::cout << "Fuelling" << std::endl;
    setCursor(correctCoords(coords{1040, 620}, appData.origin));
    mouseButton(1);
    while (!checkBreak() && getPixel(correctCoords({1075, 530}, appData.origin)).g != 255) {
        continue;
    }
    mouseButton(0);

};

//ToDo: 2, 8
int getManifoldsNumber(coords location)
{
  std::array<coords[7], 10> definitions
  {
    {{{14, 5}, {15, 15}, {16, 29}, {16, 38}, {6, 44}, {18, 44}, {30, 44}}, // 1
    {{7, 9}, {17, 3}, {25, 12}, {19, 30}, {11, 39}, {7, 45}, {25, 45}}, // 2
    {{10, 3}, {24, 9}, {19, 18}, {28, 22}, {29, 41}, {15, 46}, {3, 39}}, // 3
    {{3, 3}, {4, 26}, {19, 3}, {19, 23}, {20, 35}, {20, 46}, {29, 24}}, // 4
    {{10, 3}, {29, 2}, {19, 18}, {28, 22}, {29, 41}, {15, 46}, {3, 39}}, // 5
    {{19, 2}, {9, 11}, {3, 28}, {10, 44}, {28, 42}, {29, 26}, {14, 22}}, // 6
    {{5, 3}, {17, 5}, {30, 4}, {24, 15}, {16, 37}, {25, 11}, {17, 44}}, // 7
    {{17, 2}, {6, 10}, {27, 8}, {17, 21}, {3, 35}, {32, 36}, {16, 45}}, // 8
    {{19, 3}, {6, 13}, {17, 22}, {29, 9}, {29, 17}, {29, 32}, {29, 46}}, // 9
    {{9, 6}, {6, 44}, {16, 45}, {26, 2}, {20, 24}, {28, 46}, {33, 24}} // 10
    }
  };

  for (int i = 0; i < 10; i++) {
    bool success = true;
    for (int j = 0; j < 7; j++) {
      coords offset = definitions[i][j];
      coords pixel = {location.x + offset.x, location.y + offset.y};
      if (getPixel(pixel).r > 70) {
          success = false;
          break;
      }
    }
    if (success) { return i+1; }
  }
  return 0;
};

void manifolds(data appData) {
  std::cout << "Unlocking manifolds" << std::endl;

  coords buttons[10];
  int values[10];
  int xOrigin = 447;
  int yOrigin = 304;

  int xDiff = 109;
  int yDiff = 111;

  if (!checkCross(MANIFOLDS, appData)) { return; }

  for (int row = 0; row < 2; row++) {
    for (int column = 0; column < 5; column ++) {
      int cell = 5 * row + column % 5;
      coords currentCoords = correctCoords({xOrigin + column*xDiff, yOrigin + row*yDiff},
                                             appData.origin);
      buttons[cell] = currentCoords;
      values[cell] = getManifoldsNumber(currentCoords);
    }
  }

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 5; j++) {
      int value = values[5*i + j%5];
      std::string separator = (value==10) ? "|" : "| ";
      std::cout << separator << value;
    }
    std::cout << "|" << std::endl;
  }

  for (int i = 1; i < 11; i++) {
    for (int j = 0; j < 10; j++) {
      if (values[j] == i) {
        click(buttons[j]);
        break;
      }
      if (values[j] == 0) {
        click(crosses.at(MANIFOLDS));
        waitSeconds(0.5);
        startTask(appData);
        manifolds(appData);
        return;
      }
    }
  }
};

void reactor(data appData) {
  std::cout << "Doing Simon says" << std::endl;

  int order[5] = {-1, -1, -1, -1, -1};
  coords lights[9];
  coords buttons[9];
  int j = 0;

  int previousLight = -1;
  int foundLight = -1;

  for (int i = 0; i < 9; i++) {
    int y = 340 + floor(i / 3) * 90;
    int x1 = 370 + i%3 * 90;
    int x2 = 810 + i%3 * 90;
    lights[i] = {x1, y};
    buttons[i] = {x2, y};
  }

  while (checkCross(REACTOR, appData)) {
    while (checkCross(REACTOR, appData)
          && !(getPixel(buttons[0], appData.origin) == color{189, 189, 189}
          || getPixel(buttons[0], appData.origin) == color{214, 119, 119})) {
      foundLight = -1;

      for (int i = 0; i < 9; i++) {
        if (!(getPixel(lights[i], appData.origin) == color{0, 0, 0}
              || getPixel(lights[i], appData.origin) == color{95, 0, 0})) {
          foundLight = i;
          if (foundLight != previousLight) {
            order[j] = i;
            j++;
          }
          break;
        }
      }
      previousLight = foundLight;
    }

    for(int num : order) {
      if (num != -1) {
        click(buttons[num], appData.origin);
      }
    }

    for (int i = 0; i < 5; i++) { order[i] = -1; }
    j = 0;
  }
};

// ToDo
void sample(data appData)
{
  std::cout << "Inspecting sample" << std::endl;
  waitSeconds(0.25);
  click({900, 670}, appData.origin);
  waitSeconds(61);
  for (int i = 0; i < 5; i++) {
    int x = 520 + 80 * i;
    int buttonY = 600;
    int liquidY = 420;
    if (getPixel(correctCoords({x, liquidY}, appData.origin))
            == color{246, 134, 134}) {
        click(correctCoords({x, buttonY}, appData.origin));
        break;
    }
  }
};

void shields(data appData)
{
  std::cout << "Shiieelds" << std::endl;
  coords coordinates[] = {
    {682, 288},  // 241, 21, 25
    {602, 329},  //242, 21, 26
    {602, 450},  // 241, 22, 27
    {671, 482},  // 240, 22, 27
    {762, 450},  // 236, 30, 37
    {758, 319},  // 244, 17, 20
    {740, 318}  // 241, 21, 26
  };
  for (coords coord : coordinates) {
    if (getPixel(coord, appData.origin).g < 50) {
      click(coord, appData.origin);
      waitSeconds(0.07);
    }
  }
};

void trash(data appData)
{
  std::cout << "Doing trash" << std::endl;
  dragAndHold(coords{900, 300}, coords{900, 500}, 1.4, appData.origin);
};

// ToDo
void vent(data appData) {
  std::cout << "Cleaning vents" << std::endl;
  coords origin = correctCoords(coords{383, 116}, appData.origin);
  coords size = {600, 530};
  int step = 50;
  for (int x = origin.x; x < (origin.x + size.x + 1); x += step) {
    for (int y = origin.y; y < (origin.y + size.y + 1); y += step) {
      if (checkCross(VENT, appData) && !checkBreak()) {
        click({x, y});
      } else { return; }
    }
  }
};

wireColor getWire(color wire)
{
  if (wire.r > 250 && wire.g < 10 && wire.b < 1) {
    return RED;
  } else if (wire.r < 40 && wire.g < 40 && wire.b == 255) {
    return BLUE;
  } else if (wire.r > 250 && wire.g > 200 && wire.b < 10) {
    return YELLOW;
  } else if (wire.r > 250 && wire.b > 250 && wire.g < 10) {
    return PURPLE;
  }
  return UNDEFINED;
};

void wires(data appData)
{
  std::cout << "Doing wires" << std::endl;

  for (int i = 0; i < 4; i++) {
    coords current = coords{400, 194+132 * i};
    wireColor currentWire = getWire(getPixel(current, appData.origin));
    for (int j = 0; j < 4; j++) {
      coords pair = coords{940, 194+132*j};
      wireColor pairWire = getWire(getPixel(pair, appData.origin));
      if (currentWire == pairWire) {
        drag(current, pair, appData.origin);
        waitSeconds(0.1);
        break;
      }
    }
  }
};

void kill() {
  write("q");
};
