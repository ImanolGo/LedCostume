/*
 *  ImageManager.cpp
 *  LED Costume
 *
 *  Created by Imanol Gomez on 15/07/15.
 *
 */


#include "ofMain.h"

#include <time.h>

#include "ImageManager.h"
#include "AppManager.h"


ImageManager::ImageManager(): Manager(), m_isRecording(false), m_loop(false)
{
	//Intentionally left empty
}


ImageManager::~ImageManager()
{
    ofLogNotice() <<"ImageManager::Destructor" ;
}


void ImageManager::setup()
{
	if(m_initialized)
		return;


	Manager::setup();
    
    
    ofLogNotice() <<"ImageManager::initialized" ;
    
}




void ImageManager::update()
{
    if (m_isRecording) {
         this->updateImage();
    }
}

void ImageManager::draw()
{
    
}


void ImageManager::onRecordingChange(bool& value)
{
    if (m_isRecording && !value) {
        this->saveImage();
    }
    
     m_isRecording = value;
}


void ImageManager::saveImage()
{
    
    if(m_loop){
        this->saveImageLoop();
    }
    else{
        this->saveImageSample();
    }
}


void ImageManager::saveImageSample()
{
    
    int width = AppManager::getInstance().getLedsManager().getNumberLeds();
    int height = m_imageVector.size();
    
    m_image.allocate(width, height, OF_IMAGE_COLOR);
    
    ofPixelsRef pixels = m_image.getPixelsRef();
    
    for (int y = 0; y < height; y++) {
        auto colors = m_imageVector[y];
        
        for (int x = 0; x < width; x++) {
            
            pixels.setColor(x, y, colors[x]);
        }
    }
    
    m_image.update(); // uploads the new pixels to the gfx card
    
    string fileName = "images/saved/image_"+ getDateTime() +".bmp";
    m_image.saveImage(fileName);
    
    ofLogNotice() <<"ImageManager::saveImage ->  Saved " << fileName;
    
    m_imageVector.clear();
}

void ImageManager::saveImageLoop()
{
    
    int width = AppManager::getInstance().getLedsManager().getNumberLeds();
    int height = 2*m_imageVector.size();
    
    m_image.allocate(width, height, OF_IMAGE_COLOR);
    
    ofPixelsRef pixels = m_image.getPixelsRef();
    
    for (int y = 0; y < height; y++) {
        
        int n = y;
        if ( y >= height/2) {
            n = height - y - 1;
        }
        auto colors = m_imageVector[n];
        
        for (int x = 0; x < width; x++) {
            pixels.setColor(x, y, colors[x]);
        }
    }

    m_image.update(); // uploads the new pixels to the gfx card
    
    string fileName = "images/saved/image_"+ getDateTime() +".bmp";
    m_image.saveImage(fileName);
    
    ofLogNotice() <<"ImageManager::saveImage ->  Saved " << fileName;
    
    m_imageVector.clear();
}


void ImageManager::updateImage()
{
    auto leds = AppManager::getInstance().getLedsManager().getLeds();
    ColorVector colors;
    
    for (auto led: leds) {
        colors.push_back(led->getColor());
    }
    
    m_imageVector.push_back(colors);
}


string ImageManager::getDateTime()
{
    char buffer[80];
    string fmt="%d-%m-%Y-%X";
    time_t rawtime;
    time ( &rawtime );
    
    struct tm *timeinfo = localtime(&rawtime);
    strftime(buffer,80,fmt.c_str(),timeinfo);
    return buffer;
}





