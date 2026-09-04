#include "game.h"
#include <windows.h>
#include <conio.h>
#include <time.h>

static int g_highScore = 0;

void init_console(void) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    }
    hide_cursor();
    srand((unsigned int)time(NULL));
}

void hide_cursor(void) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

void set_cursor_position(int x, int y) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(hOut, pos);
}

void clear_screen(void) {
    system("cls");
}

void spawn_food(GameState *game) {
    bool valid = false;
    while (!valid) {
        game->food.pos.x = 1 + rand() % (BOARD_WIDTH - 2);
        game->food.pos.y = 1 + rand() % (BOARD_HEIGHT - 2);
        
        valid = true;
        for (int i = 0; i < game->snake.length; i++) {
            if (game->snake.body[i].x == game->food.pos.x &&
                game->snake.body[i].y == game->food.pos.y) {
                valid = false;
                break;
            }
        }
    }

    if ((game->foodEaten + 1) % 5 == 0) {
        game->food.symbol = '$';
        game->food.points = 30;
    } else {
        game->food.symbol = '*';
        game->food.points = 10;
    }
}

void init_game(GameState *game, Difficulty difficulty) {
    game->difficulty = difficulty;
    game->score = 0;
    game->highScore = g_highScore;
    game->gameOver = false;
    game->isPaused = false;
    game->foodEaten = 0;

    switch (difficulty) {
        case DIFF_EASY:
            game->delayMs = 120;
            break;
        case DIFF_MEDIUM:
            game->delayMs = 75;
            break;
        case DIFF_HARD:
            game->delayMs = 40;
            break;
        default:
            game->delayMs = 75;
            break;
    }

    game->snake.length = 4;
    game->snake.dir = DIR_RIGHT;

    int startX = BOARD_WIDTH / 2;
    int startY = BOARD_HEIGHT / 2;

    for (int i = 0; i < game->snake.length; i++) {
        game->snake.body[i].x = startX - i;
        game->snake.body[i].y = startY;
    }

    spawn_food(game);
}

void draw_board(const GameState *game) {
    set_cursor_position(0, 0);

    printf("========================================\n");
    printf("   JOGO DA COBRINHA (SNAKE GAME IN C)   \n");
    printf("========================================\n");

    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (y == 0 || y == BOARD_HEIGHT - 1 || x == 0 || x == BOARD_WIDTH - 1) {
                printf("#");
            } else {
                bool printed = false;

                // Desenha a cabeça da cobra
                if (x == game->snake.body[0].x && y == game->snake.body[0].y) {
                    printf("O");
                    printed = true;
                } else {
                    // Desenha o corpo da cobra
                    for (int i = 1; i < game->snake.length; i++) {
                        if (x == game->snake.body[i].x && y == game->snake.body[i].y) {
                            printf("o");
                            printed = true;
                            break;
                        }
                    }
                }

                // Desenha a comida se o espaço estiver vazio
                if (!printed) {
                    if (x == game->food.pos.x && y == game->food.pos.y) {
                        printf("%c", game->food.symbol);
                    } else {
                        printf(" ");
                    }
                }
            }
        }
        printf("\n");
    }

    printf("----------------------------------------\n");
    printf(" Pontos: %-4d | Recorde: %-4d | Frutas: %-2d\n", game->score, game->highScore, game->foodEaten);
    printf(" Dificuldade: %s\n", game->difficulty == DIFF_EASY ? "Facil" : (game->difficulty == DIFF_MEDIUM ? "Medio" : "Dificil"));
    printf("----------------------------------------\n");
    printf(" Controles: [W/A/S/D] ou [Setas] Mover \n");
    printf("            [P] Pausar | [Q] Sair       \n");

    if (game->isPaused) {
        set_cursor_position(BOARD_WIDTH / 2 - 5, BOARD_HEIGHT / 2 + 3);
        printf(" [ PAUSADO ] ");
    }
}

