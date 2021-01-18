#pragma once

#define REDTEAM 1 //the red team
#define BLUETEAM 2 //the blue team
#define MAX 50

struct LogData {
    char name[20];
    int team;
};

struct Point {
    int x, y;
};

struct User {
    int team;
    int flag;
    char name[20];
    struct Point point;
};

struct Ctrl {
    int kick;
    int carry;
};

struct TransMsg {
    int dirx;
    int diry;
    struct Ctrl ctrl;
};

struct Map {
    int width;
    int height;
    struct Point start;
    int gate_width;
    int gate_height;
};
