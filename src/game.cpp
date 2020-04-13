//
//  game.cpp
//  final_project
//
//  Created by Avinash Nathan on 4/18/19.
//

#include "game.hpp"

using std::vector;
using std::cout;

game::game() {
    ofLoadImage(board_texture, "checker_board.jpg");
    x_center = ofGetWidth() * .5;
    y_center = ofGetHeight() * .5;
    game_start = true;
    is_red_turn = true;
}

int game::GetTeamSize() {
    return red_team.size();
}

bool game::GetGameStart() {
    return game_start;
}

void game::SetGameStartFalse() {
    game_start = false;
}

vector<vector<vector<checker*>>> game::GetGameBoards() {
    return game_boards;
}

vector<checker*> game::GetTeam(bool is_red) {
    if (is_red) {
        return red_team;
    } else {
        return black_team;
    }
}

void game::SwitchTurns() {
    is_red_turn = !is_red_turn;
}

void game::DrawBoard() {
    const int kDistBetBoards = 100;
    
    board_texture.draw(x_center - (kBoardLength / 2), y_center - (kBoardLength / 2), 0, kBoardLength, kBoardLength);
    board_texture.draw(x_center - (kBoardLength / 2), y_center - (kBoardLength / 2), -kDistBetBoards, kBoardLength, kBoardLength);
    board_texture.draw(x_center - (kBoardLength / 2), y_center - (kBoardLength / 2), kDistBetBoards, kBoardLength, kBoardLength);
}

void game::StoreTeam(bool is_red) {
    for (int i = 0; i < kTeamSize; i++) {
        if (is_red) {
            red_team.push_back(new checker(true, 1, "red_checker.jpg"));
        } else {
            black_team.push_back(new checker(false, 1, "black_checker.jpg"));
        }
    }
}

void game::DrawCheckers(bool is_red) {
    const int kSpaceLength = 30;
    
    for (int i = 0; i < red_team.size(); i++) {
        red_team[i] -> GetImageTexture().draw(red_team[i] -> GetPixXPosition(), red_team[i] -> GetPixYPosition(), red_team[i] -> GetPixBoardPosition(), kSpaceLength, kSpaceLength);
    }
    
    for (int i = 0; i < black_team.size(); i++) {
        black_team[i] -> GetImageTexture().draw(black_team[i] -> GetPixXPosition(), black_team[i] -> GetPixYPosition(), black_team[i] -> GetPixBoardPosition(), kSpaceLength, kSpaceLength);
    }
}

void game::StoreAllCheckers() {
    const int kRedTeamStart = kBoardSpaces - 2;
    const int kAdjustSquare = 30;
    
    int piece_counter = 0;
    int col_start = 0;
    int y_coor = y_center + (kBoardLength / 2) - kAdjustSquare;
    
    //store black team
    for (int i = 0; i <= 1; i++) {
        if (i == 1) {
            col_start++;
            y_coor -= kAdjustSquare;
        }

        for (int j = col_start; j < kBoardSpaces; j+=2) {
            game_boards[1][i][j] = black_team[piece_counter];
            black_team[piece_counter] -> SetRow(i);
            black_team[piece_counter] -> SetCol(j);
            black_team[piece_counter] -> SetPixBoardPosition(1);
            black_team[piece_counter] -> SetPixXPosition(x_center + ((j - 4) * kAdjustSquare));
            black_team[piece_counter] -> SetPixYPosition(y_coor);
            piece_counter++;
        }
    }
    
    piece_counter = 0;
    col_start = 0;
    y_coor = y_center - (kBoardLength / 2) + kAdjustSquare;
    
    //store red team
    for (int i = kRedTeamStart; i < kBoardSpaces; i++) {
        if (i == kBoardSpaces - 1) {
            col_start++;
            y_coor -= kAdjustSquare;
        }
        
        for (int j = col_start; j < kBoardSpaces; j+=2) {
            game_boards[1][i][j] = red_team[piece_counter];
            red_team[piece_counter] -> SetRow(i);
            red_team[piece_counter] -> SetCol(j);
            red_team[piece_counter] -> SetPixBoardPosition(1);
            red_team[piece_counter] -> SetPixXPosition(x_center + ((j - 4) * kAdjustSquare));
            red_team[piece_counter] -> SetPixYPosition(y_coor);
            piece_counter++;
        }
    }
}

checker* game::SelectPiece(int board, int row, int col) {
    if (game_boards[board][row][col]) {
        return game_boards[board][row][col];
    } else {
        return nullptr;
    }
    
}

