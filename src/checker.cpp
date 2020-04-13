#include "checker.hpp"

using std::string;

checker::checker(bool red_piece, int board_pos, string img_text) {
    is_red = red_piece;
    is_king = false;
    board = board_pos;
    image_string = img_text;
    x_center = ofGetWidth() * .5;
    y_center = ofGetHeight() * .5;
    ofLoadImage(image_texture, img_text);
}

void checker::SetPixBoardPosition(int set_board) {
    p_board = set_board;
}

void checker::SetPixXPosition(int set_x) {
    p_x_position = set_x;
}

void checker::SetPixYPosition(int set_y) {
    p_y_position = set_y;
}

void checker::SetRow(int set_row) {
    row = set_row;
}

void checker::SetCol(int set_col) {
    col = set_col;
}

bool checker::GetIsRed() {
    return is_red;
}

bool checker::GetIsKing() {
    return is_king;
}

ofTexture checker::GetImageTexture() {
    return image_texture;
}

int checker::GetBoard() {
    return board;
}

int checker::GetRow() {
    return row;
}

int checker::GetCol() {
    return col;
}

int checker::GetPixBoardPosition() {
    return p_board;
}

int checker::GetPixXPosition() {
    return p_x_position;
}

int checker::GetPixYPosition() {
    return p_y_position;
}

void checker::ConvertToKing() {
    is_king = true;
    
    if (is_red) {
        ofLoadImage(image_texture, "red_king.png");
    } else {
        ofLoadImage(image_texture, "black_king.jpg");
    }
    
    image_texture.draw(p_x_position, p_y_position, p_board, kPieceSize, kPieceSize);
}

void checker::ChangeLocations(int new_board, int new_row, int new_col) {
    const int kAdjustSquare = 30;
    
    board = new_board;
    row = new_row;
    col = new_col;
    p_x_position = x_center + (new_col - 4) * kAdjustSquare;
    p_y_position = y_center - (new_row - 3) * kAdjustSquare;
    p_board = ((-1 * new_board) + 1) * 100 + 1;
}
