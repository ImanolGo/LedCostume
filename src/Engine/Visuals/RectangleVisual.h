/*
 *  RectangleVisual.h
 *
 *  Created by Imanol Gomez on 20/07/15.
 *
 */

#pragma once

#include "BasicVisual.h"


//=========================== class RectangleVisual ==============================
//============================================================================
/** \class RectangleVisual Visual.h
 *	\brief Represents an rectangle visual
 *	\details The class uses the ofRect class to draw a rectangle
 */

class RectangleVisual: public BasicVisual
{

public:

    //! Constructor
    RectangleVisual(const BasicVisual& visual, bool centred);

    //! Destructor
    virtual ~RectangleVisual();

	//! Draws the rectangle visual
	virtual void draw();
    
protected:
    
    bool                m_centred;          ///< defines if the visual should be centred or not
};


