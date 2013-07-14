
#include "ofxFatLine.h"

//--------------------------------------------------------------
inline double sideOfLine(const ofVec2f& v, const ofVec2f& a, const ofVec2f& b){
    ofVec2f dir = (b-a).normalized().perpendiculared();
    return v.normalized().dot(dir);
}
//--------------------------------------------------------------
static inline bool same_side_of_line( const ofVec2f& V, const ofVec2f& ref, const ofVec2f& a, const ofVec2f& b){
	double sign1 = sideOfLine(V*100, a, b);
    double sign2 = sideOfLine(ref*100, a, b);
    return !( (sign1>=0) ^ (sign2>=0));
    
}
//--------------------------------------------------------------
static inline ofVec3f getMidVector(ofVec3f &a, ofVec3f &b){
    return(a.normalized() + b.normalized()).normalized();
    /*
     ofVec3f perp = (a - pivot).cross(b - pivot);
     float  angle = (a - pivot).angle(b - pivot);
     return a.getRotated(angle/2,pivot, perp);//*/
}



//--------------------------------------------------------------
ofxFatLine::ofxFatLine(){
    bTriangulation = false;
	joint = OFX_FATLINE_JOINT_BEVEL;
	cap = OFX_FATLINE_CAP_BUTT;
	bFeather = true;
    feathering = 1;
	bFeatherAtCap =true;
	bFeatherAtCore = true;
}
//--------------------------------------------------------------
ofxFatLine::ofxFatLine(const vector<ofVec3f> &P,const vector<ofFloatColor> &C, const vector<double> &W, bool triangulation){
    ofxFatLine();
    add(P, C, W);
    enableTriangulation(triangulation); 
    update();
}
//--------------------------------------------------------------
void ofxFatLine::add(const ofVec3f &thePoint, const ofFloatColor &theColor, const double &theWeight){
    addVertex(thePoint);
    addColor(theColor);
    addWeight(theWeight);
    update();
}
//--------------------------------------------------------------
void ofxFatLine::add(const vector<ofVec3f> &thePoints, const vector<ofFloatColor> &theColors, const vector<double> &theWeights){
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
void ofxFatLine::updatePoint(int index, ofVec3f p){
    if (index < getVertices().size()) {
        getVertices()[index] = p;
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
         ofVec3f a (getVertices()[i-1] - getVertices()[i]);
         ofVec3f b (getVertices()[i+1] - getVertices()[i]);
         
         float  angle = a.angle(b);
         
         ofVec3f p = getMidVector(a, b);
         bool flip = !same_side_of_line(p, flippepMidVectors.back(), getVertices()[i-1], getVertices()[i]);
         
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
        bool flip = !same_side_of_line(p, flippepMidVectors.back(), getVertices()[index-1], getVertices()[index]);
        
        float cs = cos(DEG_TO_RAD * (90 - angle*0.5f));
        pushNewVertex(getVertices()[index], p, a.cross(ofVec3f(0,0,1).normalized()), b.cross(ofVec3f(0,0,1).normalized()), index, cs, flip);
    }
}
//--------------------------------------------------------------
void ofxFatLine::pushNewAnchor(ofVec3f a, ofFloatColor c){
    meshVertices.push_back(a);
    meshColors.push_back(c);
}
//--------------------------------------------------------------
void ofxFatLine::pushNewAnchors(ofVec3f v, ofVec3f dir, ofFloatColor color, float l1, float l2, bool bInv){
    
    ofVec3f pp = dir * l1;
    ofVec3f pa = pp + dir *l2;
    if (!bInv) {
        pushNewAnchor(pp + v, color);        
    }
    pushNewAnchor(pa + v, ofFloatColor(color.r, color.g, color.g, 0));
    if (bInv) {
        pushNewAnchor(pp + v, color);
    }
    //    meshVertices.push_back(pp + v);
    //  meshColors.push_back(color);
    
}
//--------------------------------------------------------------
void ofxFatLine::pushNewVertex(ofVec3f v, ofVec3f p, ofVec3f r1, ofVec3f r2, int index, float cos, bool bFlipped){
    
    ofFloatColor c(colors[index]);
    c.a =0;
    if (cos == 0){
        cos = FLT_EPSILON;
    }
    cos = 1/cos;
    midVectors.push_back(p);
    if (bFlipped) {
        p *=-1;
    }
    flippepMidVectors.push_back(p);
    
    r1.normalize();
    r2.normalize();
    if (midVectors.back().dot(r1)>0) {
        r1 *=-1;
    }
    if (midVectors.back().dot(r2)>0) {
        r2 *=-1;
    }    
    pushNewAnchors(v, r1, colors[index], weights[index], feathering, bFlipped);
    if (bFlipped) {
        pushNewAnchors(v, midVectors.back(), colors[index], weights[index]*cos, feathering*cos, !bFlipped);
        pushNewAnchor(v, colors[index]);
        pushNewAnchors(v, r2, colors[index], weights[index], feathering, bFlipped);
        
        
    }else{
        pushNewAnchors(v, r2, colors[index], weights[index], feathering, bFlipped);
        pushNewAnchor(v, colors[index]);
        pushNewAnchors(v, midVectors.back(), colors[index], weights[index]*cos, feathering*cos, !bFlipped);        
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
    /*
     ofVec3f pp = p * 50 * cos;
     ofVec3f pa = pp + p * 2 * cos;
     
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
    meshIndices.push_back((ofIndexType)i1);
    meshIndices.push_back((ofIndexType)i3);
    meshIndices.push_back((ofIndexType)i4);
    meshIndices.push_back((ofIndexType)i1);
    meshIndices.push_back((ofIndexType)i2);
    meshIndices.push_back((ofIndexType)i4);
    
}
//--------------------------------------------------------------
void ofxFatLine::pushQuadIndices(int index){
    /*
     meshIndices.push_back((ofIndexType)index -6);
     meshIndices.push_back((ofIndexType)index -5);
     meshIndices.push_back((ofIndexType)index -1);
     meshIndices.push_back((ofIndexType)index -5);
     meshIndices.push_back((ofIndexType)index -1);
     meshIndices.push_back((ofIndexType)index);
     //*/
    meshIndices.push_back((ofIndexType)index -8);
    meshIndices.push_back((ofIndexType)index -7);
    meshIndices.push_back((ofIndexType)index -1);
    meshIndices.push_back((ofIndexType)index -7);
    meshIndices.push_back((ofIndexType)index -1);
    meshIndices.push_back((ofIndexType)index);
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
void ofxFatLine::updateJoint(){
    
}
//--------------------------------------------------------------
void ofxFatLine::updateCap(ofVec3f p1, ofVec3f p2, int index){
    ofVec3f p = (p1 - p2).cross(ofVec3f(0,0,1)).normalize(); 
    bool flip = false;
    if (index>0) {
        flip = !same_side_of_line(p, flippepMidVectors.back(), p1, p2);
    }
    pushNewVertex(p2, p, p, p, index, 1, flip);
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
    ofSetColor(255, 0,127);
    ofCircle(getVertices()[0], 5);
    ofSetColor(255, 0,0);
    ofSetLineWidth(3);
    for (int i = 1; i<getVertices().size(); i++) {
        ofLine(getVertices()[i-1], getVertices()[i]);
    }
    
    ofMesh m(mesh);
    m.disableColors();
    ofSetLineWidth(1);
    ofSetColor(0);
    m.drawWireframe();
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


