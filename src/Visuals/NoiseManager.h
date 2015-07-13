/*
 *  NoiseManager.h
 *  LED Costume
 *
 *  Created by Imanol Gomez on 10/07/15.
 *
 */


#pragma once

#include "ofxFastFboReader.h"
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
    
        //bool readToPixels(ofPixelsRef pix) {return m_fboReader.readToPixels(m_fbo, pix);}
    
        void readToPixels(ofPixelsRef pix) {pix = m_noiseImage.getPixelsRef();}

        ofPixelsRef getPixels() {return m_noiseImage.getPixelsRef();}
    
        float getWidth()  {return m_noiseImage.getWidth();}
    
        float getHeight()  {return m_noiseImage.getHeight();}
    
        void onNoiseFrequencyChange(float& value) {m_noiseFrequency = value;}
    
        void onNoiseSpeedChange(float& value) {m_noiseSpeed = value;}
    
        void onNoiseHueChange(int& value) {m_hue = value;}
    
        void onNoiseBrightnessChange(int& value) {m_brightness = ofMap(value, 0, 255, 0, 1);}
    
        void onNoiseResolutionChange(int& value);

    
    private:
    
        void setupBoundingBox();
    
        void setupFbo();
    
        void setupNoise();
    
        void updateNoise();
    
        void drawRectangle();
    
    
    private:
  
        ofFbo               m_fbo;
        ofxFastFboReader    m_fboReader;

        ofRectangle         m_boundingBox;
    
        float       m_noiseFrequency;
        float       m_noiseSpeed;
        int         m_noiseResolution;
    
        int         m_hue;
        float         m_brightness;
    
        ofImage m_noiseImage;
};




