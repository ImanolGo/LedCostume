//
//  LaserGroup.h
//  Led Costume
//
//  Created by Imanol Gomez on 22/07/15.
//

#pragma once

#include "ofMain.h"
#include "BasicVisual.h"
#include "Laser.h"


class LaserGroup: public BasicVisual {
    
    public:
    
        LaserGroup(int id, int channel);
    
        virtual ~LaserGroup();
       
        void draw();
    
        void draw(int width, int height);
    
        int getId() const {return m_id;}
    
        int getChannel() const {return m_channel;}
    
        void  addLaser(ofPtr<Laser> laser) {m_lasers.push_back(laser);}
    
        int   getNumberLasers() const {return m_lasers.size();}
    
        const ofPoint& getLaserPosition(int laserId){ return m_lasers[laserId]->getPosition();}

        void normalize(const ofRectangle& boundingBox);
    
        void setPixelsColors(ofPixelsRef pixels);
    
    private:
    
        void updateColor();
    
    private:
    
        typedef  vector<ofPtr<Laser> > LaserVector;
    
        LaserVector     m_lasers;
        int m_id;
        int m_channel;
};




