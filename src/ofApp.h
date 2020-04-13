#pragma once

#include "stdlib.h"
#include "ofMain.h"
#include "ofCamera.h"
#include "ofGraphics.h"
#include "ofEasyCam.h"
#include "of3dPrimitives.h"
#include "of3dGraphics.h"
#include "ofNode.h"
#include "ofTexture.h"
#include "ofImage.h"
#include "game.hpp"

#include <vector>

using std::vector;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    private:
        float x_center;
        float y_center;
        ofNode center;
        ofTrueTypeFont game_end_string;
        ofEasyCam camera;
        game checkers_game;
        bool piece_selected;
        bool move_loc_selected;
        bool piece_moved;
        bool game_over;
        const int kTakePiece = 2;
        const int kPieceSelected = 2;
        const int kNumericConversion = 48;
        int key_press_counter = 0;
        int user_inputs = 0;
        vector<int> piece_location{3};
        vector<int> move_location{3};
};
