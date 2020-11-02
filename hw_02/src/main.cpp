#include "Board.hpp"
#include "StdioBoardView.hpp"
#include <cstring>

int main(int argc, char* argv[]) {
    bool silent = false;
    if (argc > 1 && strcmp(argv[1], "silent") == 0) {
        silent = true;
    }
    Board board;
    StdioBoardView game(board, silent);
    game.run_game();
}