#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "vase_renderer_draft1_2.h"


#define BUF_SIZE 20
class testApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void sliderChange(float & f);
    void pointsChanged(int & n);
    void buttonPressed(bool & b);
    void enable_glstates();
    void disable_glstates();
    void test_draw();
    
    void line_update();
    
    void line_update_skeleton();
    void line_init( int N);
    
    char get_joint_type();
    char get_cap_type();
    
    
    void drag_cb();
    
    bool bRedraw;
    
    
    short curx,cury, lastx,lasty;
	short cur_drag; //index of point which is being draged currently
	int tsize;

    
    ofxPanel gui;
    ofxFloatSlider weight, feathering, start_weight;
    ofxToggle feather, no_feather_at_cap, no_feather_at_core, 
    jt_miter, jt_bevel, jt_round,
    jc_butt, jc_round, jc_square, jc_rect,
    colored, alphaed, weighted,
    skeleton, triangulate;
    ofxIntSlider np;
    
    ofVec2f AP[BUF_SIZE]; 
    int size_of_AP;
    ofFloatColor AC[BUF_SIZE];
    double Aw[BUF_SIZE];
    
};
