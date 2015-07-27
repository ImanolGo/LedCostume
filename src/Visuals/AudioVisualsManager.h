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
#include "AudioParticles.h"
#include "AudioRings.h"


//========================== class AudioVisualsManager ==============================
//============================================================================
/** \class AudioVisualsManager AudioVisualsManager.h
 *	\brief Class managing the audio reactive visuals
 *	\details it creates and updates the audio reactive visuals
 */


class AudioVisualsManager: public Manager
{
    
    static const int NUMBER_VISUALS;
    
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
    
        void  onNextAudiohange();
    
        void resetPosition();
    
    private:
    
        void setupBoundingBox();
    
        void setupFbo();
    
        void setupShader();
    
        void setupRings();
    
        void setupParticles();
    
        void updateFbo();
    
        void updateRings();
    
        void updateParticles();
    
        void setupFft();
    
        void updateFft();
    
        void drawRings();
    
        void drawParticles();
    
    public:
    
        static const int FBO_WIDTH;
        static const int FBO_HEIGHT;
    
    private:
    
        bool            m_playAudioVisuals;
        ofRectangle     m_boundingBox;
        int             m_mode;
    
        ProcessFFT      m_fft;
        float           m_inputLevel;
    
        AudioParticles  m_particles;
        AudioRings      m_rings;

        ofFbo               m_fbo;
        ofShader            m_shader;
};



