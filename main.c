#include "game.h"
#include <windows.h>

int main(void) {
    init_console();

    bool running = true;
    while (running) {
        Difficulty diff = DIFF_MEDIUM;
        show_menu(&diff);

        GameState game;
        init_game(&game, diff);
        clear_screen();

        while (!game.gameOver) {
            process_input(&game);
            update_game(&game);
            draw_board(&game);
            Sleep(game.delayMs);
        }

        show_game_over(&game);

        clear_screen();
        printf("\nDeseja jogar novamente? (S/N): ");
        int resp = getchar();
        if (resp != 's' && resp != 'S') {
            running = false;
        }
        while (getchar() != '\n'); // Limpa buffer
    }

    clear_screen();
    printf("\nObrigado por jogar o Snake Game em C!\n\n");
    return 0;
}
