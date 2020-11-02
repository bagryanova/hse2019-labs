#include "BoardTest.hpp"
#include "Board.hpp"
#include "StdioBoardView.hpp"

void BoardTest::run_all_tests() {
	test_in_field_true();
	test_in_field_small_row();
	test_in_field_small_col();
	test_in_field_big_row();
	test_in_field_big_col();
	test_can_move_small_row();
	test_can_move_small_col();
	test_can_move_big_row();
	test_can_move_big_col();
    test_can_move_not_empty();
    test_move_O();
    test_move_X();
    test_move_first();
    test_current_player_empty();
    test_current_player_O();
    test_current_player_X();
    test_get_state_draw();
    test_get_state_X_row();
    test_get_state_O_row();
    test_get_state_X_col();
    test_get_state_O_col();
    test_get_state_X_diagonal_up1();
    test_get_state_X_diagonal_up2();
    test_get_state_O_diagonal_up();
    test_get_state_X_diagonal_down();
    test_get_state_O_diagonal_down();
    test_get_state_continue();
    test_win_checker_draw_false();
    test_win_checker_X_row_true();
    test_win_checker_X_row_false();
    test_win_checker_O_row_true();
    test_win_checker_O_row_false();
    test_win_checker_X_col_true();
    test_win_checker_O_col_false();
    test_win_checker_X_diagonal_up1_true();
    test_win_checker_X_diagonal_up2_false();
}

void BoardTest::test_in_field_true() {
	Board board;
	Position pos = {1, 1};
	DO_CHECK(board.in_field(pos));
}

void BoardTest::test_in_field_small_row() {
	Board board;
	Position pos = {-2, 3};
	DO_CHECK(!board.in_field(pos));
}

void BoardTest::test_in_field_small_col() {
	Board board;
	Position pos = {3, -2};
	DO_CHECK(!board.in_field(pos));
}

void BoardTest::test_in_field_big_row() {
	Board board;
	Position pos = {10, 3};
	DO_CHECK(!board.in_field(pos));
}

void BoardTest::test_in_field_big_col() {
	Board board;
	Position pos = {3, 15};
	DO_CHECK(!board.in_field(pos));
}

void BoardTest::test_can_move_small_row() {
	Board board;
	Position pos = {-2, 3};
	DO_CHECK(!board.can_move(pos));
}

void BoardTest::test_can_move_small_col() {
	Board board;
	Position pos = {3, -2};
	DO_CHECK(!board.can_move(pos));
}

void BoardTest::test_can_move_big_row() {
	Board board;
	Position pos = {10, 3};
	DO_CHECK(!board.can_move(pos));
}

void BoardTest::test_can_move_big_col() {
	Board board;
	Position pos = {3, 15};
	DO_CHECK(!board.can_move(pos));
}

void BoardTest::test_can_move_not_empty() {
	Board board;
	Position pos = {3, 5};
	board.move(pos, Player::X);
	DO_CHECK(!board.can_move(pos));
}

void BoardTest::test_move_O() {
	Board board;
	Position pos = {3, 5};
	board.move(pos, Player::O);
	bool flag = true;
	for (int i = 0; i < board.get_size(); ++i) {
		for (int j = 0; j < board.get_size(); ++j) {
			if (i == 3 && j == 5) {
				if (board.get_element(pos) != Player::O) {
					flag = false;
				} 
			} else {
				Position cur = {i, j};
				if (board.get_element(cur) != Player::EMPTY) {
					flag = false;
				} 
			}
		}
	}
	DO_CHECK(flag);
}

void BoardTest::test_move_X() {
	Board board;
	Position pos1 = {3, 5};
	board.move(pos1, Player::O);
	Position pos2 = {4, 5};
	board.move(pos2, Player::X);
	bool flag = true;
	for (int i = 0; i < board.get_size(); ++i) {
		for (int j = 0; j < board.get_size(); ++j) {
			if (i == 4 && j == 5) {
				if (board.get_element(pos2) != Player::X) {
					flag = false;
				} 
			} else if (i == 3 && j == 5) {
				if (board.get_element(pos1) != Player::O) {
					flag = false;
				} 
			} else {
				Position cur = {i, j};
				if (board.get_element(cur) != Player::EMPTY) {
					flag = false;
				} 
			}
		}
	}
	DO_CHECK(flag);
}

