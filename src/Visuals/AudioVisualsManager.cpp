/*
 *  AudioVisualsManager.cpp
 *  LED Costume
 *
 *  Created by Imanol Gomez on 21/07/15.
 *
 */


#include "ofMain.h"

#include "AudioVisualsManager.h"
#include "AppManager.h"



AudioVisualsManager::AudioVisualsManager(): Manager(), m_playAudioVisuals(false), m_inputLevel(1.0), m_highValue(0.0), m_lowValue(0.0)
{
	//Intentionally left empty
}


AudioVisualsManager::~AudioVisualsManager()
{
    ofLogNotice() <<"AudioVisualsManager::Destructor" ;
}


void AudioVisualsManager::setup()
{
	if(m_initialized)
		return;


	Manager::setup();
    
    this->setupBoundingBox();
    this->setupFbo();
    this->setupFft();
    
    ofLogNotice() <<"AudioVisualsManager::initialized" ;
    
}

void AudioVisualsManager::setupBoundingBox()
{
    float ratio = ((float)ofGetWidth())/ofGetHeight();
    
    m_boundingBox.width = AppManager::getInstance().getGuiManager().getWidth();
    m_boundingBox.height = m_boundingBox.width/ratio;
    
    
    m_boundingBox.y = AppManager::getInstance().getGuiManager().getPosition().y + AppManager::getInstance().getGuiManager().getHeight() + 20;
    m_boundingBox.x = AppManager::getInstance().getGuiManager().getPosition().x;
}


void AudioVisualsManager::setupFft()
{
    m_fft.setup();
    m_fft.setNumFFTBins(16);
    //m_fft.setVolumeRange(200);
    m_fft.setNormalize(true);
}

void AudioVisualsManager::setupFbo()
{
    float width = 1030;
    float height = 524;
    
    m_fbo.allocate(width, height);
    m_fbo.begin(); ofClear(0); m_fbo.end();
}

void AudioVisualsManager::resetPosition()
{
    setupBoundingBox();
}

void AudioVisualsManager::update()
{
    if (!m_playAudioVisuals) {
        return;
    }
    
    this->updateFft();
    this->updateFbo();
}

void AudioVisualsManager::updateFft()
{
    m_fft.update();
    
    m_lowValue = ofMap(m_fft.getLowVal(), 0, 1, 0, 30*m_inputLevel);
    //float midValue = ofMap(m_fft.getMidVal(), 0, 1, 0, m_inputLevel);
    m_highValue = ofMap(m_fft.getMidVal(), 0, 1, 0, 30*m_inputLevel);
}

void AudioVisualsManager::updateFbo()
{
    m_fbo.begin();
    ofClear(0);
    
    ofSetColor(200,0,0,100);
    ofCircle(m_fbo.getWidth()*0.2, m_fbo.getHeight()*0.5, m_lowValue);
     ofSetColor(0,0,200,100);
    ofCircle(m_fbo.getWidth()*0.8, m_fbo.getHeight()*0.5, m_highValue);
    
    m_fbo.end();
    
    ofPixels pixels;
    m_fbo.readToPixels(pixels);
    
    AppManager::getInstance().getLedsManager().setPixels(pixels);
}



void AudioVisualsManager::draw()
{
    if (!m_playAudioVisuals) {
        return;
    }
    
    m_fbo.draw(m_boundingBox);
}

void AudioVisualsManager::onPlayAudioVisualsChange(bool value)
{
    m_playAudioVisuals = value;
}





