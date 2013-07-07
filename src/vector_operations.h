#ifndef VECTOR_OPERATIONS_H
#define VECTOR_OPERATIONS_H
#include "ofMain.h"
//--------------------------------------------------------------

inline bool validColorRange(float t){
	return t>=0.0f && t<=1.0f;
}
//--------------------------------------------------------------
inline ofFloatColor colorBetween( const ofFloatColor& A, const ofFloatColor& B, float t=0.5f){
	if ( t<0.0f) t = 0.0f;
	if ( t>1.0f) t = 1.0f;
	
	float kt = 1.0f - t;
	ofFloatColor C ( A.r *kt + B.r *t,
                    A.g *kt + B.g *t,
                    A.b *kt + B.b *t,
                    A.a *kt + B.a *t);
	return C;
}
//--------------------------------------------------------------

const double vaserend_min_alw=0.00000000001;

//--------------------------------------------------------------
inline double vectorSlope(ofVec2f v){
    return v.y/v.x;
}
//--------------------------------------------------------------
inline double signed_area(const ofVec2f& P1, const ofVec2f& P2, const ofVec2f& P3){
    return (P2.x-P1.x)*(P3.y-P1.y) - (P3.x-P1.x)*(P2.y-P1.y);
}
//--------------------------------------------------------------
inline void makeOpposite(ofVec2f &v){
    v.x = -v.x;
    v.y = -v.y;
}
//--------------------------------------------------------------
inline void makeOppositeOf( ofVec2f &in, const ofVec2f& a){
    in.x = -a.x;
    in.y = -a.y;
}
//--------------------------------------------------------------
inline void makePerpendicular( ofVec2f &v){ //perpendicular: anti-clockwise 90 degrees

    double y_value=v.y;
    v.y=v.x;
    v.x=-y_value;
}
//--------------------------------------------------------------
inline void follow_signs( ofVec2f &in, const ofVec2f& a){
    if ( (in.x>0) != (a.x>0))	in.x = -in.x;
    if ( (in.y>0) != (a.y>0))	in.y = -in.y;
}
//--------------------------------------------------------------
static inline bool negligible( double M){
    return -vaserend_min_alw < M && M < vaserend_min_alw;
}
//--------------------------------------------------------------
inline bool negligible(const ofVec2f  &v){
    return negligible(v.x) && negligible(v.y);
}
//--------------------------------------------------------------
inline bool non_negligible(const ofVec2f  &v){
    return !negligible(v);
}
//--------------------------------------------------------------
inline bool is_zero(const ofVec2f  &v){
    return v.x==0.0 && v.y==0.0;
}
//--------------------------------------------------------------
inline bool non_zero(const ofVec2f  &v){
    return !is_zero(v);
}
//--------------------------------------------------------------
static inline  bool intersecting( const ofVec2f& A, const ofVec2f& B, const ofVec2f& C, const ofVec2f& D){	//return true if AB intersects CD
    return signed_area(A,B,C)>0 != signed_area(A,B,D)>0;
}
//--------------------------------------------------------------
static inline ofVec2f midpoint( const ofVec2f& A, const ofVec2f& B){
    return (A+B)*0.5;
}
//--------------------------------------------------------------
static inline  bool opposite_quadrant( const ofVec2f& P1, const ofVec2f& P2){
    char P1x = P1.x>0? 1:(P1.x<0?-1:0);
    char P1y = P1.y>0? 1:(P1.y<0?-1:0);
    char P2x = P2.x>0? 1:(P2.x<0?-1:0);
    char P2y = P2.y>0? 1:(P2.y<0?-1:0);
    
    if ( P1x!=P2x) {
        if ( P1y!=P2y)
            return true;
        if ( P1y==0 || P2y==0)
            return true;
    }
    if ( P1y!=P2y) {
        if ( P1x==0 || P2x==0)
            return true;
    }
    return false;
}
//--------------------------------------------------------------
//operations of 3 points
static inline bool anchor_outward_D( ofVec2f& V, const ofVec2f& b, const ofVec2f& c){
    return (b.x*V.x - c.x*V.x + b.y*V.y - c.y*V.y) > 0;
}
//--------------------------------------------------------------
static inline bool anchor_outward( ofVec2f& V, const ofVec2f& b, const ofVec2f& c, bool reverse=false){ //put the correct outward vector at V, with V placed on b, comparing distances from c
    bool determinant = anchor_outward_D ( V,b,c);
    if ( determinant == (!reverse)) { //when reverse==true, it means inward
        //positive V is the outward vector
        return false;
    } else {
        //negative V is the outward vector
        V.x=-V.x;
        V.y=-V.y;
        return true; //return whether V is changed
    }
}
//--------------------------------------------------------------
inline void anchor_inward( ofVec2f& V, const ofVec2f& b, const ofVec2f& c){
    anchor_outward( V,b,c,true);
}
//--------------------------------------------------------------
inline void dot( const ofVec2f& a, const ofVec2f& b, ofVec2f& o){ //dot product: o = a dot b
    o.x = a.x * b.x;
    o.y = a.y * b.y;
}
//operations of 4 points
//--------------------------------------------------------------
inline int intersect( const ofVec2f& P1, const ofVec2f& P2,  //line 1
                     const ofVec2f& P3, const ofVec2f& P4, //line 2
                     ofVec2f& Pout,			  //the output point
                     double* ua_out=0, double* ub_out=0)
{ //Determine the intersection point of two line segments
    double mua,mub;
    double denom,numera,numerb;
    
    denom  = (P4.y-P3.y) * (P2.x-P1.x) - (P4.x-P3.x) * (P2.y-P1.y);
    numera = (P4.x-P3.x) * (P1.y-P3.y) - (P4.y-P3.y) * (P1.x-P3.x);
    numerb = (P2.x-P1.x) * (P1.y-P3.y) - (P2.y-P1.y) * (P1.x-P3.x);
    
    if (	negligible(numera) &&
        negligible(numerb) &&
        negligible(denom)) {
		Pout.x = (P1.x + P2.x) * 0.5;
		Pout.y = (P1.y + P2.y) * 0.5;
		return 2; //meaning the lines coincide
    }
    
    if ( negligible(denom)) {
        Pout.x = 0;
        Pout.y = 0;
        return 0; //meaning lines are parallel
    }
    
    mua = numera / denom;
    mub = numerb / denom;
    if ( ua_out) *ua_out = mua;
    if ( ub_out) *ub_out = mub;
    
    Pout.x = P1.x + mua * (P2.x - P1.x);
    Pout.y = P1.y + mua * (P2.y - P1.y);
    
    bool out1 = mua < 0 || mua > 1;
    bool out2 = mub < 0 || mub > 1;
    
    if ( out1 & out2) {
        return 5; //the intersection lies outside both segments
    } else if ( out1) {
        return 3; //the intersection lies outside segment 1
    } else if ( out2) {
        return 4; //the intersection lies outside segment 2
    } else {
        return 1; //great
    }
	//http://paulbourke.net/geometry/lineline2d/
}
#endif
