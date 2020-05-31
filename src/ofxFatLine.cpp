
#include "ofxFatLine.h"

//--------------------------------------------------------------
ofxFatLine::ofxFatLine(){
    bTriangulation = false;
	joint = OFX_FATLINE_JOINT_BEVEL;
	cap = OFX_FATLINE_CAP_BUTT;
	bFeather = true;
    feathering = 2;
	bFeatherAtCap =true;
	bFeatherAtCore = true;
	bUseGlobalColor = false;
	bUseGlobalWidth = 1;
    //cout << "ofxFatLine" << endl;
}
//--------------------------------------------------------------
void ofxFatLine::setFromPolyline(ofPolyline & poly){
//	ofxFatLine();
	setGlobalColor(ofGetStyle().color);
	setGlobalWidth(ofGetStyle().lineWidth);
	if (!poly.getVertices().empty()){
		addVertices(poly.getVertices());
	for (int i = 0; i <getVertices().size(); i++) {
		addColor(globalColor);
		addWeight(globalWidth);
	}
	update();
	//*/
	}		
}
//--------------------------------------------------------------
ofxFatLine::ofxFatLine(const vector<ofDefaultVec3> &P,const vector<ofFloatColor> &C, const vector<double> &W, bool triangulation){
    ofxFatLine();
    add(P, C, W);
    enableTriangulation(triangulation); 
   // update();
}
//--------------------------------------------------------------
void ofxFatLine::add(const ofDefaultVec3 &thePoint, const ofFloatColor &theColor, const double &theWeight){
    addVertex(thePoint);
    addColor(theColor);
    addWeight(theWeight);
    update();
}
//--------------------------------------------------------------
void ofxFatLine::add(const vector<ofDefaultVec3> &thePoints, const vector<ofFloatColor> &theColors, const vector<double> &theWeights){
    addVertices(thePoints);
    addColors(theColors);
    addWeights(theWeights);
    update();
}
//--------------------------------------------------------------
void ofxFatLine::printDebug(){
    cout << "ofxFatLine: " << endl;
    cout << "Num vertices: " << getVertices().size() << endl;
    cout << "Num colors: " << colors.size() << endl;
    cout << "Num weights: " << weights.size() << endl;
    cout << "Num mesh vertices: " << mesh.getVertices().size() << endl;
    cout << "Num mesh colors: " << mesh.getColors().size() << endl;
    cout << "------------------------------------------------" << endl;
}
//--------------------------------------------------------------
void ofxFatLine::setGlobalColor(ofColor col){
	setGlobalColor(ofFloatColor(col.r, col.g, col.b, col.a));
}
//--------------------------------------------------------------
void ofxFatLine::setGlobalColor(ofFloatColor col){
	globalColor = col;
	bUseGlobalColor = true;
}
//--------------------------------------------------------------
void ofxFatLine::setGlobalWidth(float w){
	bUseGlobalWidth = true;
	globalWidth = w;
}
//--------------------------------------------------------------
void ofxFatLine::updatePoint(int index, ofDefaultVec3 p){
    if (index < getVertices().size()) {
        getVertices()[index] = p;
    }
}
//--------------------------------------------------------------
void ofxFatLine::updateWeight(int index, float w){
    if (index < getVertices().size()) {
        weights.at(index) = w;
    }
}
//--------------------------------------------------------------
float ofxFatLine::getWeight(int index){
    if (index < getVertices().size()) {
        return weights.at(index);
    } else {
        return -1.f;
    }
}
void ofxFatLine::updateColor(int index, ofFloatColor& c){
    if (index < getVertices().size()) {
        colors.at(index) = c;
    }
};
ofColor ofxFatLine::getColor(int index){
    if (index < getVertices().size()) {
        return colors.at(index);
    } else {
        return ofColor();
    }
}
//--------------------------------------------------------------
void ofxFatLine::updateMesh(){
    meshVertices.clear();
    meshColors.clear();
    meshIndices.clear();
    for (int i =0; i<getVertices().size(); i++) {
        updateVertex(i);
        /*
         ofDefaultVec3 a (getVertices()[i-1] - getVertices()[i]);
         ofDefaultVec3 b (getVertices()[i+1] - getVertices()[i]);
         
         float  angle = a.angle(b);
         
         ofDefaultVec3 p = getMidVector(a, b);
         bool flip = !sameSideOfLine(p, flippepMidVectors.back(), getVertices()[i-1], getVertices()[i]);
         
         float cs = cos(DEG_TO_RAD * (90 - angle*0.5f));
         pushNewVertex(getVertices()[i], p, i, cs, flip);
         //*/
        
    }   
    
    mesh.clear();
    mesh.addVertices(meshVertices);
    mesh.addColors(meshColors);
    mesh.addIndices(meshIndices);
    // updateMeshIndices();
}
//--------------------------------------------------------------
void ofxFatLine::updateVertex(int index){
    if (index == 0 && getVertices().size() >1){
        updateCap(getVertices()[index+1], getVertices()[index], index);
        
    }else if(index == getVertices().size()-1 && getVertices().size() >1) {
        updateCap(getVertices()[index-1], getVertices()[index], index);
        
    }else if ( getVertices().size() >2){
        ofVec3f a (getVertices()[index-1] - getVertices()[index]);
        ofVec3f b (getVertices()[index+1] - getVertices()[index]);
        
        float  angle = a.angle(b);
        
        ofVec3f p = getMidVector(a, b);
        ///Limits midvector length to avoid strange behaviour when angles are small.
        float hyp = MIN(a.length(), b.length());
        hyp *= hyp;
        hyp += weights[index] * weights[index];
        hyp = sqrt(hyp);
        //------
        bool flip = !sameSideOfLine(p, flippepMidVectors.back(), getVertices()[index-1], getVertices()[index]);
        
        float cs = cos(DEG_TO_RAD * (90 - angle*0.5f));
        pushNewVertex(getVertices()[index], p, a.cross(ofVec3f(0,0,1).getNormalized()), b.cross(ofVec3f(0,0,1).getNormalized()),hyp, index, cs, flip);
    }
}
//--------------------------------------------------------------
void ofxFatLine::pushNewAnchor(ofDefaultVec3 a, ofFloatColor c){
    meshVertices.push_back(a);
    meshColors.push_back(c);
}
//--------------------------------------------------------------
void ofxFatLine::pushNewAnchors(ofDefaultVec3 v, ofDefaultVec3 dir, ofFloatColor color, float l1, float l2, bool bInv){
    
    ofDefaultVec3 pp = dir * l1;
    ofDefaultVec3 pa = pp + dir *l2;
    ofFloatColor c(color.r, color.g, color.g, 0);
    if (!bInv) {
        pushNewAnchor(pp + v, color);        
    }
    pushNewAnchor(pa + v, c);
    if (bInv) {
        pushNewAnchor(pp + v, color);
    }
    //    meshVertices.push_back(pp + v);
    //  meshColors.push_back(color);
    
}
//--------------------------------------------------------------
void ofxFatLine::pushNewVertex(ofVec3f v, ofVec3f p, ofVec3f r1, ofVec3f r2, float maxLength, int index, float cos, bool bFlipped){
    
    ofFloatColor c(colors[index]);
    c.a =0;
    if (cos == 0){
        cos = FLT_EPSILON;
    }
    r1.normalize();
    r2.normalize();
    bool bAligned = false;
    if (abs(cos) == 1) {
        bAligned = true;
        p = r1;
    }
    cos = 1/cos;
    
    midVectors.push_back(p);
    if (bFlipped) {
        p *=-1;
    }
    flippepMidVectors.push_back(p);
    if (bAligned) {
		cout << "vertexAligned" << endl;
		pushNewAnchors(v, p*-1, colors[index], weights[index], feathering, true);
        pushNewAnchor(v, colors[index]);
        pushNewAnchors(v, p, colors[index], weights[index], feathering, false);
        if (index != 0) {
            if (meshVertices.size() >5) {
                for (int i = meshVertices.size()-4; i<meshVertices.size(); i++) {
                    pushQuadIndices(i);
                }
            }
        }
        
    }else{
        
        if (midVectors.back().dot(r1)>0) {
            r1 *=-1;
        }
        if (midVectors.back().dot(r2)>0) {
            r2 *=-1;
        }    
        float midLength = weights[index]*cos;
        if (midLength > maxLength) {
            midLength = maxLength;
        }
        if (bFlipped) {
            pushNewAnchors(v, r1, colors[index], weights[index], feathering, !bFlipped);
            pushNewAnchors(v, midVectors.back(), colors[index], midLength, feathering*cos, bFlipped);
            pushNewAnchor(v, colors[index]);
            pushNewAnchors(v, r2, colors[index], weights[index], feathering, !bFlipped);
            
            
        }else{
            pushNewAnchors(v, r1, colors[index], weights[index], feathering, !bFlipped);
            pushNewAnchors(v, r2, colors[index], weights[index], feathering, !bFlipped);
            pushNewAnchor(v, colors[index]);
            pushNewAnchors(v, midVectors.back(), colors[index], midLength, feathering*cos, bFlipped);        
        }
        int l = meshVertices.size();
        if (l >11) {
            if (bFlipped) {
                pushQuadIndices(l - 12, l -11, l - 5, l - 4);
                pushQuadIndices(l - 11, l -10, l - 4, l - 3);
                pushQuadIndices(l - 10, l - 9, l - 3, l - 7);
                pushQuadIndices(l -  9, l - 8, l - 7, l - 6);
            }else{
                pushQuadIndices(l - 12, l -11, l - 7, l - 6);
                pushQuadIndices(l - 11, l -10, l - 6, l - 3);
                pushQuadIndices(l - 10, l - 9, l - 3, l - 2);
                pushQuadIndices(l -  9, l - 8, l - 2, l - 1);
            }
        }
        updateJoint(index,bFlipped);
    }

    /*
     ofDefaultVec3 pp = p * 50 * cos;
     ofDefaultVec3 pa = pp + p * 2 * cos;
     
     meshVertices.push_back(pa + v);
     meshColors.push_back(c);
     
     meshVertices.push_back(pp + v);
     meshColors.push_back(colors[index]); 
     
     meshVertices.push_back(v);
     meshColors.push_back(colors[index]);
     
     meshVertices.push_back(v - pp);
     meshColors.push_back(colors[index]);
     
     meshVertices.push_back(v - pa);
     meshColors.push_back(c);
     
     if (meshVertices.size() >5) {
     for (int i = meshVertices.size()-4; i<meshVertices.size(); i++) {
     pushQuadIndices(i);
     }
     }
     //*/
    
}
//--------------------------------------------------------------
void ofxFatLine::pushQuadIndices(int i1, int i2, int i3, int i4){
    pushTriangleIndices(i1, i3, i4);
    pushTriangleIndices(i1, i2, i4);
}
//--------------------------------------------------------------
void ofxFatLine::pushQuadIndices(int index){
    pushTriangleIndices(index -6, index -5, index);
    pushTriangleIndices(index -6, index -1, index);
}
//--------------------------------------------------------------
void ofxFatLine::pushTriangleIndices(int i1, int i2, int i3){
    meshIndices.push_back((ofIndexType)i1);
    meshIndices.push_back((ofIndexType)i2);
    meshIndices.push_back((ofIndexType)i3);
}
//--------------------------------------------------------------
void ofxFatLine::updateMeshIndices(){
    for (int i = 0; i < meshVertices.size()-5; i+=5) {
        for (int j = 0; j <4; j++) {
            mesh.addIndex(j+i);
            mesh.addIndex(j+i+1);
            mesh.addIndex(j+i+5);
            mesh.addIndex(j+i+1);
            mesh.addIndex(j+i+5);
            mesh.addIndex(j+i+6);
        }   
    }
}
//--------------------------------------------------------------
void ofxFatLine::updateJoint(int index, bool bFlip){
    int l = meshVertices.size()-1;
    if (joint == OFX_FATLINE_JOINT_MITER) {
        cout << "update joint miter" << endl;
        
    }else if (joint == OFX_FATLINE_JOINT_BEVEL){
        cout << "update joint bevel" << endl;
        if (bFlip) {
            pushTriangleIndices(l -1, l-2, l-6);
            pushQuadIndices(l -6, l-5, l-1, l);
        }else{
            pushTriangleIndices(l -3, l-2, l-5);
            pushQuadIndices(l -6, l-5, l-4, l-3);        
        }
    }else if (joint == OFX_FATLINE_JOINT_ROUND){
        cout << "update joint round" << endl;        
        
    }
    
}
//--------------------------------------------------------------
void ofxFatLine::updateCap(ofVec3f p1, ofVec3f p2, int index){
    ofVec3f p = (p1 - p2).cross(ofVec3f(0,0,1)).normalize();
    bool flip = false;
    ofVec3f dir = (p2-p1).getNormalized();
    if (cap == OFX_FATLINE_CAP_SQUARE) {
        p2 =  dir * weights[index]*0.5f;
    }
    
    if (getVertices().size()>1) {
        if (index==0 || index == getVertices().size()-1) {
            midVectors.push_back(p);
            if (index != 0) {
                flip = sameSideOfLine(p, flippepMidVectors.back(), p1, p2);
                if (flip) {
                    p*=-1;
                }
            }
            flippepMidVectors.push_back(p*-1);
            
            pushNewAnchors(p2, p, colors[index], weights[index], feathering, true);
            pushNewAnchor(p2, colors[index]);
            p *=-1;
            pushNewAnchors(p2, p, colors[index], weights[index], feathering, false);
            if (index != 0) {
                if (meshVertices.size() >5) {
                    for (int i = meshVertices.size()-4; i<meshVertices.size(); i++) {
                        pushQuadIndices(i);
                    }
                }
            }
        }    
    }/*
      else{
      flip = !sameSideOfLine(p, flippepMidVectors.back(), p1, p2);
      pushNewVertex(p2, p, p, p, index, 1, flip);    
      }//*/
}
//--------------------------------------------------------------
void ofxFatLine::update(){
    updateMesh();    
}
//--------------------------------------------------------------
void ofxFatLine::draw(){
    mesh.draw();
}
//--------------------------------------------------------------
void ofxFatLine::drawDebug(){
    ofPushStyle();
    //ofSetColor(255, 0,127);
    ofDrawCircle(getVertices()[0], 5);
    //ofSetColor(255, 0,0);
    //ofSetLineWidth(3);
    for (int i = 1; i<getVertices().size(); i++) {
        ofDrawLine(getVertices()[i-1], getVertices()[i]);
    }
    
    /*ofMesh m(mesh);
    m.disableColors();
    ofSetLineWidth(1);
    ofSetColor(0);
    m.drawWireframe();*/
    
    ofSetColor(0);
    /*for (int i =0; i < meshVertices.size(); i++) {
        ofDrawBitmapStringHighlight(ofToString(i), meshVertices[i]);
    }*/
    
    ofPopStyle();
    
}
//--------------------------------------------------------------
void ofxFatLine::addColor(const ofFloatColor &c){
    colors.push_back(c);
}
//--------------------------------------------------------------
void ofxFatLine::addColors(const vector<ofFloatColor> &c){
	colors.insert( colors.end(), c.begin(), c.end());
}

//--------------------------------------------------------------
void ofxFatLine::addWeight(const double &w){
    weights.push_back(w);
}
//--------------------------------------------------------------
void ofxFatLine::addWeights(const vector<double> &w){
    weights.insert(weights.end(), w.begin(), w.end());
}

//--------------------------------------------------------------


