#pragma once

#include "ofMain.h"
#include "ofxFatLine.h"

#define DRAG_SIZE 10
class draggableVertex: public ofVec3f{
public:
    draggableVertex(float x=0, float y=0){
        r.setFromCenter(x,y,DRAG_SIZE,DRAG_SIZE);
        this->x=x;
        this->y=y;
        this->z=0;
        bOver = false;

    }
    void over(float x, float y){
        bOver = (r.inside(x, y));
    }

    void drag(float x, float y){
        if (bOver) {
            r.setFromCenter(this->x, this->y, DRAG_SIZE,DRAG_SIZE);
            this->x=x;
            this->y=y;
        }
    }
    void draw(float x=0, float y =0){
        ofPushStyle();
        ofPushMatrix();
        ofTranslate(x, y);
        ofSetLineWidth(1);
        ofNoFill();
        ofSetColor(0);
        ofDrawRectangle(this->r);
        ofPopMatrix();
        ofPopStyle();

    }

    bool bOver;
    ofRectangle r;
};


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


    ofxFatLine fatLine;
    vector<draggableVertex> vertices;
    vector<ofDefaultVec3> points;
    vector<ofFloatColor> colors;
    vector<double> weights;
    bool bDrawDebug;
    
};
