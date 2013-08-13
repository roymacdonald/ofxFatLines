#pragma once
#include "ofMain.h"
#define DEFAULT_RES 16

class sinCosineLut{

public:
    static vector<float>sinLut;
    static vector<float>cosLut;
    static inline void changeResolution(int res){
        resolution = res;
    }
    static int getResolution(){return resolution;}
private:
    static int resolution;    

    static inline vector<float>initSin(){
        vector<float> temp;
        for (int i = 0; i<resolution; i++) {
            sinLut.push_back(sin((float(i)/resolution)*TWO_PI));
        }
        return temp;
    }

    static inline vector<float>initCos(){
        vector<float> temp;
        for (int i = 0; i<resolution; i++) {
            cosLut.push_back(cos((float(i)/resolution)*TWO_PI));
        }
        return temp;
    }
};