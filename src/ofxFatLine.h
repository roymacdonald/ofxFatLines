#pragma once
#include "ofMain.h"

//--------------------------------------------------------------
inline bool lineSegmentsIntersect(const ofVec2f & l1a, const ofVec2f & l1b, const ofVec2f & l2a, const ofVec2f & l2b){
	if(l1a == l2a || l1a == l2b || l1b == l2a || l1b == l2b){
		return true;
	}

	float m1, m2;//slopes
	bool infM1 = false, infM2 = false;
	bool equalSlope = false;
	if (l1a.x == l1b.x) {
		infM1 =true;
	}
	if (l2a.x == l2b.x) { //the slope is equal to infinite, or a division by 0 is created. 
		infM2 =true;
	}
	if (infM1 && infM2) {
		equalSlope = true;
	}else{
		if(!infM1){//check so we dont divide by 0
			m1 = (l1b.y - l1a.y)/(l1b.x - l1a.x);//slope line 1
		}
		if (!infM2) {
			m2 = (l2b.y - l2a.y)/(l2b.x - l2a.x);//slope line 2		
		}
		
		if (!infM1 && !infM2) {
			if (m1 == m2) {
				equalSlope = true;
			}
		}
	}

    return equalSlope;
	
}
//--------------------------------------------------------------
inline double sideOfLine(const ofVec2f& v, const ofVec2f& a, const ofVec2f& b){
    ofVec2f dir = (b-a).getNormalized().getPerpendicular();
    return v.getNormalized().dot(dir);
}
//--------------------------------------------------------------
static inline bool sameSideOfLine( const ofVec2f& V, const ofVec2f& ref, const ofVec2f& a, const ofVec2f& b){
	double sign1 = sideOfLine(V*100, a, b);
    double sign2 = sideOfLine(ref*100, a, b);
    return !( (sign1>=0) ^ (sign2>=0));
    
}
//--------------------------------------------------------------
static inline ofVec3f getMidVector(ofVec3f &a, ofVec3f &b){
    return(a.getNormalized() + b.getNormalized()).getNormalized();
}

enum ofxFatLineJointType{
    OFX_FATLINE_JOINT_MITER,
    OFX_FATLINE_JOINT_BEVEL,
    OFX_FATLINE_JOINT_ROUND
};
enum ofxFatLineCapType{
    OFX_FATLINE_CAP_BUTT,
    OFX_FATLINE_CAP_ROUND,
    OFX_FATLINE_CAP_SQUARE,
    OFX_FATLINE_CAP_RECT
};

class ofxFatLine : public ofPolyline{
public:
    ofxFatLine();
    ofxFatLine(const vector<ofDefaultVec3> &P,const vector<ofFloatColor> &C, const vector<double> &W, bool triangulation = false );

    void add(const ofDefaultVec3 &thePoint, const ofFloatColor &theColor, const double &theWeight);
    void add(const vector<ofDefaultVec3> &thePoints, const vector<ofFloatColor> &theColors, const vector<double> &theWeights);
	
	void setFromPolyline(ofPolyline & poly);
    
    void enableFeathering(bool e = true){bFeather = e;}
    void toggleFeathering(){enableFeathering(!bFeather);}
    
    void setFeather(double f){feathering = f; update();}
    double getFeather(){return feathering;}
    
    void setJointType(ofxFatLineJointType j){joint = j;}
    ofxFatLineJointType getJointType(){return joint;}
    
    void setCapType(ofxFatLineCapType c ){cap = c;}
    ofxFatLineCapType getCapType(){return cap;}
    
    void enableTriangulation(bool e = true){bTriangulation = e; }
    void toggleTriangulation(){enableTriangulation(!bTriangulation);}

    void enableFeatherAtCore(bool e = true){bFeatherAtCore =e; }
    void toggleFeatherAtCore(){enableFeatherAtCore(!bFeatherAtCore);}

    void enableFeatherAtCap(bool e = true){bFeatherAtCap =e; }
    void toggleFeatherAtCap(){enableFeatherAtCap(!bFeatherAtCap);}    
    
	void setGlobalColor(ofColor col);
	void setGlobalColor(ofFloatColor col);
	
	void setGlobalWidth(float w);
	
    void draw();
    void update();
    void updatePoint(int index, ofDefaultVec3 p);
    void updateWeight(int index, float w);
    float getWeight(int index);
    void updateColor(int index, ofFloatColor& c);
    ofColor getColor(int index);
    ofMesh &getMesh(){return mesh;}
    void drawDebug();
    void printDebug();

protected:
    void addColor(const ofFloatColor &c);
    void addColors(const vector<ofFloatColor> &c);
    void addWeight(const double &w);
    void addWeights(const vector<double> &w);

    void pushQuadIndices(int index);
    void pushQuadIndices(int i1, int i2, int i3, int i4);
    void pushNewVertex(ofVec3f v, ofVec3f p, ofVec3f r1, ofVec3f r2, float maxLength, int index, float cos, bool bFlipped = false);
    void pushNewAnchors(ofDefaultVec3 v, ofDefaultVec3 dir, ofFloatColor color, float l1, float l2, bool bInv);
    void pushNewAnchor(ofDefaultVec3 a, ofFloatColor c);
    void pushTriangleIndices(int i1, int i2, int i3);
    void updateCap(ofVec3f p1, ofVec3f p2, int index);
    void updateMesh();
    void updateMeshIndices();
    void updateJoint(int index, bool bFlip);
    void updateVertex(int index);

    ofMesh mesh, capJointMesh;
    
    vector<ofFloatColor> colors;
    vector<double> weights;
    vector<ofVec3f> midVectors;
    vector<ofVec3f> flippepMidVectors;
    vector<ofDefaultVec3> crossedVectors;
    vector<ofDefaultVec3> meshVertices;
    vector<ofIndexType>meshIndices;
    vector<ofFloatColor> meshColors;
    vector<ofDefaultVec3>jointMeshVertices;
    vector<ofIndexType>jointMeshIndices;
    vector<ofFloatColor>jointMeshColors;
	
	ofFloatColor globalColor;
	float globalWidth;
	bool bUseGlobalColor;
	bool bUseGlobalWidth;
    bool bTriangulation;
	ofxFatLineJointType joint;
	ofxFatLineCapType cap;
	bool bFeather;
    double feathering;
	bool bFeatherAtCap;
	bool bFeatherAtCore;
    
    

};
