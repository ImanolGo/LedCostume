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



AudioVisualsManager::AudioVisualsManager(): Manager(), m_playAudioVisuals(false)
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

void AudioVisualsManager::resetPosition()
{
    setupBoundingBox();
}

void AudioVisualsManager::update()
{
    if (!m_playAudioVisuals) {
        return;
    }
    
}


void AudioVisualsManager::draw()
{
    if (!m_playAudioVisuals) {
        return;
    }
    
}

void AudioVisualsManager::onPlayAudioVisualsChange(bool value)
{
    m_playAudioVisuals = value;
}





