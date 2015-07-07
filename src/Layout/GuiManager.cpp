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

    ofLogNotice() <<"GuiManager::initialized";

	Manager::setup();
    
}

void GuiManager::draw()
{
    if(!m_showGui)
        return;
    
    guiFPS = ofGetFrameRate();
    
}


void GuiManager::saveGuiValues()
{
    //
}

void GuiManager::loadGuiValues()
{
     //
}

void GuiManager::toggleGui()
{
    m_showGui = !m_showGui;
}