void BoardTest::test_move_first() {
	Board board;
	Position pos = {9, 0};
	board.move(pos, Player::O);
	bool flag = true;
	for (int i = 0; i < board.get_size(); ++i) {
		for (int j = 0; j < board.get_size(); ++j) {
			if (i == 9 && j == 0) {
				if (board.get_element(pos) != Player::O) {
					flag = false;
				} 
			} else {
				Position cur = {i, j};
				if (board.get_element(cur) != Player::EMPTY) {
					flag = false;
				} 
			}
		}
	}
	DO_CHECK(flag);
}

void BoardTest::test_current_player_empty() {
	Board board;
	DO_CHECK(board.current_player() == Player::O);
}

void BoardTest::test_current_player_O() {
	Board board;
	Position pos1 = {3, 5};
	Position pos2 = {4, 5};
	board.move(pos1, Player::O);
	board.move(pos2, Player::X);
	DO_CHECK(board.current_player() == Player::O);
}

void BoardTest::test_current_player_X() {
	Board board;
	Position pos1 = {3, 5};
	Position pos2 = {4, 5};
	Position pos3 = {9, 0};
	board.move(pos1, Player::O);
	board.move(pos2, Player::X);
	board.move(pos3, Player::O);
	DO_CHECK(board.current_player() == Player::X);
}

void BoardTest::test_get_state_draw() {
	Board board;
	for (int i = 0; i < board.get_size(); ++i) {
		for (int j = 0; j < board.get_size(); ++j) {
			Position pos = {i, j};
			Player player;
			if ((i / 2) % 2) {
				if (j % 2) {
					player = Player::X;
				} else {
					player = Player::O;
				}				
			} else {
				if (j % 2) {
					player = Player::O;
				} else {
					player = Player::X;
				}
			}
			board.move(pos, player);
		}
	}
	DO_CHECK(board.get_state() == State::DRAW);
}

void BoardTest::test_get_state_X_row() {
	Board board;
	Position posX = {2, 5};
	for (int i = 0; i < 5; ++i) {
		board.move(posX, Player::X);
		posX.col++;
	}
	DO_CHECK(board.get_state() == State::X);
}

void BoardTest::test_get_state_O_row() {
	Board board;
	Position posO = {2, 5};
	for (int i = 0; i < 5; ++i) {
		board.move(posO, Player::O);
		posO.col++;
	}
	DO_CHECK(board.get_state() == State::O);
}

void BoardTest::test_get_state_X_col() {
	Board board;
	Position posX = {1, 3};
	for (int i = 0; i < 5; ++i) {
		board.move(posX, Player::X);
		posX.row++;
	}
	DO_CHECK(board.get_state() == State::X);
}

void BoardTest::test_get_state_O_col() {
	Board board;
	Position posO = {4, 8};
	for (int i = 0; i < 5; ++i) {
		board.move(posO, Player::O);
		posO.row++;
	}
	DO_CHECK(board.get_state() == State::O);
}

void BoardTest::test_get_state_X_diagonal_up1() {
	Board board;
	Position posX = {6, 3};
	for (int i = 0; i < 5; ++i) {
		board.move(posX, Player::X);
		posX.col++;
		posX.row--;
	}
	DO_CHECK(board.get_state() == State::X);
}

void BoardTest::test_get_state_X_diagonal_up2() {
	Board board;
	Position posX = {9, 3};
	for (int i = 0; i < 5; ++i) {
		board.move(posX, Player::X);
		posX.col++;
		posX.row--;
	}
	DO_CHECK(board.get_state() == State::X);
}

void BoardTest::test_get_state_O_diagonal_up() {
	Board board;
	Position posO = {9, 0};
	for (int i = 0; i < 5; ++i) {
		board.move(posO, Player::O);
		posO.col++;
		posO.row--;
	}
	DO_CHECK(board.get_state() == State::O);
}

void BoardTest::test_get_state_X_diagonal_down() {
	Board board;
	Position posX = {1, 3};
	for (int i = 0; i < 5; ++i) {
		board.move(posX, Player::X);
		posX.row++;
		posX.col++;
	}
	DO_CHECK(board.get_state() == State::X);
}

