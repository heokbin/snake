#include <ctime>
#include "console.h"
#include <string>
#include <cstring>
#include <cstdlib>

void setup();
void makeMap();
void fruit();
void newFruit();
void drawSnake();
void win();
void snakeDie();
void nextSnake();
void handleInput();
void printScore(int score);
void restartGame();
void printLose();

void console::init();
void console::wait();
void console::draw(int x, int y, std::string s);
void console::clear();
enum Key {K_NONE = 0, K_OTHER, K_LEFT, K_RIGHT, K_UP, K_DOWN, K_ESC, K_ENTER};
bool console::key(Key k);

#define BOARD_SIZE 20
#define MOVE_DELAY 15
#define SNAKE_STRING "■"
#define SNAKE_BODY_STRING "■"
#define APPLE_STRING "●"

int x;
int y;
int snakeX[BOARD_SIZE * BOARD_SIZE] = {};
int snakeY[BOARD_SIZE * BOARD_SIZE] = {};
int fruitX;
int fruitY;
int snakeLen;
bool trueFalse = true;
int startNum = 0;
int score = 0;
std::string direc = "";
int main() {
    while (true) {

        setup();

        while(trueFalse){
            console::clear();

            makeMap();
            
            fruit();
            
            drawSnake();

            if (snakeLen == (BOARD_SIZE-2)*(BOARD_SIZE-2)) {
                win();
                break;
            }

            snakeDie();

            nextSnake();

            printScore(score);
            console::wait();
        }

        restartGame();
    }
}

void setup() {
    console::init();
    trueFalse = true;
    startNum = 0;
    score = 0;
    snakeLen = 1;
    snakeX[BOARD_SIZE * BOARD_SIZE] = {};
    snakeY[BOARD_SIZE * BOARD_SIZE] = {};
    snakeX[0] = BOARD_SIZE/2;
    snakeY[0] = BOARD_SIZE/2;
    x = BOARD_SIZE/2;
    y = BOARD_SIZE/2;
    direc = "right";
    newFruit();
}

void fruit() {
    console::draw(fruitX, fruitY, APPLE_STRING);
    if ((snakeX [0] == fruitX) && (snakeY [0] == fruitY)) {
        if (snakeLen == (BOARD_SIZE-2)*(BOARD_SIZE-2)-1) {
            snakeLen++;
        }
        else {
            newFruit();
            snakeLen++;
            score += 10;
        }
    }
}

void newFruit() {
    int num = 0;
    int fruitXY [((BOARD_SIZE - 2)*(BOARD_SIZE - 2) - snakeLen)] [2];
    for (int i = 0; i < BOARD_SIZE - 2; i++) {
        for (int j = 0; j < BOARD_SIZE - 2; j++) {
            fruitXY [num] [0] = i+1;
            fruitXY [num] [1] = j+1;
            // num++;
            int k = 0;
            while(k < snakeLen) {
                if ((i + 1 == snakeX[k]) && (j + 1 == snakeY[k])) {
                    num--;
                    k = snakeLen;
                }
                k++;
            }
            num++;
        }
    }
    srand(time(NULL));
    int randomNum = (rand()*rand()/rand()) % ((BOARD_SIZE- 2)*(BOARD_SIZE- 2) - snakeLen);
    fruitX = fruitXY [randomNum] [0];
    fruitY = fruitXY [randomNum] [1];
}

void drawSnake() {
    console::draw(snakeX[0], snakeY[0], SNAKE_STRING);

    for (int i = 1; i < snakeLen; i++) {
        console::draw(snakeX[i], snakeY[i], SNAKE_BODY_STRING);
    }
}

void win() {
    std::string youWin [8] = {"Y","o","u"," ","W","i","n","!",};
    int j = 0;
    for (int i = 6; i< 14; i++) {
        std::string print = youWin [j];
        console::draw(i, (BOARD_SIZE-1)/2, print);
        j++;
    }
}

void snakeDie() {
    if (snakeX [0] == 0 || snakeX [0] == (BOARD_SIZE - 1) || snakeY [0] == 0 || snakeY [0] == (BOARD_SIZE - 1)) {
        trueFalse = false;
    }

    for (int i = 1; i < snakeLen; i++) {
        if (snakeX [0] == snakeX [i] && snakeY [0] == snakeY [i]) {
            trueFalse = false;
        }
    }
}

void nextSnake() {
    if (startNum == MOVE_DELAY) {

        for (int i = snakeLen - 1; i>0; i--) {
            snakeX [i] = snakeX[i-1];
            snakeY [i] = snakeY[i-1];
        }
        handleInput();
        snakeX [0] = x;
        snakeY [0] = y;
    }
    if (startNum == 15) {
        startNum = 0;
    }
    startNum++;
}

void handleInput() {
    if (console::key(console::K_ESC)) {
        exit(0);
    }
    else if (console::key(console::K_LEFT)) {
        if (snakeLen != 1 && direc == "right") {
            x++;
        }
        else {
            x--;
            direc = "left";
        }
    }
    else if (console::key(console::K_RIGHT)) {
        if (snakeLen != 1 && direc == "left") {
            x--;
        }
        else {
            x++;
            direc = "right";
        }  
    }
    else if (console::key(console::K_UP)) {
        if (snakeLen != 1 && direc == "down") {
            y++;
        }
        else {
            y--;
            direc = "up";
        }
    }
    else if (console::key(console::K_DOWN)) {
        if (snakeLen != 1 && direc == "up") {
            y--;
        }
        else {
            y++;
            direc = "down";
        }
    }
    
    else {
        if (direc == "left") {
            x--;
        }
        if (direc == "right") {
            x++;
        }
        if (direc == "up") {
            y--;
        }
        if (direc == "down") {
            y++;
        }
    }
}

void printScore(int score) {
    std::string num = std::to_string(score);
    std::string print [7 + num.length()] = {"S", "c", "o", "r", "e", ":", " "};
    
    int n = 7;
    for (int i = 0; i < num.length(); i++) {
        print [n] = std::to_string(int(num[i])-48);
        n++;
    }
    
    int len = sizeof(print)/sizeof(*print);
    int formul = (BOARD_SIZE - len) / 2;
    int j = 0;
    for (int i = formul; i< formul + len; i++) {
        std::string printString = print [j];
        console::draw(i, BOARD_SIZE, printString);
        j++;
    }
}

void restartGame() {
    bool restart = true;
    while (restart) {
        if (console::key(console::K_ESC)) {
            exit(0);
        }
        else if (console::key(console::K_ENTER)) {
            restart = false;
        }
        printLose();
        console::wait();
    }
}

void printLose() {
    std::string print1 [9] = {"Y", "O", "U", " ", "L", "O", "S", "E", "!"};
    std::string print2 [18] = {"T", "r", "y", " ", "a", "g", "a", "i", "n", "?", " ", "(", "E", "n", "t", "e", "r", ")"};
            
    int j = 0;
    for (int i = 6; i< 15; i++) {
        std::string print = print1 [j];
        console::draw(i, (BOARD_SIZE-1)/2, print);
        j++;
    }

    j = 0;
    for (int i = 1; i< 19; i++) {
        std::string print = print2 [j];
        console::draw(i, ((BOARD_SIZE-1)/2 + 1), print);
        j++;
    }
}