#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "ofxFatLine.h"


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

    void enableCustomGLstates();
    void disableCustomGLstates();
    void testDraw();
    
    void lineUpdate();
    
    void lineInit( int N);
    
    ofxFatLineJointType getJointType();
    ofxFatLineCapType getCapType();
    
    
    
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
