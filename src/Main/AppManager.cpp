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

    ofLogNotice() << "AppManager::initialized";

	Manager::setup();
    
    this->setupOF();
	this->setupManagers();
    
    setDebugMode(m_debugMode);
}

void AppManager::setupOF()
{
   ofSetVerticalSync(true);
   //ofDisableAlphaBlending();
   //ofDisableSmoothing();
   //ofDisableDepthTest();
   //ofDisableLighting();
   //ofDisableBlendMode();
   //ofDisableAntiAliasing();
   ofShowCursor();
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
    m_guiManager.setup();

}

void AppManager::update()
{
    m_visualEffectsManager.update();
    m_viewManager.update();
    m_costumeManager.update();
}


void AppManager::draw()
{
    m_viewManager.draw();
    m_costumeManager.draw();
    m_guiManager.draw();
    
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
        ofSetLogLevel(OF_LOG_VERBOSE);
    }
    else{
        ofSetLogLevel(OF_LOG_NOTICE);
    }
    

    m_guiManager.showGui(m_debugMode);
    
}



