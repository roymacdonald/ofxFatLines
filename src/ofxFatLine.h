#pragma once
#include "ofMain.h"

#include "vector_operations.h"
#include "vertex_array_holder.h"

static double vaserend_actual_PPI = 96.0;
const double vaserend_standard_PPI = 111.94; //the PPI I used for calibration

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

//void ofxFatLine(const ofVec2f* P, const ofFloatColor* C, const double* weight, int size_of_P, const ofxFatLineOptions* options, bool triangulation);
//void ofxFatLine(const ofVec2f* P, const ofFloatColor* C, const double* weight, int size_of_P, const ofxFatLineOptions* options);
//inline void ofxFatSegment(  const ofVec2f& P1, const ofVec2f& P2, const ofFloatColor& C1, const ofFloatColor& C2, double W1, double W2, const ofxFatLineOptions* options);

class ofxFatLine : public ofPolyline{
public:
    ofxFatLine();
    ofxFatLine(const vector<ofVec3f> &P,const vector<ofFloatColor> &C, const vector<double> &W, bool triangulation = false );

    void add(const ofVec3f &p, const ofFloatColor &c, const double &w);
    void add(const vector<ofVec3f> &p, const vector<ofFloatColor> &c, const vector<double> &w);
    void addColor(const ofFloatColor &c);
    void addColors(const vector<ofFloatColor> &c);
    
    void addWeight(const double &w);
    void addWeights(const vector<double> &w);
    
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
    
protected:
    
    vector<ofFloatColor> colors;
    vector<double> weights;
    bool bTriangulation;
	ofxFatLineJointType joint;
	ofxFatLineCapType cap;
	bool bFeather;
    double feathering;
	bool bFeatherAtCap;
	bool bFeatherAtCore;
    

};