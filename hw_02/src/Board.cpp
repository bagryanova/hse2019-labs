#include "Board.hpp"

#include <cassert>

Board::Board() {
	field.resize(SZ, std::vector<Player> (SZ, Player::EMPTY));
}

bool Board::in_field(Position pos) const {
	return (pos.row >= 0 && pos.row < SZ && pos.col >= 0 && pos.col < SZ);
}

bool Board::can_move(Position pos) const {
	return (in_field(pos) && field[pos.row][pos.col] == Player::EMPTY);
}

void Board::move(Position pos, Player player) {
	assert(player != Player::EMPTY);
	assert(can_move(pos));
	field[pos.row][pos.col] = player;
}

Player Board::current_player() const {
	int cntX = 0, cntO = 0;
	for (int i = 0; i < SZ; ++i) {
		for (int j = 0; j < SZ; ++j) {
			if (field[i][j] == Player::X) {
				++cntX;
			}
			if (field[i][j] == Player::O) {
				++cntO;
			}
		}
	}
	if (cntX < cntO) {
		return Player::X;
	} else {
		return Player::O;
	}
}

State Board::win_checker(Position pos, int dRow, int dCol) const {
	Player curPlayer = field[pos.row][pos.col];
	if (curPlayer == Player::EMPTY) {
		return State::CONTINUE;
	}
	for (int step = 0; step < MUST; ++step) {
		if (!in_field(pos) || field[pos.row][pos.col] != curPlayer) {
			return State::CONTINUE;
		}
		pos.col += dCol;
		pos.row += dRow;
	}
	if (curPlayer == Player::X) {
		return State::X;
	} else {
		return State::O;
	}
}

State Board::get_state() const {
	State state = State::CONTINUE;
	for (int row = 0; row < SZ; ++row) {
		for (int col = 0; col < SZ; ++col) {
			Position pos = {row, col};
			for (int dRow = -1; dRow <= 1; ++dRow) {
				for (int dCol = -1; dCol <= 1; ++dCol) {
					if (dRow == 0 && dCol == 0) {
						continue;
					}
					state = win_checker(pos, dRow, dCol);
					if (state != State::CONTINUE) {
						return state;
					}
				}
			}
		}
	}
	if (state == State::CONTINUE) {
		int cnt = 0;
		for (int row = 0; row < SZ; ++row) {
			for (int col = 0; col < SZ; ++col) {
				if (field[row][col] != Player::EMPTY) {
					++cnt;
				}
			}
		}
		if (cnt == SZ * SZ) {
			state = State::DRAW;
		}
	}
	return state;
}

int Board::get_size() const {
	return SZ;
}

Player Board::get_element(Position pos) const {
    return field[pos.row][pos.col];
}