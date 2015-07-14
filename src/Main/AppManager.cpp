/*
 *  AppManager.cpp
 *  Led Costume
 *
 *  Created by Imanol Gomez on 07/07/15.
 *
 */

#include "ofMain.h"


#include "AppManager.h"

AppManager& AppManager::getInstance()
{
	// The only instance
	// Guaranteed to be lazy initialized
	// Guaranteed that it will be destroyed correctly
	static AppManager    m_instance;
    return m_instance;

}

AppManager::AppManager(): Manager(), m_debugMode(false)
{
   //Intentionally left empty
}


AppManager::~AppManager()
{
    ofLogNotice() <<"AppManager::Destructor";
}


void AppManager::setup()
{
	if(m_initialized)
		return;

    ofSetDataPathRoot("../Resources/data/");
    
    ofLogNotice() << "AppManager::initialized";

	Manager::setup();
    
    this->setupOF();
	this->setupManagers();
    this->setupGlfwWidows();
    
    //setDebugMode(m_debugMode);
}

void AppManager::setupOF()
{
    ofSetVerticalSync(true);
    ofSetEscapeQuitsApp(true);
}

void AppManager::setupGlfwWidows()
{
    ofLogNotice() << "AppManager::setupGlfwWidows";
    
    //ofVbo::disableVAOs();
    
    m_glfw = (ofxMultiGLFWWindow*)ofGetWindowPtr();
    
    // vector of windows, count set in main
    m_windows = &m_glfw->windows;
    
    WindowSettingsVector windowSettingsVector = AppManager::getInstance().getSettingsManager().getWindowsSettings();
    
    int i = 0;
    for(auto windowSettings : windowSettingsVector) {
        ofLogNotice() << "AppManager::setupGlfwWidows -> creating window: " << i;
        
        if(i>1){
            m_glfw->createWindow();
        }
        
        m_glfw->setWindow(m_windows->at(i));    // set window pointer
        m_glfw->initializeWindow();       // initialize events (mouse, keyboard, etc) on window (optional)
        ofSetWindowPosition(windowSettings.x, windowSettings.y);    // business as usual...
        ofSetWindowShape(windowSettings.width, windowSettings.height);
        ofSetWindowTitle(windowSettings.title);
        ofSetFullscreen(windowSettings.fullscreen);        // order important with fullscreen
        //ofLogNotice() << "AppManager::setupGlfwWidows -> width = " << ofGetWidth() << ", height = " << ofGetHeight();
        
        if(windowSettings.showCursor){
            ofShowCursor();
        }
        else{
            ofHideCursor();
        }
        
        i++;
    }
    
    
    m_glfw->setWindow(m_windows->at(0));
    
    //m_sceneManager.changeScene("SmokyHandsScene");
}


void AppManager::setupManagers()
{
    m_settingsManager.setup();
    m_resourceManager.setup();
    m_viewManager.setup();
    m_visualEffectsManager.setup();
    m_layoutManager.setup();
    m_keyboardManager.setup();
    m_costumeManager.setup();
    m_ledsManager.setup();
    m_noiseManager.setup();
    m_guiManager.setup();

}

void AppManager::update()
{
    m_visualEffectsManager.update();
    m_viewManager.update();
    m_noiseManager.update();
    m_ledsManager.update();
    m_costumeManager.update();
}


void AppManager::draw()
{

    // the window index will increment
    int wIndex = m_glfw->getWindowIndex();
    
    switch (wIndex) { // switch on window index
        case 0:
            ofBackground(0,0,0); // change background color on each window
            m_viewManager.draw();
            m_noiseManager.draw();
            m_guiManager.draw();
            break;
        case 1:
            ofEnableAlphaBlending();
            ofBackgroundGradient( ofColor(55), ofColor(0), OF_GRADIENT_CIRCULAR );
            m_costumeManager.draw();
            ofDisableAlphaBlending();
            break;
    }

    
}

void AppManager::toggleDebugMode()
{
    m_debugMode = !m_debugMode;
    setDebugMode(m_debugMode);
}


void AppManager::setDebugMode(bool showDebug)
{
    m_debugMode = showDebug;
    
    ofLogNotice()<<"AppManager::setDebugMode-> " << m_debugMode;
    
    if(m_debugMode){
        //ofSetLogLevel(OF_LOG_VERBOSE);
    }
    else{
        ofSetLogLevel(OF_LOG_NOTICE);
    }
    

    m_guiManager.showGui(m_debugMode);
    
}



