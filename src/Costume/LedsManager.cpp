/*
 *  LedsManager.cpp
 *  LED Costume
 *
 *  Created by Imanol Gomez on 09/07/15.
 *
 */


#include "ofMain.h"

#include "LedsManager.h"
#include "AppManager.h"


LedsManager::LedsManager(): Manager()
{
	//Intentionally left empty
}


LedsManager::~LedsManager()
{
    ofLogNotice() <<"LedsManager::Destructor" ;
}


void LedsManager::setup()
{
	if(m_initialized)
		return;


	Manager::setup();
    
    ofLogNotice() <<"LedsManager::initialized" ;
    
}



void LedsManager::update()
{
    //
}



void LedsManager::draw()
{
}


