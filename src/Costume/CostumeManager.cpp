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
    this->setupScrollView();
    
    ofLogNotice() <<"CostumeManager::initialized" ;
    
}


void CostumeManager::setupImages()
{
    string resourceName = "LedCostumes";
    ofPoint position;
    m_costumeImage =  ofPtr<ImageVisual> (new ImageVisual(position,resourceName));
    //m_costumeImage->setHeight(700,true);
    
    m_costumeSvgImage =  ofPtr<SvgVisual> (new SvgVisual(position,resourceName));
    //m_costumeImage->setHeight(700,true);

    
    //AppManager::getInstance().getViewManager().addVisual(m_costumeImage);
    //m_costumeSvgImage->setHeight(1700,true);
}


void CostumeManager::setupScrollView()
{
    ofRectangle contentRect;
    contentRect.width = m_costumeImage->getOriginalWidth();
    contentRect.height = m_costumeImage->getOriginalHeight();
    
    ofRectangle windowRect;
    windowRect.width = 1920;
    windowRect.height =  1080;
    
    //----------------------------------------------------------
    m_scrollView.setWindowRect(windowRect); // window size and position of scroll view.
    m_scrollView.setContentRect(contentRect); // the pixel size of the content being displayed in scroll view.
    m_scrollView.fitContentToWindow(OF_ASPECT_RATIO_KEEP); // fits content into window, works with ofAspectRatioMode values.
    
    m_scrollView.setScrollEasing(0.3); // smoothness of scrolling, between 0 and 1.
    m_scrollView.setBounceBack(0.3); // the speed of bounce back, between 0 and 1.
    m_scrollView.setDragVelocityDecay(0.9); // the speed of decay of drag velocity after release, between 0 and 1.
    m_scrollView.setUserInteraction(true); // enable / disable mouse or touch interaction.
    m_scrollView.setPinchZoom(true);
    
    m_scrollView.setDoubleTapZoom(true); // enable double tap zoom.
    m_scrollView.setDoubleTapZoomIncrement(1.0); // the increment value of zoom on double tap, between 0 and 1.
    m_scrollView.setDoubleTapZoomIncrementTimeInSec(0.3); // the time amount of time for zoom increment.
    m_scrollView.setDoubleTapRegistrationTimeInSec(0.25); // the time threshold between taps for double tap event to register.
    m_scrollView.setDoubleTapRegistrationDistanceInPixels(20); // the distance threshold between taps for double tap event to register.
    
    m_scrollView.setup(); // setup must always be called at the end of scroll view config.
    
}

void CostumeManager::update()
{
    m_scrollView.update();
}


void CostumeManager::draw()
{
    m_scrollView.begin();
    
        m_costumeImage->draw();
        this->drawCostumeLeds();
    
    m_scrollView.end();
    
}

void CostumeManager::drawCostumeLeds()
{
    
    auto leds = AppManager::getInstance().getLedsManager().getLeds();
    for (auto led : leds) {
        auto pos = led->getPosition();
        
        ofPushMatrix();
        ofTranslate(pos.x*m_costumeImage->getOriginalWidth(), pos.y*m_costumeImage->getOriginalHeight());
            led->draw();
        ofPopMatrix();
    }
    
}



