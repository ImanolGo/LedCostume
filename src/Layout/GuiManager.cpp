/*
 *  GuiManager.cpp
 *  Led Costume
 *
 *  Created by Imanol Gomez on 07/07/15.
 *
 */

#include "ofMain.h"

#include "AppManager.h"

#include "GuiManager.h"


const string GuiManager::GUI_SETTINGS_FILE_NAME = "xmls/GuiSettings.xml";
const string GuiManager::GUI_SETTINGS_NAME = "LedCostume";
const int GuiManager::GUI_WIDTH = 350;


GuiManager::GuiManager(): Manager(), m_showGui(true)
{
	//Intentionally left empty
}


GuiManager::~GuiManager()
{
    this->saveGuiValues();
    ofLogNotice() <<"GuiManager::Destructor";
}


void GuiManager::setup()
{
	if(m_initialized)
		return;
    
    Manager::setup();


    this->setupGuiParameters();
    this->setupModesGui();
    this->setupImageGui();
    this->setupVideoGui();
    this->setupNoiseGui();
    this->loadGuiValues();
    
    ofLogNotice() <<"GuiManager::initialized";
    
}

void GuiManager::setupGuiParameters()
{
    m_gui.setDefaultWidth(GUI_WIDTH);
    m_gui.setup(GUI_SETTINGS_NAME, GUI_SETTINGS_FILE_NAME);
    m_gui.setPosition(ofGetWidth() - GUI_WIDTH - 20, 40);
    //m_gui.setPosition(20, 20);
    m_gui.add(m_guiFPS.set("FPS", 0, 0, 60));
    ofxGuiSetFont( "fonts/open-sans/OpenSans-Semibold.ttf", 9 );

}


void GuiManager::setupModesGui()
{

    m_parametersModes.setName("Modes");
    
    m_videoMode.set("Video",  false );
    m_videoMode.addListener(this, &GuiManager::onSetVideoMode);
    m_parametersModes.add(m_videoMode);
    
    m_noiseMode.set("Noise",  false );
    m_noiseMode.addListener(this, &GuiManager::onSetNoiseMode);
    m_parametersModes.add(m_noiseMode);
    
    m_gui.add(m_parametersModes);
}


void GuiManager::setupImageGui()
{
    auto imageManager = &AppManager::getInstance().getImageManager();
    
    m_parametersImage.setName("Image Export");
    
    m_imageRecord.set("Record",  false );
    m_imageRecord.addListener(imageManager, &ImageManager::onRecordingChange);
    m_parametersImage.add(m_imageRecord);
    
    m_imageLoop.set("Loop",  false );
    m_imageLoop.addListener(imageManager, &ImageManager::onLoopingChange);
    m_parametersImage.add(m_imageLoop);

    
    m_gui.add(m_parametersImage);
}

void GuiManager::setupVideoGui()
{
    auto videoManager = &AppManager::getInstance().getVideoManager();
    
    m_parametersVideo.setName("Video");
    
    m_nextVideo.setup("Next Video");
    m_nextVideo.addListener(videoManager, &VideoManager::onNextVideoChange);
    
    m_gui.add(&m_nextVideo);
    
}



void GuiManager::setupNoiseGui()
{
    auto noiseManager = &AppManager::getInstance().getNoiseManager();
    
    m_parametersNoise.setName("Noise");

    m_noiseResolution.set("Noise Resolution",  64, 2, 256 );
    m_noiseResolution.addListener(noiseManager, &NoiseManager::onNoiseResolutionChange);
    m_parametersNoise.add(m_noiseResolution);
    
    m_noiseHue.set("Noise Hue",  0, 0, 255);
    m_noiseHue.addListener(noiseManager, &NoiseManager::onNoiseHueChange);
    m_parametersNoise.add(m_noiseHue);
    
    m_noiseBrightness.set("Noise Brightness",  0, 0, 255);
    m_noiseBrightness.addListener(noiseManager, &NoiseManager::onNoiseBrightnessChange);
    m_parametersNoise.add(m_noiseBrightness);

    
    m_noiseFrequency.set("Noise Frequency",  0.4, 0.0, 4.0);
    m_noiseFrequency.addListener(noiseManager, &NoiseManager::onNoiseFrequencyChange);
    m_parametersNoise.add(m_noiseFrequency);
    
    m_noiseSpeed.set("Noise Speed",  1.0, 0.001, 3);
    m_noiseSpeed.addListener(noiseManager, &NoiseManager::onNoiseSpeedChange);
    m_parametersNoise.add(m_noiseSpeed);

    
    m_gui.add(m_parametersNoise);
}


void GuiManager::draw()
{
    if(!m_showGui)
        return;
    
    this->drawRectangle();
    
    m_guiFPS = ofGetFrameRate();
    m_gui.draw();
    
}


void GuiManager::saveGuiValues()
{
    m_gui.saveToFile(GUI_SETTINGS_FILE_NAME);
}

void GuiManager::loadGuiValues()
{
    m_gui.loadFromFile(GUI_SETTINGS_FILE_NAME);
}


void GuiManager::toggleGui()
{
    m_showGui = !m_showGui;
}

void GuiManager::drawRectangle()
{
    ofPushStyle();
    ofSetColor(ofColor::black);
    ofRect( m_gui.getPosition().x - 20, 0, GUI_WIDTH + 60, ofGetHeight());
    ofPopStyle();
}



void GuiManager::onSetVideoMode(bool& value)
{
    if(value == true){
        m_noiseMode = false;
        AppManager::getInstance().getVideoManager().onPlayVideoChange(value);
        AppManager::getInstance().getNoiseManager().onPlayNoiseChange(false);
    }

}

void GuiManager::onSetNoiseMode(bool& value)
{
    if(value == true){
        m_videoMode = false;
        AppManager::getInstance().getVideoManager().onPlayVideoChange(m_videoMode.get());
        AppManager::getInstance().getNoiseManager().onPlayNoiseChange(value);
    }

}
