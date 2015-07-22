//
//  Led.h
//
//  Created by Imanol Gomez on 09/07/15.
//

#pragma once

#include "ofMain.h"
#include "BasicVisual.h"


class Led: public BasicVisual {
    
    static const int SIZE;
    
    public:
    
        Led(const ofPoint& position, int id, int channel);
    
        virtual ~Led();
       
        void draw();
    
        void draw(int width, int height);
    
        int getId() const {return m_id;}
    
        int getChannel() const {return m_channel;}
    
        void normalize(const ofRectangle& boundingBox);
    
        void setPixelColor(ofPixelsRef pixels);
    
    private:
            
        int m_id;

        int m_channel;
};




