#pragma once

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
    struct Point start;
    int gate_width;
    int gate_heigth;
}