bool game::TakeValidPiece(int i_board, int i_row, int i_col, int f_board, int f_row, int f_col) {
    //taking a piece (check proper piece is being taken)
    int row_between = (int) ((f_row + i_row) / 2);
    int col_between = (int) ((f_col + i_col) / 2);
    checker* take_piece = game_boards[f_board][row_between][col_between];
    
    //check if piece being taken is of other color
    if (take_piece) {
        if (game_boards[i_board][i_row][i_col] -> GetIsRed() != take_piece -> GetIsRed()) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

void game::TakeOppPiece(int board, int row, int col) {
    if (game_boards[board][row][col] -> GetIsRed()) {
        for (int i = 0; i < red_team.size(); i++) {
            if (red_team[i] -> GetBoard() == board && red_team[i] -> GetRow() == row &&
                    red_team[i] -> GetCol() == col) {
                red_team.erase(red_team.begin() + i);
            }
        }
    } else {
        for (int i = 0; i < black_team.size(); i++) {
            if (black_team[i] -> GetBoard() == board && black_team[i] -> GetRow() == row &&
                black_team[i] -> GetCol() == col) {
                black_team.erase(red_team.begin() + i);
            }
        }
    }
    
    //remove piece from 3d vector game_boards
    game_boards[board][row][col] == nullptr;
}

bool game::IsValidMove(int i_board, int i_row, int i_col, int f_board, int f_row, int f_col) {
    const int kTakePiece = 2;
    
    //make sure no piece is at new loc
    if (game_boards[f_board][f_row][f_col]) {
        return false;
    } else {
        //make sure pieces move on proper turns
        if (game_boards[i_board][i_row][i_col] -> GetIsRed() != is_red_turn) {
            return false;
        }
        
        if (f_board - i_board == 0) {
            int row_diff = f_row - i_row;
            int col_diff = f_col - i_col;
            
            if (game_boards[i_board][i_row][i_col] -> GetIsKing()) {
                //must be any diagonal move for king piece
                if (abs(row_diff) == 1 && abs(col_diff) == 1) {
                    return true;
                } else if (abs(row_diff) == kTakePiece && abs(col_diff) == kTakePiece) {
                    //taking enemy piece
                    return TakeValidPiece(i_board, i_row, i_col, f_board, f_row, f_col);
                } else {
                    return false;
                }
            } else {
                //must be diagonal in proper direction for not-king piece
                if (game_boards[i_board][i_row][i_col] -> GetIsRed()) {
                    if (row_diff == -1 && abs(col_diff) == 1) {
                        return true;
                    } else if (row_diff == -kTakePiece && abs(col_diff) == kTakePiece) {
                        //taking enemy piece
                        return TakeValidPiece(i_board, i_row, i_col, f_board, f_row, f_col);
                    } else {
                        return false;
                    }
                } else {
                    if (row_diff == 1 && abs(col_diff) == 1) {
                        return true;
                    } else if (row_diff == kTakePiece && abs(col_diff) == kTakePiece) {
                        //taking enemy piece
                        return TakeValidPiece(i_board, i_row, i_col, f_board, f_row, f_col);
                    }
                    
                    else {
                        return false;
                    }
                }
            }
        } else if (abs(f_board - i_board) == 1) {
            //must be at same location on new board
            if (f_row == i_row && f_col == i_col) {
                return true;
            } else {
                return false;
            }
        } else {
            //can't move 2 boards over
            return false;
        }
    }
}

void game::Move(int i_board, int i_row, int i_col, int f_board, int f_row, int f_col) {
    game_boards[f_board][f_row][f_col] = game_boards[i_board][i_row][i_col];
    game_boards[i_board][i_row][i_col] = nullptr;
}

checker* game::ReachedOppositeSide() {
    const int kFirstRow = 0;
    const int kLastRow = 7;
    
    for (int i = 0; i < game_boards.size(); i++) {
        //check for red piece on black side
        for (int j = 0; j < game_boards[i][kFirstRow].size(); j++) {
            if (game_boards[i][kFirstRow][j]) {
                if (game_boards[i][kFirstRow][j] -> GetIsRed()) {
                    return game_boards[i][kFirstRow][j];
                }
            }
        }
        
        //check for black piece on red side
        for (int k = 0; k < game_boards[i][kLastRow].size(); k++) {
            if (game_boards[i][kLastRow][k]) {
                if (!(game_boards[i][kLastRow][k] -> GetIsRed())) {
                    return game_boards[i][kLastRow][k];
                }
            }
        }
    }
    
    //no pieces that should turn to kings
    return nullptr;
}

bool game::ValidKeyPressed(int loc_index, int key) {
    int sel_num = key - kNumericConversion;
    
    //board values from 0-2; row/col values from 0-7
    if (loc_index == 0) {
        if (sel_num < 0 || sel_num > 2) {
            return false;
        } else {
            return true;
        }
    } else {
        if (sel_num < 0 || sel_num > 7) {
            return false;
        } else {
            return true;
        }
    }
}

bool game::HaveWinner() {
    return (red_team.size() == 0 || black_team.size() == 0);
}

bool game::IsRedWinner() {
    if (red_team.size() == 0) {
        return true;
    } else {
        return false;
    }
}
