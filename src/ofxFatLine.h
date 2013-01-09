#ifndef VASE_RENDERER_DRAFT1_2_H
#define VASE_RENDERER_DRAFT1_2_H
#include "ofMain.h"

#include "vector_operations.h"
#include "vertex_array_holder.h"

typedef ofFloatColor ofFloatColor;

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

struct ofxFatLineOptions
{	//set the whole structure to 0 will give default options
	ofxFatLineJointType joint;
	ofxFatLineCapType cap;
	bool feather;
    double feathering;
	bool no_feather_at_cap;
	bool no_feather_at_core;
	
};
void ofxFatLine(const ofVec2f* P, const ofFloatColor* C, const double* weight, int size_of_P, const ofxFatLineOptions* options, bool triangulation);
void ofxFatLine(const ofVec2f* P, const ofFloatColor* C, const double* weight, int size_of_P, const ofxFatLineOptions* options);
inline void ofxFatSegment(  const ofVec2f& P1, const ofVec2f& P2, const ofFloatColor& C1, const ofFloatColor& C2,
		double W1, double W2, const ofxFatLineOptions* options)
{
	ofVec2f   AP[2];
	ofFloatColor  AC[2];
	double AW[2];
		AP[0] = P1; AC[0] = C1; AW[0] = W1;
		AP[1] = P2; AC[1] = C2; AW[1] = W2;
	ofxFatLine( AP, AC, AW, 2, options);
}

#endif
