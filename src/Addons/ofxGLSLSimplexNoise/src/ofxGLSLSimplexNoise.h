#pragma once

#define STRINGIFY(A) #A
#include "ofMain.h"

class ofxGLSLSimplexNoise {
public:
    ofxGLSLSimplexNoise();
    void draw();
    void draw(int x, int y, int w, int h);
    
    string frag;
    string vert;
    
    ofShader shader;
    ofVec2f freqR, freqG, freqB;
    ofVec2f shiftR, shiftG, shiftB;
    ofVec3f mul;
    ofVec3f add;
    ofVec3f speed;
    ofFbo fbo;
};