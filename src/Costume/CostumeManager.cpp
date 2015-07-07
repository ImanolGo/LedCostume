/*
 *  CostumeManager.cpp
 *  LED Costume
 *
 *  Created by Imanol Gomez on 07/07/15.
 *
 */


#include "ofMain.h"

#include "CostumeManager.h"
#include "AppManager.h"


CostumeManager::CostumeManager(): Manager()
{
	//Intentionally left empty
}


CostumeManager::~CostumeManager()
{
    ofLogNotice() <<"CostumeManager::Destructor" ;
}


void CostumeManager::setup()
{
	if(m_initialized)
		return;


	Manager::setup();
    
    this->setupImages();
    
    ofLogNotice() <<"CostumeManager::initialized" ;
    
}

void CostumeManager::setupImages()
{
    string resourceName = "LedCostumes";
    ofPoint position;
    m_costumeImage =  ofPtr<ImageVisual> (new ImageVisual(position,resourceName));
    m_costumeImage->setHeight(700,true);
}

void CostumeManager::update()
{
   
}



void CostumeManager::draw()
{
    m_costumeImage->draw();
}


