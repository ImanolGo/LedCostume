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
    this->setupShader();
    
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
    
    m_fbo.allocate(width, height,GL_RGBA32F_ARB);
    m_fbo.begin(); ofClear(0); m_fbo.end();
}

void AudioVisualsManager::setupShader()
{
    m_shader.setGeometryInputType(GL_LINES);
    m_shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
    m_shader.setGeometryOutputCount(4);
    m_shader.load("shaders/ThickLineShaderVert.glsl", "shaders/ThickLineShaderFrag.glsl", "shaders/ThickLineShaderGeom.glsl");
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
    
    m_lowValue = ofMap(m_fft.getLowVal(), 0, 1, 8, 20*m_inputLevel);
    //float midValue = ofMap(m_fft.getMidVal(), 0, 1, 0, m_inputLevel);
    m_highValue = ofMap(m_fft.getHighVal(), 0, 1, 8, 20*m_inputLevel);
}

void AudioVisualsManager::updateFbo()
{
    
    ofEnableAlphaBlending();
    m_fbo.begin();
   
        this->drawAudioCircles();
    
    m_fbo.end();
    
    ofPixels pixels;
    m_fbo.readToPixels(pixels);
    
    ofDisableAlphaBlending();
    
    AppManager::getInstance().getLedsManager().setPixels(pixels);
}

void AudioVisualsManager::drawAudioCircles()
{
    ofPushStyle();
    ofFill();
    ofSetColor(0,0,0,15);
    ofRect(0,0,m_fbo.getWidth(),m_fbo.getHeight());
    
    m_shader.begin();
    m_shader.setUniform1f("thickness", 6);

    ofNoFill();
    ofSetLineWidth(100);
    ofSetColor(200,0,0);
    ofCircle(m_fbo.getWidth()*0.2, m_fbo.getHeight()*0.5, m_lowValue);
    ofSetColor(0,0,200);
    ofCircle(m_fbo.getWidth()*0.8, m_fbo.getHeight()*0.5, m_highValue);
    
    ofPopStyle();
    m_shader.end();
}

void AudioVisualsManager::draw()
{
    if (!m_playAudioVisuals) {
        return;
    }
    
    ofEnableAlphaBlending();
    ofSetColor(255,255,255);
    m_fbo.draw(m_boundingBox);
    ofDisableAlphaBlending();
}

void AudioVisualsManager::onPlayAudioVisualsChange(bool value)
{
    m_playAudioVisuals = value;
}





