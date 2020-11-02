#pragma once

#include "Board.hpp"

class StdioBoardView final {
public:
    explicit StdioBoardView(Board &board, bool silent);

    void run_game();

    void send_board() const;

    bool split_input(std::string &input, Position &pos) const;

    Position read_good_position(Player player) const;

private:
	Board &board;
	bool silent;
	const Position END_GAME = {-1, -1};
};