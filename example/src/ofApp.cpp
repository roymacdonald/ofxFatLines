#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    int totalVertices = 5;
    float yInc = (ofGetHeight()-100)/totalVertices;
    for (int i = 0; i<= totalVertices; i++) {
        points.push_back(ofDefaultVec3(ofGetWidth()*0.5f, ofGetHeight() - (yInc * i + 50),0));
        vertices.push_back(draggableVertex(points.back().x, points.back().y));
        ofFloatColor c; c.setHsb(ofRandom(1), 1, 1 );
        colors.push_back(c);
        weights.push_back(100);
    }
    fatLine.setFeather(2);
    fatLine.add(points, colors, weights);
    fatLine.printDebug();
    bDrawDebug = false;

}


//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    fatLine.draw();
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i].draw();
    }
    if (bDrawDebug) {
        fatLine.drawDebug();
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case ' ':
            bDrawDebug ^= true;
            break;

        default:
            break;
    }
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){}
//--------------------------------------------------------------
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i].drag(x, y);
        points[i].x = vertices[i].x;
        points[i].y = vertices[i].y;
        fatLine.updatePoint(i, points[i]);
    }
    fatLine.update();
}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i].over(x, y);
    }
}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i].bOver = false;
    }
    fatLine.update();
}
//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i].bOver = false;
    }
    fatLine.update();
}
//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i].bOver = false;
    }
    fatLine.update();
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){}
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){}
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){}
