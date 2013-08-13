#pragma once
#include "ofMain.h"
#include "sincosineLut.h"

//#include "vector_operations.h"
//#include "vertex_array_holder.h"

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
    ofxFatLine(const vector<ofVec3f> &P,const vector<ofFloatColor> &C, const vector<double> &W, bool triangulation = false );

    void add(const ofVec3f &thePoint, const ofFloatColor &theColor, const double &theWeight);
    void add(const vector<ofVec3f> &thePoints, const vector<ofFloatColor> &theColors, const vector<double> &theWeights);

    
    void enableFeathering(bool e = true){bFeather = e;}
    void toggleFeathering(){enableFeathering(!bFeather);}
    
    void setFeather(double f){feathering = f;}
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
    
    void draw();
    void update();
    void updatePoint(int index, ofVec3f p);
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
    void pushNewVertex(ofVec3f v, ofVec3f p, ofVec3f r1, ofVec3f r2, int index, float cos, bool bFlipped = false);    
    void pushNewAnchors(ofVec3f v, ofVec3f dir, ofFloatColor color, float l1, float l2, bool bInv);
    void pushNewAnchor(ofVec3f a, ofFloatColor c);
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
    vector<ofVec3f> crossedVectors;
    vector<ofVec3f> meshVertices;
    vector<ofIndexType>meshIndices;
    vector<ofFloatColor> meshColors;
    vector<ofVec3f>jointMeshVertices;
    vector<ofIndexType>jointMeshIndices;
    vector<ofFloatColor>jointMeshColors;

    bool bTriangulation;
	ofxFatLineJointType joint;
	ofxFatLineCapType cap;
	bool bFeather;
    double feathering;
	bool bFeatherAtCap;
	bool bFeatherAtCore;
    
    

};