void process_input(GameState *game) {
    if (_kbhit()) {
        int ch = _getch();

        if (ch == 0 || ch == 224) { // Trata teclas especiais (Setas)
            ch = _getch();
            switch (ch) {
                case 72: // Cima
                    if (game->snake.dir != DIR_DOWN) game->snake.dir = DIR_UP;
                    break;
                case 80: // Baixo
                    if (game->snake.dir != DIR_UP) game->snake.dir = DIR_DOWN;
                    break;
                case 75: // Esquerda
                    if (game->snake.dir != DIR_RIGHT) game->snake.dir = DIR_LEFT;
                    break;
                case 77: // Direita
                    if (game->snake.dir != DIR_LEFT) game->snake.dir = DIR_RIGHT;
                    break;
            }
        } else {
            switch (ch) {
                case 'w': case 'W':
                    if (game->snake.dir != DIR_DOWN) game->snake.dir = DIR_UP;
                    break;
                case 's': case 'S':
                    if (game->snake.dir != DIR_UP) game->snake.dir = DIR_DOWN;
                    break;
                case 'a': case 'A':
                    if (game->snake.dir != DIR_RIGHT) game->snake.dir = DIR_LEFT;
                    break;
                case 'd': case 'D':
                    if (game->snake.dir != DIR_LEFT) game->snake.dir = DIR_RIGHT;
                    break;
                case 'p': case 'P':
                    game->isPaused = !game->isPaused;
                    break;
                case 'q': case 'Q': case 27: // Q ou ESC
                    game->gameOver = true;
                    break;
            }
        }
    }
}

void update_game(GameState *game) {
    if (game->isPaused || game->gameOver) return;

    // Nova posição da cabeça
    Position newHead = game->snake.body[0];

    switch (game->snake.dir) {
        case DIR_UP:    newHead.y--; break;
        case DIR_DOWN:  newHead.y++; break;
        case DIR_LEFT:  newHead.x--; break;
        case DIR_RIGHT: newHead.x++; break;
    }

    // Colisão com as paredes
    if (newHead.x <= 0 || newHead.x >= BOARD_WIDTH - 1 ||
        newHead.y <= 0 || newHead.y >= BOARD_HEIGHT - 1) {
        game->gameOver = true;
        return;
    }

    // Colisão com o próprio corpo
    for (int i = 0; i < game->snake.length; i++) {
        if (newHead.x == game->snake.body[i].x && newHead.y == game->snake.body[i].y) {
            game->gameOver = true;
            return;
        }
    }

    // Verifica se comeu a fruta
    bool ateFood = (newHead.x == game->food.pos.x && newHead.y == game->food.pos.y);

    if (ateFood) {
        game->score += game->food.points;
        game->foodEaten++;
        if (game->score > game->highScore) {
            game->highScore = game->score;
            g_highScore = game->highScore;
        }
        if (game->snake.length < MAX_SNAKE_LEN) {
            game->snake.length++;
        }
        Beep(1000, 30); // Som ao comer fruta
        spawn_food(game);
    }

    // Move o corpo
    for (int i = game->snake.length - 1; i > 0; i--) {
        game->snake.body[i] = game->snake.body[i - 1];
    }
    game->snake.body[0] = newHead;
}

void show_menu(Difficulty *selectedDiff) {
    clear_screen();
    printf("\n");
    printf("   =========================================\n");
    printf("   *                                       *\n");
    printf("   *        JOGO DA COBRINHA EM C          *\n");
    printf("   *                                       *\n");
    printf("   =========================================\n\n");
    printf("   Selecione a Dificuldade:\n\n");
    printf("     [1] Facil  (Velocidade reduzida)\n");
    printf("     [2] Medio  (Velocidade normal)\n");
    printf("     [3] Dificil (Alta velocidade)\n\n");
    printf("   Escolha (1-3): ");

    int choice = 2;
    if (scanf("%d", &choice) != 1) {
        choice = 2;
    }

    switch (choice) {
        case 1: *selectedDiff = DIFF_EASY; break;
        case 3: *selectedDiff = DIFF_HARD; break;
        default: *selectedDiff = DIFF_MEDIUM; break;
    }

    // Limpa o buffer do teclado
    while (getchar() != '\n');
}

void show_game_over(const GameState *game) {
    clear_screen();
    printf("\n");
    printf("   =========================================\n");
    printf("   !              GAME OVER                !\n");
    printf("   =========================================\n\n");
    printf("   Pontuacao Final: %d\n", game->score);
    printf("   Recorde Atual:   %d\n", game->highScore);
    printf("   Frutas Coletadas: %d\n\n", game->foodEaten);
    printf("   =========================================\n\n");
    printf("   Pressione qualquer tecla para retornar ao menu...\n");
    _getch();
}
