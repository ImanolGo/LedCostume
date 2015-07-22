//
//  Laser.h
//
//  Created by Imanol Gomez on 22/07/15.
//

#pragma once

#include "ofMain.h"
#include "BasicVisual.h"


class Laser: public BasicVisual {
    
    static const int SIZE;
    
    public:
    
        Laser(const ofPoint& position);
    
        virtual ~Laser();
       
        void draw();
};




