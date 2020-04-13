#include "ofApp.h"

using std::string;

void ofApp::setup(){
    ofEnableDepthTest();
    ofSetVerticalSync(true);

    piece_selected = false;
    move_loc_selected = false;
    piece_moved = false;
    game_over = false;

    x_center = ofGetWidth() * .5;
    y_center = ofGetHeight() * .5;

    camera.setDistance(150);

    //camera rotates around center of screen
    center.setPosition(ofGetWidth() * .5, ofGetHeight() * .5, 0);
    camera.setTarget(center);

    checkers_game.StoreTeam(true);
    checkers_game.StoreTeam(false);
    checkers_game.StoreAllCheckers();
    
    game_end_string.load("airstrike.ttf", 43);
}


void ofApp::update(){
    if (checkers_game.HaveWinner()) {
        game_over = true;
    }
    
    checker* king_piece = checkers_game.ReachedOppositeSide();
    if (king_piece) {
        king_piece -> ConvertToKing();
    }
    
    if (piece_moved) {
        checkers_game.SwitchTurns();
        piece_moved = false;
    }
}

void ofApp::draw() {
    //just change the color of this string
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("Red player goes first.\nTo select a piece, enter 3 numbers:\nBoard number, row, and column in that order.", x_center - 150, y_center - 300);
    ofDrawBitmapString("Key:\nTop board at back,left is 000, and\nbottom board at front,right is 277", 30, y_center);
    ofSetColor(255, 255, 255);
    
    if (game_over) {
        string winner;
        
        if (checkers_game.IsRedWinner()) {
            winner = "Red";
        } else {
            winner = "Black";
        }
        game_end_string.drawString("Game over! " + winner + " won the game.", 0, y_center);
    }

    camera.begin();
    
    checkers_game.DrawBoard();
    checkers_game.DrawCheckers(true);
    checkers_game.DrawCheckers(false);

    //if player has selected a piece (location on board)
    if (piece_selected) {
        checker* s_piece = checkers_game.SelectPiece(piece_location[0], piece_location[1], piece_location[2]);

        if (s_piece) {
            //just change the color of this string
            camera.end();
            ofSetColor(0, 0, 0);
            ofDrawBitmapString("Select position to move to.", x_center - 150, y_center - 250);
            ofSetColor(255, 255, 255);
            camera.begin();
            
            //if new loc is selected, check if it's valid then move
            if (move_loc_selected) {
                if (checkers_game.IsValidMove(piece_location[0], piece_location[1], piece_location[2], move_location[0], move_location[1], move_location[2])) {
                    
                    int row_diff = move_location[1] - piece_location[1];
                    int col_diff = move_location[2] - piece_location[2];
                    
                    //if a piece is taken, remove it from board/team
                    if (abs(row_diff) == kTakePiece && abs(col_diff) == kTakePiece) {
                        //location of piece to take
                        int row_between = (int) ((move_location[1] + piece_location[1]) / 2);
                        int col_between = (int) ((move_location[2] + piece_location[2]) / 2);
                        
                        //all pieces are on board numbered move_location[0]
                        checkers_game.TakeOppPiece(move_location[0], row_between, col_between);
                    }

                    //move and save new locations
                    checkers_game.Move(piece_location[0], piece_location[1], piece_location[2], move_location[0], move_location[1], move_location[2]);
                    
                    s_piece -> ChangeLocations(move_location[0], move_location[1], move_location[2]);
                    
                    piece_moved = true;
                }

                //reset
                piece_selected = false;
                move_loc_selected = false;
            }
        } else {
            //invalid piece selected
            piece_selected = false;
        }
    }
    
    camera.end();
}

void ofApp::keyPressed(int key){
    if (!piece_selected && !move_loc_selected) {
        //selecting piece to move
        if (key_press_counter == kPieceSelected) {
            //make sure proper numeric value was pressed
            if (checkers_game.ValidKeyPressed(
                        key_press_counter, key)) {
                piece_location[key_press_counter] = key - kNumericConversion;
                key_press_counter = 0;
                user_inputs++;
                piece_selected = true;
            }
        } else {
            //make sure proper numeric value was pressed
            if (checkers_game.ValidKeyPressed(
                        key_press_counter, key)) {
                piece_location[key_press_counter] = key - kNumericConversion;
                key_press_counter++;
            }
        }
    } else if (!move_loc_selected) {
        //selecting location to move to
        if (key_press_counter == kPieceSelected) {
            //make sure proper numeric value was pressed
            if (checkers_game.ValidKeyPressed(
                        key_press_counter, key)) {
                move_location[key_press_counter] = key - kNumericConversion;
                key_press_counter = 0;
                user_inputs++;
                move_loc_selected = true;
            }
        } else {
            //make sure proper numeric value was pressed
            if (checkers_game.ValidKeyPressed(
                        key_press_counter, key)) {
                move_location[key_press_counter] = key - kNumericConversion;
                key_press_counter++;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}



