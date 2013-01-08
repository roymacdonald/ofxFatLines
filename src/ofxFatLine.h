#ifndef VASE_RENDERER_DRAFT1_2_H
#define VASE_RENDERER_DRAFT1_2_H
#include "ofMain.h"

#include "vector_operations.h"
#include "vertex_array_holder.h"

typedef ofFloatColor Color;

static double vaserend_actual_PPI = 96.0;
const double vaserend_standard_PPI = 111.94; //the PPI I used for calibration

struct ofxFatLineOptions
{	//set the whole structure to 0 will give default options
	char joint;
		#define LJ_miter 0
		#define LJ_bevel 1
		#define LJ_round 2
	char cap;
		#define LC_butt   0
		#define LC_round  1
		#define LC_square 2
		#define LC_rect   3 //unique to vase renderer
	bool feather;
		double feathering;
		bool no_feather_at_cap;
		bool no_feather_at_core;
	
	//bool uniform_color;
	//bool uniform_weight;
};
void ofxFatLine( const ofVec2f*, const Color*, const double*, int, const ofxFatLineOptions*,bool triangulation);
void ofxFatLine( const ofVec2f*, const Color*, const double*, int, const ofxFatLineOptions*);
inline void ofxFatSegment(  const ofVec2f& P1, const ofVec2f& P2, const Color& C1, const Color& C2,
		double W1, double W2, const ofxFatLineOptions* options)
{
	ofVec2f   AP[2];
	Color  AC[2];
	double AW[2];
		AP[0] = P1; AC[0] = C1; AW[0] = W1;
		AP[1] = P2; AC[1] = C2; AW[1] = W2;
	ofxFatLine( AP, AC, AW, 2, options);
}

#endif
