//
//  checker.hpp
//  final_project
//
//  Created by Avinash Nathan on 4/17/19.
//

#ifndef checker_hpp
#define checker_hpp

#include "ofTexture.h"
#include "ofImage.h"
#include "ofMain.h"

#include <stdio.h>
#include <string>

class checker {
private:
    const int kPieceSize = 30;
    
    //type of piece
    bool is_red;
    bool is_king;
    
    //move this texture on gameboard
    std::string image_string;
    ofTexture image_texture;
    
    //stores board, x, and y locations on game_board
    int board;
    int row;
    int col;
    
    //stores board, x, and y pixel locations (for where to draw)
    int p_board;
    int p_x_position;
    int p_y_position;
    
    //board center coordinates
    float x_center;
    float y_center;
public:
    checker(bool red_piece, int board_pos, std::string img_text);
    
    void SetPixBoardPosition(int set_board);
    
    void SetPixXPosition(int set_x);
    
    void SetPixYPosition(int set_y);
    
    void SetRow(int set_row);
    
    void SetCol(int set_col);
    
    ofTexture GetImageTexture();
    
    bool GetIsRed();
    
    bool GetIsKing();
    
    int GetBoard();
    
    int GetRow();
    
    int GetCol();
    
    int GetPixBoardPosition();
    
    int GetPixXPosition();
    
    int GetPixYPosition();
    
    //move to space clicked on by user
    void ChangeLocations(int new_board, int new_row, int new_col);
    
    void ConvertToKing();
};

#endif /* checker_hpp */
