#pragma once

#define REDTEAM 1 //the red team
#define BLUETEAM 2 //the blue team
#define MAX 50
#define MAXMSG 1024
struct LogRequest {
    char name[20];
    int team; //0 RED 1 BLUE
    char msg[512];
};

struct LogResponse{ 
    int type; // 0 success 1 faild
    char msg[512];
};

struct Point {
    int x, y;
};

struct User {
    int fd;
    int online;
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

#define FT_TEST 0x01
#define FT_WALL 0x02
#define FT_MSG  0x04
#define FT_ACK  0x08

struct FootBallMsg {
    int type;
    int size;
    char msg[MAXMSG];
};
