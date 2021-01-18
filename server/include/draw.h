#pragma once

extern struct Map court;

extern WINDOW *Football, *Message, *Help, *Score, *Write;

void initgame();
void drawpeople();
void drawball();
void drawhelp();
void drawchat();
void drawinput();
WINDOW *create_newwin(int width, int height, int  startx, int starty);
void destroy_win(WINDOW *win);
void gotoxy(int x, int y);
void gotoxy_putc(int x, int y, char c);
void gotoxy_puts(int x, int y, char *str);
void w_gotoxy_putc(WINDOW *win, int x, int y, char c);
void w_gotoxy_puts(WINDOW *win, int x, int y, char *str);
void initfootball();
void *draw(void *arg);


