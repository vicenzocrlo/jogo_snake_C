#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BOARD_WIDTH  40
#define BOARD_HEIGHT 20
#define MAX_SNAKE_LEN (BOARD_WIDTH * BOARD_HEIGHT)

typedef enum {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} Direction;

typedef enum {
    DIFF_EASY = 1,
    DIFF_MEDIUM = 2,
    DIFF_HARD = 3
} Difficulty;

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    Position body[MAX_SNAKE_LEN];
    int length;
    Direction dir;
} Snake;

typedef struct {
    Position pos;
    int points;
    char symbol;
} Food;

typedef struct {
    Snake snake;
    Food food;
    int score;
    int highScore;
    bool gameOver;
    bool isPaused;
    Difficulty difficulty;
    int delayMs;
    int foodEaten;
} GameState;

/* Function prototypes */
void init_console(void);
void hide_cursor(void);
void set_cursor_position(int x, int y);
void clear_screen(void);

void init_game(GameState *game, Difficulty difficulty);
void draw_board(const GameState *game);
void draw_banner(void);
void process_input(GameState *game);
void update_game(GameState *game);
void spawn_food(GameState *game);
void show_game_over(const GameState *game);
void show_menu(Difficulty *selectedDiff);

#endif /* GAME_H */
