#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    for (int i = 0; i<6; i++) {
        points.push_back(ofVec3f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())));
        vertices.push_back(draggableVertex(points.back().x, points.back().y));
        ofFloatColor c; c.setHsb(ofRandom(1), 1, 1 );
        colors.push_back(c);
        weights.push_back(20);
    }
    fatLine.add(points, colors, weights);
    fatLine.printDebug();
}


//--------------------------------------------------------------
void testApp::update(){
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(255);
    fatLine.draw();
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i].draw();
    }
   fatLine.drawDebug();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){}
//--------------------------------------------------------------
void testApp::keyReleased(int key){}
//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){}
//--------------------------------------------------------------
//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i].drag(x, y);
        points[i].set(vertices[i]);
        fatLine.updatePoint(i, points[i]);
    }
    fatLine.update();
}
//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i].over(x, y);
    }
}
//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i].bOver = false;
    }
    fatLine.update();
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){}
//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){}
//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){}