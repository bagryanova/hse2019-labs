#pragma once

#include <string>
#include <vector>

enum class Player : char {
	O = 'O',
	X = 'X',
	EMPTY = '.'
};

enum class State: char {
	CONTINUE = 'C',
	DRAW = 'D',
	X = 'X',
	O = 'O',
};

struct Position {
	int row, col;
};


class Board final {
public:       
	explicit Board();                           

    bool can_move(Position pos) const;

    void move(Position pos, Player player);

    State win_checker(Position pos, int dcol, int drow) const;

    State get_state() const;

    Player current_player() const;

    int get_size() const;

    Player get_element(Position pos) const;

    bool in_field(Position pos) const;

private:
	const int SZ = 10;
	const int MUST = 5;
	std::vector<std::vector<Player> > field;
};