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


ImageManager::ImageManager(): Manager(), m_isRecording(false), m_mirror(false)
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
         this->updateColorPixels();
    }
}

void ImageManager::draw()
{
    
}

void ImageManager::updateColorPixels()
{
    this->updateLedColorPixels();
    this->updateLaserColorPixels();
}

void ImageManager::updateLedColorPixels()
{
    auto ledMap = AppManager::getInstance().getLedsManager().getLeds();
    
    for( auto& ledVector: ledMap){
        
        if(m_colorVectorMap.find(ledVector.first) == m_colorVectorMap.end()){
            m_colorVectorMap[ledVector.first] = ColorVector();
            m_imageMap[ledVector.first] = ofImage();
        }
        
        for(auto& led: ledVector.second)
        {
            //m_colorVectorMap.at(ledVector.first).push_back(led->getColor());
            auto& colors = m_colorVectorMap.at(ledVector.first);
            colors.push_back(led->getColor());
            //colors.push_back(ofColor::black);
        }
    }
}


void ImageManager::updateLaserColorPixels()
{
    auto laserMap = AppManager::getInstance().getLedsManager().getLasers();
    
    for( auto& laserVector: laserMap){
        
        if(m_colorVectorMap.find(laserVector.first) == m_colorVectorMap.end()){
            m_colorVectorMap[laserVector.first] = ColorVector();
            m_imageMap[laserVector.first] = ofImage();
        }
        
        for(auto& laserGroup: laserVector.second)
        {
            //m_colorVectorMap.at(laserVector.first).push_back(laserGroup->getColor());
            auto& colors = m_colorVectorMap.at(laserVector.first);
            colors.push_back(laserGroup->getColor());
        }
    }
}



void ImageManager::onRecordingChange(bool& value)
{
    if (m_isRecording && !value) {
        this->saveImages();
    }
    
     m_isRecording = value;
}


void ImageManager::saveImages()
{
    
    for(auto& colorMap: m_colorVectorMap)
    {
        if(m_mirror){
            this->saveImageMirror(colorMap.first);
        }
        else{
            this->saveImageSample(colorMap.first);
        }
    }
    
    m_colorVectorMap.clear();
    m_imageMap.clear();
}



void ImageManager::saveImageMirror(const string& key)
{
    
    int width = AppManager::getInstance().getLedsManager().getNumberLeds(key) + AppManager::getInstance().getLedsManager().getNumberLasers(key);
    int height = 2*m_colorVectorMap.at(key).size()/width;
    ofLogNotice() <<"ImageManager::saveImageMirror ->  width = " << width;
    ofLogNotice() <<"ImageManager::saveImageMirror ->  height = " << height;
    
    ofImage& image = m_imageMap.at(key);
    image.allocate(width, height, OF_IMAGE_COLOR);
    
    ofPixelsRef pixels = image.getPixelsRef();
    
    ColorVector& colorVector = m_colorVectorMap.at(key);
    
    //ofLogNotice() <<"ImageManager::saveImageMirror ->  colorVector size = " << colorVector.size();
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int n = x + y*width;
            
            if ( y >= height/2) {
                int y_ = height - y - 1;
                n = x + y_* width;
            }
            
            
            pixels.setColor(x, y, colorVector[n]);
        }
    }
    
    image.update(); // uploads the new pixels to the gfx card
    
    string fileName = "images/saved/image_"+ getDateTime() + "_" + key + ".bmp";
    image.saveImage(fileName);
    
    ofLogNotice() <<"ImageManager::saveImageMirror ->  Saved " << fileName;
    
}


void ImageManager::saveImageSample(const string& key)
{
    
    int width = AppManager::getInstance().getLedsManager().getNumberLeds(key) + AppManager::getInstance().getLedsManager().getNumberLasers(key);
    int height = m_colorVectorMap.at(key).size()/width;
    
    ofLogNotice() <<"ImageManager::saveImageMirror ->  width = " << width;
    ofLogNotice() <<"ImageManager::saveImageMirror ->  height = " << height;
    
    ofImage& image = m_imageMap.at(key);
    image.allocate(width, height, OF_IMAGE_COLOR);
    
    ofPixelsRef pixels = image.getPixelsRef();
    
    ColorVector& colorVector = m_colorVectorMap.at(key);
    
    //ofLogNotice() <<"ImageManager::saveImageMirror ->  colorVector size = " << colorVector.size();
    
    /*
    In a bottom-up DIB, the image buffer starts with the bottom row of pixels, followed by the next row up,
    and so forth. The top row of the image is the last row in the buffer.
    Therefore, the first byte in memory is the bottom-left pixel of the image.
    */
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int y_ = height - y - 1;
            int n = x + y_*width;
            pixels.setColor(x, y, colorVector[n]);
        }
    }
    
    image.update(); // uploads the new pixels to the gfx card
    
    string fileName = "images/saved/image_"+ getDateTime() + "_" + key + ".bmp";
    image.saveImage(fileName);
    
    ofLogNotice() <<"ImageManager::saveImageSample ->  Saved " << fileName;
    
}

string ImageManager::getDateTime()
{
    char buffer[80];
    string fmt="%d-%m-%Y-%H-%M-%S";
    time_t rawtime;
    time ( &rawtime );
    
    struct tm *timeinfo = localtime(&rawtime);
    strftime(buffer,80,fmt.c_str(),timeinfo);
    return buffer;
}