void BoardTest::test_get_state_O_diagonal_down() {
	Board board;
	Position posO = {4, 1};
	for (int i = 0; i < 5; ++i) {
		board.move(posO, Player::O);
		posO.row++;
		posO.col++;
	}
	DO_CHECK(board.get_state() == State::O);
}

void BoardTest::test_get_state_continue() {
	Board board;
	Position pos1 = {3, 5};
	Position pos2 = {4, 5};
	Position pos3 = {9, 0};
	board.move(pos1, Player::O);
	board.move(pos2, Player::X);
	board.move(pos3, Player::O);
	DO_CHECK(board.get_state() == State::CONTINUE);
}

void BoardTest::test_win_checker_draw_false() {
	Board board;
	for (int i = 0; i < board.get_size(); ++i) {
		for (int j = 0; j < board.get_size(); ++j) {
			Position pos = {i, j};
			Player player;
			if ((i / 2) % 2) {
				if (j % 2) {
					player = Player::X;
				} else {
					player = Player::O;
				}				
			} else {
				if (j % 2) {
					player = Player::O;
				} else {
					player = Player::X;
				}
			}
			board.move(pos, player);
		}
	}
	Position pos = {2, 3};
	DO_CHECK(board.win_checker(pos, 1, 1) == State::CONTINUE);
}

void BoardTest::test_win_checker_X_row_true() {
	Board board;
	Position posX = {2, 5};
	for (int i = 0; i < 5; ++i) {
		board.move(posX, Player::X);
		posX.col++;
	}
	posX = {2, 5};
	DO_CHECK(board.win_checker(posX, 0, 1) == State::X);
}

void BoardTest::test_win_checker_X_row_false() {
	Board board;
	Position posX = {2, 5};
	for (int i = 0; i < 5; ++i) {
		board.move(posX, Player::X);
		posX.col++;
	}
	posX = {2, 5};
	DO_CHECK(board.win_checker(posX, 1, 0) == State::CONTINUE);
}

void BoardTest::test_win_checker_O_row_true() {
	Board board;
	Position posO = {2, 5};
	for (int i = 0; i < 5; ++i) {
		board.move(posO, Player::O);
		posO.col++;
	}
	posO = {2, 5};
	DO_CHECK(board.win_checker(posO, 0, 1) == State::O);
}

void BoardTest::test_win_checker_O_row_false() {
	Board board;
	Position posO = {2, 5};
	for (int i = 0; i < 5; ++i) {
		board.move(posO, Player::O);
		posO.col++;
	}
	posO = {2, 4};
	DO_CHECK(board.win_checker(posO, 0, 1) == State::CONTINUE);
}

void BoardTest::test_win_checker_X_col_true() {
	Board board;
	Position posX = {1, 3};
	for (int i = 0; i < 5; ++i) {
		board.move(posX, Player::X);
		posX.row++;
	}
	posX = {1, 3};
	DO_CHECK(board.win_checker(posX, 1, 0) == State::X);
}

void BoardTest::test_win_checker_O_col_false() {
	Board board;
	Position posO = {4, 8};
	for (int i = 0; i < 5; ++i) {
		board.move(posO, Player::O);
		posO.row++;
	}
	DO_CHECK(board.win_checker(posO, -1, -1) == State::CONTINUE);
}

void BoardTest::test_win_checker_X_diagonal_up1_true() {
	Board board;
	Position posX = {6, 3};
	for (int i = 0; i < 5; ++i) {
		board.move(posX, Player::X);
		posX.col++;
		posX.row--;
	}
	posX = {6, 3};
	DO_CHECK(board.win_checker(posX, -1, 1) == State::X);
}

void BoardTest::test_win_checker_X_diagonal_up2_false() {
	Board board;
	Position posX = {9, 3};
	for (int i = 0; i < 5; ++i) {
		board.move(posX, Player::X);
		posX.col++;
		posX.row--;
	}
	posX = {9, 3};
	DO_CHECK(board.win_checker(posX, -1, -1) == State::CONTINUE);
}
