#pragma once

#include "Test.hpp"

class BoardTest final : public Test {
public:
    void run_all_tests() override;

private:
    void test_in_field_true();
    void test_in_field_small_row();
    void test_in_field_small_col();
    void test_in_field_big_row();
    void test_in_field_big_col();
    
    void test_can_move_small_row();
    void test_can_move_small_col();
    void test_can_move_big_row();
    void test_can_move_big_col();
    void test_can_move_not_empty();

    void test_move_O();
    void test_move_X();
    void test_move_first();

    void test_current_player_empty();
    void test_current_player_O();
    void test_current_player_X();

    void test_get_state_draw();
    void test_get_state_X_row();
    void test_get_state_O_row();
    void test_get_state_X_col();
    void test_get_state_O_col();
    void test_get_state_X_diagonal_up1();
    void test_get_state_X_diagonal_up2();
    void test_get_state_O_diagonal_up();
    void test_get_state_X_diagonal_down();
    void test_get_state_O_diagonal_down();
    void test_get_state_continue();

    void test_win_checker_draw_false();
    void test_win_checker_X_row_true();
    void test_win_checker_X_row_false();
    void test_win_checker_O_row_true();
    void test_win_checker_O_row_false();
    void test_win_checker_X_col_true();
    void test_win_checker_O_col_false();
    void test_win_checker_X_diagonal_up1_true();
    void test_win_checker_X_diagonal_up2_false();
};