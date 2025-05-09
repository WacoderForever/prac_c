#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>

#define HEIGHT 20
#define WIDTH 40
#define INITIAL_DELAY 100000 // 100ms in microseconds

int snakeTailX[100], snakeTailY[100]; 
int snakeTailLen;
int gameover, key, score;
int x, y, fruitx, fruity;
int gameDelay; // Variable to control game speed

void setup() {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);  // Hide cursor
    timeout(100); // Non-blocking input with 100ms timeout
    
    // Initialize random seed
    srand(time(NULL));
    
    // Initialize game variables
    gameover = 0;
    key = 0;
    snakeTailLen = 0;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    
    fruitx = rand() % WIDTH;
    fruity = rand() % HEIGHT;
    
    while (fruitx == 0)
        fruitx = rand() % WIDTH;
    while (fruity == 0)
        fruity = rand() % HEIGHT;
        
    score = 0;
    gameDelay = INITIAL_DELAY; // Set initial game speed
}

void draw() {
    clear();
    
    // Draw top border
    for (int i = 0; i < WIDTH + 2; i++)
        mvprintw(0, i, "-");
    
    // Draw side borders and game area
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j <= WIDTH; j++) {
            if (j == 0 || j == WIDTH)
                mvprintw(i + 1, j, "#");
            else if (i == y && j == x) {
                // Draw the snake head with direction
                char headChar = 'O';
                switch (key) {
                    case 1: headChar = '<'; break; // Left
                    case 2: headChar = '>'; break; // Right
                    case 3: headChar = '^'; break; // Up
                    case 4: headChar = 'v'; break; // Down
                    default: headChar = '>'; break; // Default right
                }
                mvprintw(i + 1, j, "%c", headChar);
            }
            else if (i == fruity && j == fruitx)
                mvprintw(i + 1, j, "*");
            else {
                int prTail = 0;
                for (int k = 0; k < snakeTailLen; k++) {
                    if (snakeTailX[k] == j && snakeTailY[k] == i) {
                        mvprintw(i + 1, j, "o");
                        prTail = 1;
                    }
                }
                if (!prTail)
                    mvprintw(i + 1, j, " ");
            }
        }
    }
    
    // Draw bottom border
    for (int i = 0; i < WIDTH + 2; i++)
        mvprintw(HEIGHT + 1, i, "-");
    
    // Draw score and instructions
    mvprintw(HEIGHT + 2, 0, "Score = %d", score);
    mvprintw(HEIGHT + 3, 0, "Press W, A, S, D for movement. Press Q to quit.");
    
    refresh();
}

void input() {
    int ch = getch();
    if (ch != ERR) {
        switch (tolower(ch)) {
            case 'a':
                if (key != 2)
                    key = 1;
                break;
            case 'd':
                if (key != 1)
                    key = 2;
                break;
            case 'w':
                if (key != 4)
                    key = 3;
                break;
            case 's':
                if (key != 3)
                    key = 4;
                break;
            case 'q':
                gameover = 1;
                break;
        }
    }
}

void logic() {
    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    int prev2X, prev2Y;
    
    snakeTailX[0] = x;
    snakeTailY[0] = y;
    
    for (int i = 1; i < snakeTailLen; i++) {
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    
    switch (key) {
        case 1: 
            x--; 
            break;
        case 2: 
            x++; 
            break;
        case 3: 
            y--; 
            break;
        case 4: 
            y++; 
            break;
        default:
            break;
    }
    
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        gameover = 1;
        
    for (int i = 0; i < snakeTailLen; i++) {
        if (snakeTailX[i] == x && snakeTailY[i] == y)
            gameover = 1;
    }
    
    if (x == fruitx && y == fruity) {
        fruitx = rand() % WIDTH;
        fruity = rand() % HEIGHT;
        
        while (fruitx == 0)
            fruitx = rand() % WIDTH;
        while (fruity == 0)
            fruity = rand() % HEIGHT;
            
        score += 10;
        snakeTailLen++;
        
        // Increase speed every 100 points (10 fruits)
        if (score % 100 == 0 && gameDelay > 20000) { // Don't go faster than 20ms
            gameDelay = gameDelay * 0.9; // Reduce delay by 10%
            timeout(gameDelay / 1000); // Update ncurses timeout (convert to ms)
            mvprintw(HEIGHT + 4, 0, "Speed increased! Current delay: %d ms", gameDelay / 1000);
        }
    }
}

int main() {
    setup();
    
    while (!gameover) {
        draw();
        input();
        logic();
        usleep(gameDelay); // Use variable delay
    }
    
    // Clean up ncurses
    endwin();
    printf("Game Over! Final Score: %d\n", score);
    
    return 0;
}