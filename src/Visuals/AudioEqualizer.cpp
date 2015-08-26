/*
 *  AudioEqualizer.cpp
 *  LED Costume
 *
 *  Created by Imanol Gomez on 26/08/15.
 *
 */


#include "ofMain.h"

#include "AudioEqualizer.h"


#include "AppManager.h"




AudioEqualizer::AudioEqualizer(): m_numFrames(0), m_currentFrame(0)
{
	//Intentionally left empty
}


AudioEqualizer::~AudioEqualizer()
{
    ofLogNotice() <<"AudioEqualizer::Destructor" ;
}


void AudioEqualizer::setup()
{
    this->setupNumFrames();
}


void AudioEqualizer::setupNumFrames()
{
    float fps =  24;
    float animationTimeInS = 1;
    
    m_numFrames = animationTimeInS*fps;
    
}


void AudioEqualizer::update()
{
    //ofLogNotice() <<"AudioEqualizer::update" ;
    
    float width = AudioVisualsManager::FBO_WIDTH;
    float height = AudioVisualsManager::FBO_HEIGHT;
    auto channelMap = AppManager::getInstance().getLedsManager().getLedChannels();
    auto ledMap = AppManager::getInstance().getLedsManager().getLeds();
    
    m_leds.clear();
    
    for( auto ledVector: ledMap){
        
        int ledOffset = 0;
        int currentChannel = 0;
        
        for(auto led: ledVector.second)
        {
            if(currentChannel != led->getChannel())
            {
                ledOffset += channelMap.at(ledVector.first)[currentChannel];
                currentChannel = led->getChannel();
            }
            
            
            int channelSize = channelMap.at(ledVector.first)[led->getChannel()];
            int numLeds = ofMap(m_currentFrame, 0, m_numFrames-1, channelSize, 0, true);
            int id = led->getId() - ledOffset;
           
            if (id < numLeds) {
                auto position =  led->getPosition();
                position.x *= width; position.y *= height;
                
                ofPtr<Led> led = ofPtr<Led> (new Led ( position, id, currentChannel ) );
                led->setColor(ofColor::red);
                m_leds.push_back(led);
            }
            
        }
    }

    m_currentFrame = (m_currentFrame + 1)%m_numFrames;
    //ofLogNotice() <<"AudioEqualizer::update-> current frame " << m_currentFrame;
}

void AudioEqualizer::draw()
{
    for (auto led: m_leds) {
        led->draw();
    }
}






