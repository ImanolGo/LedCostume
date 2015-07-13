/*
 *  NoiseManager.cpp
 *  LED Costume
 *
 *  Created by Imanol Gomez on 10/07/15.
 *
 */


#include "ofMain.h"

#include "NoiseManager.h"
#include "AppManager.h"


NoiseManager::NoiseManager(): Manager(), m_width(200), m_height(200)
{
	//Intentionally left empty
}


NoiseManager::~NoiseManager()
{
    ofLogNotice() <<"NoiseManager::Destructor" ;
}


void NoiseManager::setup()
{
	if(m_initialized)
		return;


	Manager::setup();
    
    this->setupFbo();
    this->setupNoise();
    this->setupFft();
    
    ofLogNotice() <<"NoiseManager::initialized" ;
    
}

void NoiseManager::setupFbo()
{
    m_fbo.allocate(m_width, m_height, GL_RGB);
    m_fbo.begin(); ofClear(0); m_fbo.end();
    
}

void NoiseManager::setupNoise()
{
    m_noise.freqR.set(0.2, 0.2);
    m_noise.freqG.set(0.4, 0.4);
    m_noise.freqB.set(0.8, 0.8);
    m_noise.speed.set(ofRandom(1.0), ofRandom(2.0), ofRandom(4.0));
}


void NoiseManager::setupFft()
{
    m_fft.setup();
    m_fft.setNumFFTBins(16);
    m_fft.setNormalize(true);
}



void NoiseManager::update()
{
    this->updateNoise();
}


void NoiseManager::updateNoise()
{
    m_fft.update();
    
    float lowValue = ofMap(m_fft.getLowVal(), 0, 1, 0, m_level);
    float midValue = ofMap(m_fft.getMidVal(), 0, 1, 0, m_level);
    float highValue = ofMap(m_fft.getHighVal(), 0, 1, 0, m_level);
    
    m_noise.mul.set(lowValue, midValue, highValue);
    m_noise.add.set(lowValue, midValue, highValue);
    m_noise.freqR.set(m_noiseFrequency, m_noiseFrequency);
    m_noise.freqG.set(m_noiseFrequency * 2.0, m_noiseFrequency * 2.0);
    m_noise.freqB.set(m_noiseFrequency * 4.0, m_noiseFrequency * 4.0);
    m_noise.speed.set(m_noiseSpeed, m_noiseSpeed * 1.2, m_noiseSpeed * 1.5);
    
    m_fbo.begin();
        m_noise.draw(0, 0, m_width, m_height);
    m_fbo.end();
}



void NoiseManager::draw()
{
    m_fbo.draw(0,0);
}




