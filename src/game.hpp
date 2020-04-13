//
//  game.hpp
//  final_project
//
//  Created by Avinash Nathan on 4/18/19.
//

#ifndef game_hpp
#define game_hpp

#include "checker.hpp"
#include "ofMain.h"

#include <stdio.h>
#include <vector>

class game {
private:
    bool game_start;
    bool is_red_turn;
    ofTexture board_texture;
    std::vector<checker*> red_team;
    std::vector<checker*> black_team;
    const int kNewRow = 4;
    const int kBoardLength = 240;
    const int kNumericConversion = 48;
    const int kTeamSize = 8;
    const int kBoardSpaces = 8;
    float x_center;
    float y_center;

    std::vector<std::vector<std::vector<checker*>>>
    game_boards {3,std::vector<std::vector<checker*>>
                {8, std::vector<checker*>(8)}};
public:
    game();
    
    int GetTeamSize();
    
    bool GetGameStart();
    
    void SwitchTurns();
    
    void SetGameStartFalse();
    
    //used for testing purposes only
    std::vector<checker*> GetTeam(bool is_red);
    
    //used for testing purposes only
    std::vector<std::vector<std::vector<checker*>>> GetGameBoards();
    
    void DrawBoard();
    
    void StoreTeam(bool is_red);
    
    //instantiates pieces/teams and piece locations
    void DrawCheckers(bool is_red);
    
    //stores locations of pieces from both players in 3d vector
    void StoreAllCheckers();
    
    //go through all types of moves with each type of piece
    bool IsValidMove(int i_board, int i_row, int i_col, int f_board, int f_row, int f_col);
    
    //make sure key pressed is a numeric value
    bool ValidKeyPressed(int loc_index, int key);
    
    //move piece on 3d vector game_boards
    void Move(int i_board, int i_row, int i_col, int f_board, int f_row, int f_col);
    
    //make sure piece being taken by player is of opposite team
    bool TakeValidPiece(int i_board, int i_row, int i_col, int f_board, int f_row, int f_col);
    
    void TakeOppPiece(int board, int row, int col);
    
    //if there is a checker, then it will be converted to a king
    checker* ReachedOppositeSide();
    
    bool HaveWinner();
    
    bool IsRedWinner();
    
    //selects corresponding piece (return null if invalid piece is selected)
    checker* SelectPiece(int board, int row, int col);
};

#endif /* game_hpp */
