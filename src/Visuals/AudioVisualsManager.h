/*
 *  AudioVisualsManager.h
 *  LED Costume
 *
 *  Created by Imanol Gomez on 21/07/15.
 *
 */


#pragma once

#include "Manager.h"

#include "ofxProcessFFT.h"


//========================== class AudioVisualsManager ==============================
//============================================================================
/** \class AudioVisualsManager AudioVisualsManager.h
 *	\brief Class managing the audio reactive visuals
 *	\details it creates and updates the audio reactive visuals
 */


class AudioVisualsManager: public Manager
{
    
    public:

        //! Constructor
        AudioVisualsManager();

        //! Destructor
        ~AudioVisualsManager();

        //! Setup the Video Manager
        void setup();

        //! Update the Video Manager
        void update();
    
        //! Draw the Video Manager
        void draw();
    
        void  onPlayAudioVisualsChange(bool value);
    
        void  onInputLevelChange(float& value) {m_inputLevel = value;}
    
        void resetPosition();
    
    private:
    
        void setupBoundingBox();
    
        void setupFbo();
    
        void setupShader();
    
        void updateFbo();
    
        void setupFft();
    
        void updateFft();
    
        void drawAudioCircles();
    
    private:
    
        bool            m_playAudioVisuals;
        ofRectangle     m_boundingBox;
    
        ProcessFFT      m_fft;
        float           m_inputLevel;
        float           m_highValue;
        float           m_lowValue;

        ofFbo           m_fbo;
        ofShader        m_shader;
};




