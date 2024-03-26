#include "console.h"
#include <string>
#include <cstring>

void console::draw(int x, int y, std::string s);

#define WALL_VERTICAL_STRING "┃"
#define WALL_HORIZONTAL_STRING "━"
#define WALL_RIGHT_TOP_STRING "┓"
#define WALL_LEFT_TOP_STRING "┏"
#define WALL_RIGHT_BOTTOM_STRING "┛"
#define WALL_LEFT_BOTTOM_STRING "┗"
#define BOARD_SIZE 20

void makeMap() {
    console::draw(0,0,WALL_LEFT_TOP_STRING);
    console::draw(0, BOARD_SIZE-1, WALL_LEFT_BOTTOM_STRING);
    console::draw(BOARD_SIZE-1, 0, WALL_RIGHT_TOP_STRING);
    console::draw(BOARD_SIZE-1, BOARD_SIZE-1, WALL_RIGHT_BOTTOM_STRING);
    for (int i = 1; i < BOARD_SIZE - 1; i++) {
        int j=0;
        console::draw(i,j,WALL_HORIZONTAL_STRING);
        j = BOARD_SIZE-1;
        console::draw(i,j,WALL_HORIZONTAL_STRING);
    }

    for (int j = 1; j < BOARD_SIZE - 1; j++) {
        int i=0;
        console::draw(i,j,WALL_VERTICAL_STRING);
        i = BOARD_SIZE-1;
        console::draw(i,j,WALL_VERTICAL_STRING);
    }
}