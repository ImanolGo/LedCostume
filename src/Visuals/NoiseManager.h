/*
 *  NoiseManager.h
 *  LED Costume
 *
 *  Created by Imanol Gomez on 10/07/15.
 *
 */


#pragma once

#include "ofxFastFboReader.h"
#include "ofxGLSLSimplexNoise.h"
#include "ofxProcessFFT.h"
#include "Manager.h"


//========================== class NoiseManager ==============================
//============================================================================
/** \class NoiseManager NoiseManager.h
 *	\brief Class managing the noise visuals
 *	\details it creates and updates noise visuals, as well it provides methods to change it in real time
 */


class NoiseManager: public Manager
{
    
    public:

        //! Constructor
        NoiseManager();

        //! Destructor
        ~NoiseManager();

        //! Setup the Halo Manager
        void setup();

        //! Update the Halo Manager
        void update();
    
        //! Draw the Halo Manager
        void draw();
    
        bool readToPixels(ofPixelsRef pix) {return m_fboReader.readToPixels(m_fbo, pix);}

    
        float getWidth() const {return m_width;}
    
        float getHeight() const {return m_height;}
    
        void onNoiseFrequencyChange(float& value) {m_noiseFrequency = value;}
    
        void onNoiseSpeedChange(float& value) {m_noiseSpeed = value;}
    
        void onInputLevelChange(float& value) {m_level = value;}
    
    
    private:
    
        void setupFbo();
    
        void setupNoise();
    
        void setupFft();
    
        void updateNoise();
    
    
    private:
  
        ofFbo               m_fbo;
        ofxFastFboReader    m_fboReader;
        ProcessFFT          m_fft;
        ofxGLSLSimplexNoise m_noise;
    
    
        float m_width;
        float m_height;
    
        float   m_noiseFrequency;
        float   m_noiseSpeed;
        float   m_level;
};




