#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <curses.h>
#include <sys/epoll.h>
#include "getvalue.h"
#include "color.h"
#include "udp.h"
#include "game.h"
#include "draw.h"
#include "udp_epoll.h"
#include "thread_pool.h"
#include "sub_reactor.h"
#include "heart_beat.h"
#include "stdint.h"
// DBG
#ifndef _D
#define DBG(fmt, args...) printf(fmt, ##args)
#else
#define DBG(fmt, args...)
#endif
