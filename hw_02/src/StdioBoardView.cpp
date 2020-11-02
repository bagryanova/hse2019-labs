#include "StdioBoardView.hpp"

#include <string>
#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>

StdioBoardView::StdioBoardView(Board &board, bool silent): board(board), silent(silent) {};

void StdioBoardView::send_board() const {
    assert(std::cout.good());
    std::cout << std::endl;
    assert(!std::cout.fail());
    int SZ = board.get_size();
    assert(SZ > 0);
    for (int i = 0; i < SZ; ++i) {
        for (int j = 0; j < SZ; ++j) {
            Position pos = {i, j};
            assert(std::cout.good());
            std::cout << static_cast<char>(board.get_element(pos));
        }
        assert(std::cout.good());
        std::cout << std::endl;
    }
    assert(!std::cout.fail());
}

bool is_int(std::string &s) {
    for (size_t i = 0; i < s.length(); ++i) {
        if ((s[i] >= '0' && s[i] <= '9') || (i == 0 && s[i] == '-')) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}

bool StdioBoardView::split_input(std::string &input, Position &pos) const {
    std::stringstream ss;
    ss << input;
    std::vector<std::string> strs;
    std::string cur;
    while (ss >> cur) {
        strs.push_back(cur);
    }
    if (strs.size() == 2 && is_int(strs[0]) && is_int(strs[1])) {
        pos.row = stoi(strs[0]);
        pos.col = stoi(strs[1]);
        if (pos.row == END_GAME.row && pos.col == END_GAME.col) {
            return true;
        }
        return board.in_field(pos);
    }
    return false;
}

Position StdioBoardView::read_good_position(Player player) const {
    while (true) {
        assert(std::cout.good());
        std::cout << static_cast<char>(player);
        assert(std::cout.good());
        std::cout << " move: ";
        assert(!std::cout.fail());
        Position pos;
        std::string input;
        assert(std::cin.good());
        std::getline(std::cin, input); 
        assert(!std::cin.fail());
        bool good = false;
        if (split_input(input, pos)) {
            good = true;
        }
        if (pos.row == END_GAME.row && pos.col == END_GAME.col) {
            return pos;
        }
        if (!good || !board.can_move(pos)) {
            assert(std::cout.good());
            std::cout << "Bad move!\n";
            assert(!std::cout.fail());
            continue;
        } else {
            return pos;
        }
    }
}

void StdioBoardView::run_game() {
    while (true) {
        if (!silent) {
            send_board();
        }
        Player player = board.current_player();
        Position pos = read_good_position(player);
        if (pos.row == END_GAME.row && pos.col == END_GAME.col) {
            return;
        }
        board.move(pos, player);
        State state = board.get_state();
        if (state == State::X || state == State::O || state == State::DRAW) {
            send_board();
            assert(std::cout.good());
            if (state == State::X || state == State::O) {
                std::cout << static_cast<char>(state);
                assert(std::cout.good());
                std::cout << " wins!\n";
            } else {
                std::cout << "Draw.\n";
            }
            assert(!std::cout.fail());
            break;
        }
    }
}